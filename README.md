# Real Time Chat Application

## Overview
This project is a multi-threaded chat application developed in C++ using socket programming. It allows multiple clients to connect to a server, enabling real-time communication between them. The server handles client connections and facilitates messaging between clients. The project demonstrates core concepts of networking, concurrency, and inter-process communication using C++.

## Features
- Real-time, bi-directional messaging between a server and clients.
- Multi-threading to allow simultaneous message sending and receiving.
- Client and server can communicate without waiting for a response, enabling asynchronous messaging.
- Basic error handling and graceful disconnection detection.

## Technologies Used
- C++: Core language for socket programming.
- WinSock2: Windows sockets API for handling network connections.
- Multi-threading: Used to handle simultaneous sending and receiving of messages.

## How It Works
- The server creates a socket, binds it to a port, and listens for incoming connections from clients. When a client connects, the server accepts the connection and creates a new thread for handling messages from that client.
- The client connects to the server by specifying the server’s IP address and port. Once connected, the client can send messages to the server and receive responses asynchronously.

## Prerequisites
- Windows Operating System: This project uses Windows' WinSock2 API.
- MSYS2/MinGW or Visual Studio: To compile and run the C++ code.
- C++ Compiler: g++ (MinGW) or cl (Visual Studio).

## Future Improvements
- Add encryption for secure messaging (e.g., using SSL/TLS).
- Implement a user authentication system (username and password).
- Allow multiple clients to connect and broadcast messages to all connected clients.
- Add a GUI for a better user experience.

## Troubleshooting
- Connection Issues: Ensure that both the server and client are using the same IP address and port number. Check firewall settings to allow communication through the specified port.
- WinSock Errors: Ensure that WSAStartup() is called correctly and the correct socket options are used.
