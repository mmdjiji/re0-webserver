// tcp.c
// This file is a part of re0-webserver project.
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji/re0-webserver
// License: GPL v3.0
// Author's Blog: https://mmdjiji.com

#include "tcp.h"

void sig_handler(int sig) {
  if(sig == SIGINT) {
    closesocket(socketServer);
    WSACleanup();
    printf("[Info] Close socket listening.\r\n");
    exit(0);
  }
}

int tcp(server_config *config) {
  WSADATA wsaData;
  SOCKADDR_IN addrServer;
  SOCKET socketClient;
  SOCKADDR_IN addrClient;

  int addrlen = sizeof(SOCKADDR);
  char recvBuf[RECV_BUFFER_LENGTH];
  char *sendBuf;

  WSAStartup(MAKEWORD(2, 2), &wsaData);
  socketServer = socket(AF_INET, SOCK_STREAM, 0);
  addrServer.sin_addr.S_un.S_addr = inet_addr(config->local_ip);
  addrServer.sin_family = AF_INET; // IPv4
  addrServer.sin_port = htons(config->local_port);
  bind(socketServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
  
  if(listen(socketServer, BACKLOG_LENGTH) == 0) {
    printf("[Info] Start to listen %s:%d\r\n", config->local_ip, config->local_port);
    signal(SIGINT, sig_handler);
    while(1) {
      socketClient = accept(socketServer, (SOCKADDR*)&addrClient, &addrlen);
      if(socketClient != -1) {
        recv(socketClient, recvBuf, RECV_BUFFER_LENGTH, 0);
        char *abstract = http_abstract(recvBuf);
        printf("[Request] (%s:%d) %s\r\n", inet_ntoa(addrClient.sin_addr), ntohs(addrClient.sin_port), abstract);
        free(abstract);
        sendBuf = http_process(recvBuf, config);
        if(sendBuf) {
          send(socketClient, sendBuf, strlen(sendBuf), 0);
        }
        closesocket(socketClient);
      }
    }
  } else {
    printf("[Error] Cannot listen %s:%d.\r\n", config->local_ip, config->local_port);
  }
  return 0;
}
