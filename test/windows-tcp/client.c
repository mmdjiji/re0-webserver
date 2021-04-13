#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <stdio.h>
#include <stdlib.h>

#define CONNECT_IP ("127.0.0.1")
#define CONNECT_PORT (8080)

int main() {
  WSADATA wsaData;
  SOCKET client;
  SOCKADDR_IN remoteServer;
  char message[128] = "Hello Socket!";

  WSAStartup(MAKEWORD(2, 2), &wsaData);
  client = socket(AF_INET, SOCK_STREAM, 0);
  remoteServer.sin_addr.S_un.S_addr = inet_addr(CONNECT_IP);
  remoteServer.sin_family = AF_INET; // IPv4
  remoteServer.sin_port = htons(CONNECT_PORT);
  connect(client, (SOCKADDR*)&remoteServer, sizeof(SOCKADDR));

  send(client, message, strlen(message)+1, 0);
  printf("[Send] %s\r\n", message);
  recv(client, message, 128, 0);
  printf("[Received] %s\r\n", message);

  closesocket(client);
  WSACleanup();
  system("pause");
  return 0;
}
