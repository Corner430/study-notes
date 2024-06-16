#include "CommonConnectionPool.h"
#include "Connection.h"

int main() {
  /*
  // 多线程普通连接测试，耗时：160649ms
  Connection conn;
  conn.connect("localhost", 3306, "root", "1", "chat");
  clock_t start = clock();
  thread t1([&]() {
    for (int i = 0; i < 250; ++i) {
      Connection conn;
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      conn.connect("localhost", 3306, "root", "1", "chat");
      conn.update(sql);
    }
  });

  thread t2([&]() {
    for (int i = 0; i < 250; ++i) {
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      conn.update(sql);
    }
  });

  thread t3([&]() {
    for (int i = 0; i < 250; ++i) {
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      conn.update(sql);
    }
  });

  thread t4([&]() {
    for (int i = 0; i < 250; ++i) {
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      conn.update(sql);
    }
  });

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  cout << "time: " << clock() - start << "ms" << endl;
  return 0;
  */

  // 多线程连接池测试，耗时：125148ms
  /*
  clock_t start = clock();
  thread t1([]() {
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    for (int i = 0; i < 250; ++i) {
      shared_ptr<Connection> sp = cp->getConnection();
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      sp->update(sql);
    }
  });

  thread t2([]() {
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    for (int i = 0; i < 250; ++i) {
      shared_ptr<Connection> sp = cp->getConnection();
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      sp->update(sql);
    }
  });

  thread t3([]() {
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    for (int i = 0; i < 250; ++i) {
      shared_ptr<Connection> sp = cp->getConnection();
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      sp->update(sql);
    }
  });

  thread t4([]() {
    ConnectionPool *cp = ConnectionPool::getConnectionPool();
    for (int i = 0; i < 250; ++i) {
      shared_ptr<Connection> sp = cp->getConnection();
      char sql[1024] = {0};
      sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
              "zhang san", 20, "male");
      sp->update(sql);
    }
  });
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  cout << "time: " << clock() - start << "ms" << endl;
  return 0;
  */

  //********************** 普通连接测试，耗时：73244ms **********************
  /*
  Connection conn;
  conn.connect("localhost", 3306, "root", "1", "chat");

  clock_t start = clock();
  for (int i = 0; i < 1000; ++i) {
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
            "zhang san", 20, "male");
    conn.update(sql);
  }
  cout << "time: " << clock() - start << "ms" << endl;
  return 0;
  */

  //******************** 线程池连接测试，耗时：194060ms ******************
  clock_t start = clock();
  ConnectionPool *cp = ConnectionPool::getConnectionPool();
  for (int i = 0; i < 1000; ++i) {
    shared_ptr<Connection> sp = cp->getConnection();
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
            "zhang san", 20, "male");
    sp->update(sql);
  }
  cout << "time: " << clock() - start << "ms" << endl;
  return 0;
}