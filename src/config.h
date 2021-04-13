// config.h
// This file is a part of re0-webserver project.
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji/re0-webserver
// License: GPL v3.0
// Author's Blog: https://mmdjiji.com

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "cJSON.h"

#ifdef __cpluscplus
extern "C" {
#endif

#define CONFIG_PATH ("config.json")

#define LOCAL_IP_MAXLEN (64)
#define ROOT_MAXLEN (64)
#define INDEX_MAXLEN (64)
#define ACCESS_LOG_MAXLEN (64)

typedef struct {
  char local_ip[LOCAL_IP_MAXLEN];
  unsigned short local_port;
  char root[ROOT_MAXLEN];
  char index[INDEX_MAXLEN];
  char access_log[ACCESS_LOG_MAXLEN];
} server_config;

const char *read_json();
const char *read_field_string(cJSON *src, const char *string);
int read_field_int(cJSON *src, const char *string);
server_config *read_config();

#ifdef __cpluscplus
}
#endif

#endif // _CONFIG_H_
