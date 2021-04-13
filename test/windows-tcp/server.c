#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

#define LISTENING_PORT (8080)

SOCKET socketServer;

void sig_handler(int sig) {
  if(sig == SIGINT) {
    closesocket(socketServer);
    WSACleanup();
    printf("[Info] Exit.\r\n");
    exit(0);
  }
}

int main() {
  WSADATA wsaData;
  SOCKADDR_IN addrServer;
  SOCKET socketClient;
  SOCKADDR_IN addrClient;

  int len = sizeof(SOCKADDR);
  
  char recvBuf[1024];

  WSAStartup(MAKEWORD(2, 2), &wsaData);
  socketServer = socket(AF_INET, SOCK_STREAM, 0);
  addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 0.0.0.0
  addrServer.sin_family = AF_INET; // IPv4
  addrServer.sin_port = htons(LISTENING_PORT);
  bind(socketServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
  
  if(listen(socketServer, 128) == 0) {
    printf("[Info] Start listen on %d.\r\n", LISTENING_PORT);
    signal(SIGINT, sig_handler);
    while(1) {
      socketClient = accept(socketServer, (SOCKADDR*)&addrClient, &len);
      if(socketClient != -1) {
        int retv = recv(socketClient, recvBuf, 1024, 0);
        send(socketClient, recvBuf, strlen(recvBuf)+1, 0);
        closesocket(socketClient);
        printf("[Event] (%s:%d) %s.\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), recvBuf);
      }
    }
  } else {
    printf("[Error] Cannot listen 0.0.0.0:%d.\r\n", LISTENING_PORT);
  }
  
  return 0;
}
