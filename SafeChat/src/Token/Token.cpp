#include "./Token.h"
#include <string>
#include <unordered_map>

std::string Token::getNewToken(){
    return "Valid";
}
std::unordered_map<std::string,int> Token::token2sharedKey;

bool Token::isValid(const std::string token){
    if(token=="Valid")return true;
    else return false;
}