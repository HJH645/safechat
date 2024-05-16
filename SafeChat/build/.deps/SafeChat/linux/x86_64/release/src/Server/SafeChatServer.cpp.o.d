{
    files = {
        "src/Server/SafeChatServer.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-isystem",
            "/home/zhy/.xmake/packages/c/cryptopp/8.9.0/9c19a519fd66433683eed4f0bbb0df1a/include",
            "-isystem",
            "/home/zhy/.xmake/packages/c/cpp-httplib/0.15.3/10d0838bab72482e8b727994616a9af6/include",
            "-isystem",
            "/home/zhy/.xmake/packages/n/nlohmann_json/v3.11.3/ec1183311a224b34b5c138edda96fdde/include"
        }
    },
    depfiles_gcc = "SafeChatServer.o: src/Server/SafeChatServer.cpp  src/Server/./SafeChatServer.h src/Server/../Config/Config.h  src/Server/../Entity/Messages.h src/Server/../Token/Token.h  src/Server/../Utils/AESTools.h\
"
}