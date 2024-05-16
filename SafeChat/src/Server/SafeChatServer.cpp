#include "./SafeChatServer.h"
#include "../Config/Config.h"
#include "../Entity/Messages.h"
#include "../Token/Token.h"
#include "../Utils/AESTools.h"
#include <cmath>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <ostream>
#include <random>
#include <string>

std::string log(const httplib::Request &req, const httplib::Response &res);

    SafeChatServer::SafeChatServer() {
  // svr.new_task_queue = [] { return new httplib::ThreadPool(1); };



  // 相对路径为编译后的路径
  svr.set_base_dir("../../../../resources/");
  // svr.set_base_dir("/home/zhy/SafeChat/resources/");
  // auto ret = svr.set_mount_point("/", "/home/zhy/SafeChat/resources/");
  auto ret = svr.set_mount_point("/", "../../../../resources");

  if (!ret) {
    // The specified base directory doesn't exist...
    std::cout<<"ERROR IN DIR!!"<<std::endl;
  }

  //   设置文件扩展名和对应的Content-Type
  svr.set_file_extension_and_mimetype_mapping("html", "text/html");
  svr.set_file_extension_and_mimetype_mapping("js", "text/javascript");
  svr.set_file_extension_and_mimetype_mapping("css", "text/css");
  svr.set_file_extension_and_mimetype_mapping("ttf", "font/ttf");

  // // 设置日志记录器
  // svr.set_logger([](const auto &req, const auto &res) {
  //   std::cout << "Request method: " << req.method << std::endl;
  //   std::cout << "Request path: " << req.path << std::endl;

  //   std::cout << "Request headers:" << std::endl;
  //   for (const auto &header : req.headers) {
  //     std::cout << header.first << ": " << header.second << std::endl;
  //   }

  //   std::cout << "Response status code: " << res.status << std::endl;
  // });

  // auto loF = [](const httplib::Request &req, httplib::Response &res) -> void {
  //   std::string userName = req.get_param_value("userName");
  //   std::string pwSha256 = req.get_param_value("password");

  //   std::cout << "login!" << std::endl;
  //   auto params = req.params;
  //   // 遍历参数
  //   for (const auto &param : params) {
  //     std::cout << "Parameter: " << param.first << ", Value: " << param.second
  //               << std::endl;
  //   }

  //   nlohmann::json json;
  //   std::string password = Config::password;
  //   std::string sha256Password = "qwe";

  //   if (pwSha256 != sha256Password) {
  //     json["valid"] = false;
  //     json["token"] = nullptr;
  //   } else {
  //     json["valid"] = true;
  //     json["token"] = Token::getNewToken();
  //   }
  //   std::cout << json.dump() << std::endl;
  //   res.set_content(json.dump(), "application/json");
  // };
  //  svr.Get("/login",
  //          [](const httplib::Request &req, httplib::Response &res) -> {

  //          });

  //   svr.Get("/login", loF);
}
SafeChatServer::SafeChatServer(int port) : port(port) { SafeChatServer(); }

SafeChatServer::~SafeChatServer() {}

void SafeChatServer::start() {

  // 测试接口
  auto encode = [](const httplib::Request &req, httplib::Response &res) {
    auto params = req.params;
    std::cout << "Hello param:" << std::endl;
    std::string plaintext;
    // 遍历参数
    for (const auto &param : params) {
      if (param.first == "plaintext") {
        plaintext = param.second;
      }
      std::cout << "Parameter: " << param.first << ", Value: " << param.second
                << std::endl;
    }
    std::string responseText =
        "ciphertext:" + AESTool::AES_encrypt("111", plaintext);
    res.set_content(responseText.c_str(), "text/html");
  };
  svr.Get("/hello", encode);

  svr.Get("/login",
          [&](const auto &req, auto &res) -> void { login(req, res); });

  svr.Post("/swapDHKey",
           [&](const auto &req, auto &res) -> void { swapDHKey(req, res); });

  svr.Get("/Messages",
          [&](const auto &req, auto &res) -> void { getMessage(req, res); });

  svr.Post("/sendMessages",
           [&](const auto &req, auto &res) -> void { sendMessage(req, res); });

  // auot getIndex=[](const httplib::Request& req,httplib::Response& res){
  //     res.set_content()
  // }
  // svr.Get("/",getIndex);

  // 处理POST请求
  svr.Post("/post", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content(req.body, "text/plain");
  });

  std::cout << "Server started on port:"<<port << std::endl;
  // svr.listen("localhost", 8080); // 监听本地8080端口

  svr.set_logger([](const httplib::Request &req, const httplib::Response &res) {
    printf("%s", log(req, res).c_str());
  });

  svr.listen("0.0.0.0", port);
}

