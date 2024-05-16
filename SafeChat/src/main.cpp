#include <iostream>
#include <string>
#include "./Utils/AESTools.h"
#include "./Test/HttpTest.cpp"
#include "./Test/AESTest.cpp"
#include "./Server/SafeChatServer.h"

int main() {
    // HttpTest Test;
    // Test.run();

    SafeChatServer server(8081);
    server.start();
    return 0;
}
