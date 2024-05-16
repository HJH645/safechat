#include "httplib.h"
#include <iostream>

class HttpClientTest {
  void run() {
    httplib::Client cli("192.168.1.100", 8080); // 指定IP地址和端口

    // 发送GET请求
    auto res = cli.Get("/hello");

    if (res && res->status == 200) {
      std::cout << "Response: " << res->body << std::endl;
    } else {
      std::cout << "Request failed" << std::endl;
    }
  }
};