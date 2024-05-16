#include <string>
#include <vector>
struct AMessage {
  std::string userName;
  std::string content;
  std::string time;
  AMessage(std::string userName, std::string content, std::string time)
      : userName(userName), content(content), time(time) {}
};

class Messages {
private:
  static std::vector<AMessage> messages;

public:
  static bool addMessage(std::string userName, std::string content, std::string time);
  static std::vector<AMessage> getMessageList();
};
