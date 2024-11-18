#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>


#pragma comment(lib,"ws2_32.lib")

SOCKET acceptSocket;

void receiveMessages() {
    char receiveBuffer[200];
    while (true) {
        int byteCount = recv(acceptSocket, receiveBuffer, sizeof(receiveBuffer), 0);
        if (byteCount <= 0) {
            std::cout << "Client Disconnected or Error: " << WSAGetLastError() << std::endl;
            break;
        }
        receiveBuffer[byteCount] = '\0'; // Null-terminate the received string
        std::cout << "Client: " << receiveBuffer << std::endl;
    }
}

int main(){
    
    WSADATA data;
    int wsaerr = WSAStartup(MAKEWORD(2,2), &data);
    if(wsaerr!=0){
        std::cout<<"Failed to initialize Winsock"<<std::endl;
        return 1;
    }
    else{
        std::cout<<"WinSock Status : "<<data.szSystemStatus<<std::endl;
    }

    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);


    if(serverSocket == INVALID_SOCKET){
        std::cout<<"Error Creating Socket : "<<WSAGetLastError()<<std::endl;
        WSACleanup();
        return 1;
    }
    else{
        std::cout<<"Socket Status : OK"<<std::endl;
    }

    int port = 55555;
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET,_T("127.0.0.1"), &service.sin_addr);
    service.sin_port = htons(port);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
        std::cout<<"Bind Failed : "<<WSAGetLastError()<<std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else{
        std::cout<<"Bind OK"<<std::endl;
    }

    if (listen(serverSocket, 4) == SOCKET_ERROR){
        std::cout<<"Listen failed : "<<WSAGetLastError()<<std::endl;
    }
    else{
        std::cout<<"Listen OK"<<std::endl;
    }
    
    std::cout<<"Server Listening in Port "<<port<<std::endl;
    std::cout<<"Waiting for Connection...."<<std::endl;

    acceptSocket;
    acceptSocket = accept(serverSocket, nullptr, nullptr);
    if(acceptSocket == INVALID_SOCKET){
        std::cout<<"Accept Failed : "<<WSAGetLastError()<<std::endl;
        WSACleanup();
        return 1;
    }

    std::cout<<"Connection Accepted"<<std::endl;

    
    std::thread receiverThread(receiveMessages);

    std::string replyMessage;
    while (true) {
        
        std::getline(std::cin, replyMessage);
        if (replyMessage == "exit") break;
        send(acceptSocket, replyMessage.c_str(), replyMessage.size(), 0);
    }


    // system("pause");
    closesocket(acceptSocket);
    closesocket(serverSocket);
    receiverThread.join();
    WSACleanup();
}