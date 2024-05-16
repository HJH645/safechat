#include "Messages.h"
#include <vector>

std::vector<AMessage> Messages::messages;

bool Messages::addMessage(std::string userName, std::string content,
                          std::string time) {
  AMessage newMessage(userName, content, time);
  Messages::messages.push_back(newMessage);
  return true;
}

std::vector<AMessage> Messages::getMessageList(){

  return messages;
}