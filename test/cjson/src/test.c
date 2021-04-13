// test.c
// Test cJSON library
// Author: mmdjiji (JiJi)
// Blog: https://mmdjiji.com
// GitHub: https://github.com/mmdjiji

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"

#define JSON_PATH ("config.json")

const char *read_json() {
  FILE *fptr = fopen(JSON_PATH, "r");
  int file_size;
  if(fptr) {
    fseek(fptr, 0L, SEEK_END);
    file_size = ftell(fptr);
    char *retval = (char *)malloc(file_size * sizeof(char));
    memset(retval, 0, file_size * sizeof(char));
    fseek(fptr, 0, SEEK_SET);
    fread(retval, file_size, 1, fptr);
    fclose(fptr);
    return retval;
  }
  return NULL;
}

const char *read_field_string(cJSON *src, const char *string) {
  cJSON *result = cJSON_GetObjectItem(src, string);
  return result->valuestring;
}

int read_field_int(cJSON *src, const char *string) {
  cJSON *result = cJSON_GetObjectItem(src, string);
  return result->valueint;
}

int main() {
  printf("cJSON Version: %s\r\n", cJSON_Version());

  const char *config_src = read_json();
  cJSON *config = cJSON_Parse(config_src);

  // printf("%s\r\n", config_src);
  
  if(config) {
    printf("version=%s\r\n", read_field_string(config, "version"));
    printf("local_ip=%s\r\n", read_field_string(config, "local_ip"));
    printf("local_port=%d\r\n", read_field_int(config, "local_port"));
  } else {
    printf("parse failed.\r\n");
  }
  return 0;
}
