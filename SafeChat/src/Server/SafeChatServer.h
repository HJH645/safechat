#ifndef SAFECAHT_SEVER
#define SAFECAHT_SEVER

#include <cryptopp/cryptlib.h>
#include <cryptopp/dh.h>
#include <cryptopp/hex.h>
#include <httplib.h>
#include <string>



class SafeChatServer{
    public:
    SafeChatServer();
    SafeChatServer(int port);
    ~SafeChatServer();
    void start();

    private:
    int port;
    httplib::Server svr;

    //DH算法交换密钥
    //前端发来名字，公钥
    void swapDHKey(const httplib::Request& req, httplib::Response& res);
    
    // 用户凭借userName和加密的SHA256密码登录，返回是否成功，成功的话还返回DH加密参数
    void login(const httplib::Request& req, httplib::Response& res);
    //计算SHA256
    std::string sha256(const std::string& input);

    //获取加密的消息列表
    void getMessage(const httplib::Request& req, httplib::Response& res);

    //发送信息
    void sendMessage(const httplib::Request& req, httplib::Response& res);
};

#endif