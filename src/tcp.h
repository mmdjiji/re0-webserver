// tcp.h
// This file is a part of re0-webserver project.
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji/re0-webserver
// License: GPL v3.0
// Author's Blog: https://mmdjiji.com

#ifndef _TCP_H_
#define _TCP_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "config.h"
#include "http.h"

#define RECV_BUFFER_LENGTH (4096)
#define BACKLOG_LENGTH (256)

#ifdef __cpluscplus
extern "C" {
#endif

SOCKET socketServer;

void sig_handler(int sig);
int tcp(server_config *config);

#ifdef __cpluscplus
}
#endif

#endif // _TCP_H_
