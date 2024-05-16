#include <httplib.h>
#include <iostream>

class HttpTest {
public:
  void run() {
    httplib::Server svr;

    // 处理GET请求
    svr.Get("/hello", [](const httplib::Request &req, httplib::Response &res) {
      res.set_content("Hello World!", "text/plain");
    });

    // 处理POST请求
    svr.Post("/post", [](const httplib::Request &req, httplib::Response &res) {
      res.set_content(req.body, "text/plain");
    });

    std::cout << "Server started on port 8080" << std::endl;
    // svr.listen("localhost", 8080); // 监听本地8080端口

    svr.listen("0.0.0.0", 8080);
  }
};