void SafeChatServer::swapDHKey(const httplib::Request &req,
                               httplib::Response &res) {

  std::cout << "swapDHKey!" << std::endl;
  auto requestJson =nlohmann::json::parse(req.body.c_str());

  std::cout<<"requestBody: "<<requestJson.dump()<<std::endl;

  // 返回结果
  nlohmann::json json;
  std::string token = requestJson["token"];
  std::cout<<"token:"<<token<<std::endl;
  if (!Token::isValid(token)) {
    std::cout<<"Token inValid!"<<std::endl;
    json["status"] = "failed";
    json["serverPublicKey"] = nullptr;
    res.set_content(json.dump(), "application/json");
    return;
  }
  std::cout << "Token Valid!" << std::endl;
  auto clientPublicKey = std::stoull(requestJson["clientPublicKey"].dump());
  std::cout << "ClientPublicKey: " <<clientPublicKey << std::endl;
  std::random_device seed; // 硬件生成随机数种子
  std::default_random_engine randomEngine(seed());
  std::uniform_int_distribution<> dis(1, Config::q);
  // 随机选择一个私钥
  int serverPrivateKey = dis(randomEngine);
  std::cout<<"ServerPrivateKey: "<<serverPrivateKey<<std::endl;

  // 计算公钥
  int serverPublicKey = std::pow(Config::a, serverPrivateKey);

  // 计算密钥
  int sharedKey = (int)std::pow(clientPublicKey, serverPrivateKey) % Config::q;

  // 管理sharedKey
  Token::token2sharedKey.insert({token, sharedKey});

  json["status"] = "success";
  json["serverPublicKey"] = serverPublicKey;
  // std::cout << "交换报文的返回结果" << std::endl;
  // std::cout << json.dump() << std::endl;
  std::cout << "sharedKey" << std::endl;
  std::cout << sharedKey << std::endl;
  res.set_content(json.dump(), "application/json");
}

// 处理登录
void SafeChatServer::login(const httplib::Request &req,
                           httplib::Response &res) {
  std::string userName = req.get_param_value("userName");
  std::string pwSha256 = req.get_param_value("password");

  std::cout << "login!" << std::endl;
  // 遍历参数
  for (const auto &param : req.params) {
    std::cout << "Parameter: " << param.first << ", Value: " << param.second
              << std::endl;
  }

  nlohmann::json json;
  std::string sha256Password = sha256(Config::password);

  sha256Password = "qwe"; // test

  if (pwSha256 != sha256Password) {
    json["valid"] = false;
    json["token"] = nullptr;
    json["q"] = nullptr;
    json["a"] = nullptr;
  } else {
    json["valid"] = true;
    json["token"] = Token::getNewToken();
    json["q"] = Config::q;
    json["a"] = Config::a;
  }
  std::cout << json.dump() << std::endl;
  res.set_content(json.dump(), "application/json");
}

std::string SafeChatServer::sha256(const std::string &input) {
  std::string hash;
  CryptoPP::SHA256 sha;
  CryptoPP::StringSource temp(
      input, true,
      new CryptoPP::HashFilter(
          sha, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
  return hash;
}

void SafeChatServer::getMessage(const httplib::Request &req,
                                httplib::Response &res) {
  std::string token = req.get_param_value("token");
  // std::string userName = req.get_param_value("userName");
  nlohmann::json json;
  if (!token.empty() && Token::isValid(token)) {

    // TODO
    json["status"] = "success";

    json["messages"][0]["time"] = "today";
    json["messages"][0]["user"] = "qwe";
    json["messages"][0]["content"] = "test";
    auto lists = Messages::getMessageList();
    for(int i=0;i<lists.size();++i){
      json["messages"][i]["time"]=lists[i].time;
      json["messages"][i]["user"] = lists[i].userName;
      json["messages"][i]["content"] = lists[i].content;
    }
  } else {
    json["status"] = "failed";
    json["messages"] = nullptr;
  }

  res.set_content(json.dump(), "application/json");
}

// 处理发送信息的Post请求
void SafeChatServer::sendMessage(const httplib::Request &req,
                                 httplib::Response &res) {
  nlohmann::json json;
  nlohmann::json requestBody = nlohmann::json::parse(req.body.c_str());
  
  std::cout<<"SendMessage"<<std::endl;
  std::cout<<requestBody.dump()<<std::endl;

  std::string token = requestBody["token"];
  std::cout<<"token:"<<token<<std::endl;
  if (!Token::isValid(token)) {
    json["status"] = "failed";
    res.set_content(json.dump(), "application/json");
    return;
  }

  std::string userName = requestBody["userName"];
  std::string content = requestBody["content"];
  // std::string contentEncoded = requestBody["content"].dump();

  // std::string key = std::to_string(Token::token2sharedKey[token]);
  std::string key = "13";
  // content = AESTool::AES_decrypt(content, key);
  // userName = AESTool::AES_decrypt(userName, key);

  auto t =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  // 转为字符串
  std::stringstream ss;
  // 格式化
  ss << std::put_time(std::localtime(&t), "%Y年%m月%d日%H时%M分%S秒");

  std::string str_time = ss.str();

  Messages::addMessage(userName, content, str_time);

  json["status"] = "success";
  
  res.set_content(json.dump(), "application/json");
}

std::string dump_headers(const httplib::Headers &headers) {
  std::string s;
  char buf[BUFSIZ];

  for (auto it = headers.begin(); it != headers.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}

std::string log(const httplib::Request &req, const httplib::Response &res) {
  std::string s;
  char buf[BUFSIZ];

  s += "================================\n";

  snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
           req.version.c_str(), req.path.c_str());
  s += buf;

  std::string query;
  for (auto it = req.params.begin(); it != req.params.end(); ++it) {
    const auto &x = *it;
    snprintf(buf, sizeof(buf), "%c%s=%s",
             (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
             x.second.c_str());
    query += buf;
  }
  snprintf(buf, sizeof(buf), "%s\n", query.c_str());
  s += buf;

  s += dump_headers(req.headers);

  s += "--------------------------------\n";

  snprintf(buf, sizeof(buf), "%d %s\n", res.status, res.version.c_str());
  s += buf;
  s += dump_headers(res.headers);
  s += "\n";

  if (!res.body.empty()) {
    s += res.body;
  }

  s += "\n";

  return s;
}