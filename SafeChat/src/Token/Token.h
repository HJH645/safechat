#include <string>
#include <unordered_map>

class Token{
private:
    
public:
    static std::unordered_map<std::string,int> token2sharedKey;
    static std::string getNewToken();
    static bool isValid(const std::string token);
    
};