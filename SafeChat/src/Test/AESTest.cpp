#include <iostream>
#include "../Utils/AESTools.h"

class AESTest{
    void run(){
     
    std::string str1 = "Hello, World!";


    std::string key="111";


    auto res =AESTool::AES_encrypt(str1,key);
    auto res2 = AESTool::AES_decrypt(res,key);
    
    std::cout<<"加密内容"<<std::endl;
    std::cout << str1 << std::endl;
    std::cout<<"加密密钥"<<std::endl;
    std::cout<<key<<std::endl;

    std::cout<<"加密结果"<<std::endl;
    std::cout<<res<<std::endl;
    
    std::cout<<"复原结果"<<std::endl;
    std::cout<<res2<<std::endl;
    
    }
};