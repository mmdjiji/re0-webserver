// config.c
// This file is a part of re0-webserver project.
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji/re0-webserver
// License: GPL v3.0
// Author's Blog: https://mmdjiji.com

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *read_json() {
  FILE *config_file = fopen(CONFIG_PATH, "r");
  int file_size;
  if(config_file) {
    fseek(config_file, 0L, SEEK_END);
    file_size = ftell(config_file);
    char *retval = (char *)malloc(file_size * sizeof(char));
    memset(retval, 0, file_size * sizeof(char));
    fseek(config_file, 0, SEEK_SET);
    fread(retval, file_size, 1, config_file);
    fclose(config_file);
    return retval;
  }
  return NULL;
}

int write_json(char * src) {
  FILE *config_file = fopen(CONFIG_PATH, "w");
  if(config_file) {
    fprintf(config_file, "%s", src);
    fclose(config_file);
    return 1;
  }
  return 0;
}

const char *read_field_string(cJSON *src, const char *string) {
  cJSON *result = cJSON_GetObjectItem(src, string);
  return result->valuestring;
}

int read_field_int(cJSON *src, const char *string) {
  cJSON *result = cJSON_GetObjectItem(src, string);
  return result->valueint;
}

server_config *read_config() {
  server_config *retval = (server_config *) malloc(sizeof(server_config));
  const char *config_file = read_json();
  
  if(config_file) {
    cJSON *config = cJSON_Parse(config_file);
    if(config) {
      strcpy(retval->local_ip, read_field_string(config, "local_ip"));
      retval->local_port = read_field_int(config, "local_port");
      strcpy(retval->root, read_field_string(config, "root"));
      strcpy(retval->index, read_field_string(config, "index"));
      strcpy(retval->access_log, read_field_string(config, "access_log"));
      printf("[Info] Read config.json successfully.\r\n");
      return retval;
    } else {
      printf("[Error] Cannot parse config.json correctly.\r\n");
      return NULL;
    }
  } else {
    printf("[Info] config.json does not exist, try to create it.\r\n");
    strcpy(retval->local_ip, "0.0.0.0");
    retval->local_port = 80;
    strcpy(retval->root, "htdocs");
    strcpy(retval->index, "index.html");
    strcpy(retval->access_log, "access.log");

    cJSON *config = cJSON_CreateObject();
    cJSON *config_local_ip = cJSON_CreateString(retval->local_ip);
    cJSON *config_local_port = cJSON_CreateNumber(retval->local_port);
    cJSON *config_root = cJSON_CreateString(retval->root);
    cJSON *config_index = cJSON_CreateString(retval->index);
    cJSON *config_access_log = cJSON_CreateString(retval->access_log);

    cJSON_AddItemToObject(config, "local_ip", config_local_ip);
    cJSON_AddItemToObject(config, "local_port", config_local_port);
    cJSON_AddItemToObject(config, "root", config_root);
    cJSON_AddItemToObject(config, "index", config_index);
    cJSON_AddItemToObject(config, "access_log", config_access_log);

    if(write_json(cJSON_Print(config)) == 1) {
      printf("[Info] Create config.json successfully.\r\n");
      return retval;
    } else {
      printf("[Error] Cannot create config.json.\r\n");
      return NULL;
    }
  }
}
