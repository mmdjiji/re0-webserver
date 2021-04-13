// http.c
// This file is a part of re0-webserver project.
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji/re0-webserver
// License: GPL v3.0
// Author's Blog: https://mmdjiji.com

#include "http.h"

int prefix_match(char *src, const char *model) {
  return (strncmp(src, model, strlen(model)) == 0);
}

char *http_abstract(char *request) {
  int i, abstract_len = 0;
  char *retval;
  if(prefix_match(request, "GET") || prefix_match(request, "POST") || prefix_match(request, "HEAD") || prefix_match(request, "PUT")) {
    while(1) {
      ++abstract_len;
      if(request[abstract_len] == 0x0d && request[abstract_len + 1] == 0x0a) break;
    }
    retval = (char *) malloc(sizeof(char) * abstract_len);
    for(i=0; i<abstract_len; ++i) {
      retval[i] = request[i];
    }
    retval[i] = '\0';
    return retval;
  }
  return NULL;
}

char *http_process(char *request, server_config *config) {
  int flag = -1;
  // flag = -1: be ready to parse first line.
  // flag =  0: get the line filed.
  // flag =  1: get the value.
  int subflag = 0;

  char *req_ptr;
  char uri[BUFFER_SIZE], field[BUFFER_SIZE], value[BUFFER_SIZE];
  char *uri_ptr = uri, *field_ptr = field, *value_ptr = value;

  char http_version[SYNC_SIZE];

  char path[PATH_SIZE];
  _getcwd(path, PATH_SIZE);

  static char response[BUFFER_SIZE];
  *response = '\0';

  FILE *rdfile;

  // printf("%s", request);
  
  for(req_ptr = request; flag != 2; ++req_ptr) {
    //printf("%s(%d)", req_ptr, flag);
    switch(flag) {
      case -1:
        if(*req_ptr == ' ') {
          *value_ptr = '\0';
          *uri_ptr = '\0';
          // process with value
          if(subflag == 0) {
            
            // printf("<%s>", value); // http method
          }
          value_ptr = value;
          ++subflag;
        } else if(subflag == 0) {
          *value_ptr++ = *req_ptr;
        } else if(subflag == 1) {
          *uri_ptr++ = *req_ptr;
        } else if(subflag == 2) {
          if(*req_ptr == 0x0d && *(req_ptr+1) == 0x0a) {
            *value_ptr = '\0';
            // printf("<%s>", value); // http version
            strcpy(http_version, value);
            value_ptr = value;
            ++req_ptr;
            flag = 0;
          } else {
            *value_ptr++ = *req_ptr;
          }
        }
        break;
      case 0:
        if(*req_ptr == ':') {
          ++req_ptr;
          *field_ptr = '\0';
          field_ptr = field;
          flag = 1;
        } else if(*req_ptr == 0x0d && *(req_ptr+1) == 0x0a) {
          ++req_ptr;
          flag = 2;
        } else {
          *field_ptr++ = *req_ptr;
        }
        break;
      case 1:
        if(*req_ptr == 0x0d && *(req_ptr+1) == 0x0a) {
          ++req_ptr;
          *value_ptr = '\0';
          // printf("%s=>%s\r\n", field, value);
          value_ptr = value;
          flag = 0;
        } else {
          *value_ptr++ = *req_ptr;
        }
        break;
      default:
        printf("[Error] An error occurred by http process state machine meet unexpected flag %d.\r\n", flag);
    }
  }
  
  strcat(path, "\\");
  strcat(path, config->root);
  
  for(uri_ptr = uri; *uri_ptr != '\0'; ++uri_ptr) {
    if(*uri_ptr == '/') {
      *uri_ptr = '\\';
    }
  }
  for(; uri_ptr != uri; --uri_ptr) {
    if(*uri_ptr == '?') {
      *uri_ptr = '\0';
      break;
    }
  }
  if(strcmp(uri, "\\") == 0) {
    strcat(uri, config->index);
  }
  strcat(path, uri);

  // printf("<%s>\r\n", path);
  // printf("(%s)\r\n", uri);

  strcat(response, http_version);
  strcat(response, " ");

  rdfile = fopen(path, "r");

  if(rdfile) {
    strcat(response, "200 OK\r\n");
  } else {
    strcat(response, "404 Not Found\r\n");
  }
  
  strcat(response, "Server: re0-webserver\r\n");
  strcat(response, "Connection: close\r\n");
  strcat(response, "Content-type: text/html\r\n");
  
  strcat(response, "\r\n");
  
  if(rdfile) {
    while(fgets(value, BUFFER_SIZE, rdfile) != NULL) {
      strcat(response, value);
    }
    fclose(rdfile);
  } else {
    strcpy(path, config->root);
    strcat(path, "\\404.html");
    rdfile = fopen(path, "r");
    if(rdfile) {
      while(fgets(value, BUFFER_SIZE, rdfile) != NULL) {
        strcat(response, value);
      }
      fclose(rdfile);
    }
  }

  return response;
}
