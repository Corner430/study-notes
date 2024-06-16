#include "CommonConnectionPool.h"
#include "public.h"

// 线程安全的懒汉单例模式
ConnectionPool *ConnectionPool::getConnectionPool() {
  static ConnectionPool pool; // lock 和 unlock
  return &pool;
}

// 从配置文件中加载配置
bool ConnectionPool::loadConfigFile() {
  FILE *pf = fopen("mysql.conf", "r");
  if (pf == nullptr) {
    LOG("mysql.conf file is not exist!");
    return false;
  }
  while (!feof(pf)) {
    char line[1024] = {0};
    fgets(line, 1024, pf);
    string str = line;
    int idx = str.find("=", 0);
    if (-1 == idx)
      continue;

    int endidx = str.find('\n', idx);
    string key = str.substr(0, idx);
    string value = str.substr(idx + 1, endidx - idx - 1);
    if ("ip" == key)
      _ip = value;
    else if ("port" == key)
      _port = stoul(value);
    else if ("username" == key)
      _username = value;
    else if ("password" == key)
      _password = value;
    else if ("dbname" == key)
      _dbname = value;
    else if ("initSize" == key)
      _initSize = stoi(value);
    else if ("maxSize" == key)
      _maxSize = stoi(value);
    else if ("maxIdleTime" == key)
      _maxIdleTime = stoi(value);
    else if ("connectionTimeout" == key)
      _connectionTimeout = stoi(value);
  }
  return true;
}

// 构造函数
ConnectionPool::ConnectionPool() {
  // 从配置文件中加载配置
  if (!loadConfigFile())
    return;

  // 创建初始数量的数据库连接
  for (int i = 0; i < _initSize; i++) {
    Connection *p = new Connection;
    p->connect(_ip, _port, _username, _password, _dbname);
    p->refreshAliveTime(); // 刷新连接的起始的空闲时间点
    _connectionQue.push(p);
    ++_connectionCnt;
  }

  // 生产者线程
  thread produce(std::bind(&ConnectionPool::produceConnectionTask, this));
  produce.detach();

  // 定时线程，检测空闲连接
  thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
  scanner.detach();
}

// 生产者线程，生产新连接
void ConnectionPool::produceConnectionTask() {
  while (true) {
    unique_lock<mutex> lock(_queueMutex);
    while (!_connectionQue.empty()) { // 队列不为空， 释放锁并等待
      cv.wait(lock);
    }

    // 连接数量没有达到最大值，创建新连接
    if (_connectionCnt < _maxSize) {
      Connection *p = new Connection;
      p->connect(_ip, _port, _username, _password, _dbname);
      p->refreshAliveTime(); // 刷新连接的起始的空闲时间点
      _connectionQue.push(p);
      ++_connectionCnt;
    }
    cv.notify_all(); // 唤醒消费者线程
  }
}

// 对外提供接口，获取空闲连接
shared_ptr<Connection> ConnectionPool::getConnection() {
  unique_lock<mutex> lock(_queueMutex);
  while (_connectionQue.empty()) {
    // 需要判断 timeout，防止被唤醒之后，队列还是空的（别人手快，取走了）
  }
  if (cv_status::timeout ==
      cv.wait_for(lock, chrono::milliseconds(_connectionTimeout))) {
    if (_connectionQue.empty()) {
      LOG("get connection timeout!");
      return nullptr;
    }
  }

  // 自定义删除器，用于释放资源
  shared_ptr<Connection> sp(_connectionQue.front(), [&](Connection *p) {
    unique_lock<mutex> lock(_queueMutex);
    p->refreshAliveTime(); // 刷新连接的起始的空闲时间点
    _connectionQue.push(p);
  });

  _connectionQue.pop();
  if (_connectionQue.empty())
    cv.notify_all(); // 唤醒生产者线程
  return sp;
}

// 检测空闲连接，回收超时连接
void ConnectionPool::scannerConnectionTask() {
  while (true) {
    this_thread::sleep_for(chrono::seconds(_maxIdleTime)); // 模拟定时任务

    unique_lock<mutex> lock(_queueMutex);
    while (_connectionCnt > _initSize) {
      Connection *p = _connectionQue.front();
      if (p->getAliveTime() < _maxIdleTime * 1000) { // 未超时，后面的更不会超时
        break;
      }
      _connectionQue.pop();
      --_connectionCnt;
      delete p;
    }
  }
}