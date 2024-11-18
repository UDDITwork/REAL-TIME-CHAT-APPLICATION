#include <iostream>
#include <string.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Tchar.h>
#include <thread>

#pragma comment(lib,"ws2_32.lib")

SOCKET clientSocket; 

void receiveMessages() {
    char receiveBuffer[200];
    while (true) {
        int byteCount = recv(clientSocket, receiveBuffer, sizeof(receiveBuffer), 0);
        if (byteCount <= 0) {
            std::cout << "Server Disconnected or Error: " << WSAGetLastError() << std::endl;
            break;
        }
        receiveBuffer[byteCount] = '\0';
        std::cout << "Server: " << receiveBuffer << std::endl;
    }
}

int main(){

    WSAData data;
    int wsaerr = WSAStartup(MAKEWORD(2,2),&data);
    if(wsaerr!=0){
        std::cout<<"Failed to initialize Winsock"<<std::endl;
        return 0;
    }
    else{
        std::cout<<"WinSock Status : "<<data.szSystemStatus<<std::endl;
    }

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET,SOCK_STREAM, 0);

    if(clientSocket==INVALID_SOCKET){
        std::cout<<"Socket Failed : "<<WSAGetLastError()<<std::endl;
        WSACleanup();
        return 1;
    }
    else{
        std::cout<<"Socket Status : OK"<<std::endl;
    }

    int port = 55555;
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET,_T("127.0.0.1"), &clientService.sin_addr);
    clientService.sin_port = htons(port);


    if(connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR){
        std::cout<<"Connet Failed : "<<WSAGetLastError()<<std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }
    else{
        std::cout<<"Connnet OK"<<std::endl;
    }

    std::thread receiverThread(receiveMessages);

    std::string message;
    while (true) {
        
        std::getline(std::cin, message);
        if (message == "exit") break;
        send(clientSocket, message.c_str(), message.size(), 0);
    }


    // system("pause");
    receiverThread.join();
    closesocket(clientSocket);
     
    WSACleanup();    
}