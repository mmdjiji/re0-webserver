// main.c
// This file is a part of re0-webserver project.
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji/re0-webserver
// License: GPL v3.0
// Author's Blog: https://mmdjiji.com

#include <stdio.h>

#include "config.h"
#include "tcp.h"

int main() {
  server_config *config = NULL;

  printf("[Info] Welcome to re0-webserver!\r\n");
  printf("[Info] GitHub: https://github.com/mmdjiji/re0-webserver\r\n");
  printf("[Info] Author: mmdjiji (JiJi).\r\n");
  printf("[Info] Author's Blog: https://mmdjiji.com\r\n");

  if((config = read_config()) != NULL) {
    return tcp(config);
  }
  return 0;
}
