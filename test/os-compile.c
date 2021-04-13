// os-compile.c
// Author: mmdjiji (JiJi)
// GitHub: https://github.com/mmdjiji
// Blog: https://mmdjiji.com

#include <stdio.h>

int main() {

  #ifdef __ANDROID__
    printf("Compiled on Android system.\r\n");
  #elif __linux__
    printf("Compiled on Linux system.\r\n");
  #elif _WIN32
    printf("Compiled on Windows system.\r\n");
  #else
    printf("Cannot detect compile system.\r\n");
  #endif
  
  return 0;
}