// http.h
// This file is a part of re0-webserver project.
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji/re0-webserver
// License: GPL v3.0
// Author's Blog: https://mmdjiji.com

#ifndef _HTTP_H_
#define _HTTP_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <direct.h>
#include "config.h"

#define BUFFER_SIZE (4096)
#define PATH_SIZE (1024)
#define SYNC_SIZE (32)

#ifdef __cpluscplus
extern "C" {
#endif

int prefix_match(char *src, const char *model);

char *http_abstract(char *request);
char *http_process(char *request, server_config *config);

#ifdef __cpluscplus
}
#endif

#endif // _HTTP_H_
