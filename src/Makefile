# Makefile
# This file is a part of re0-webserver project.
# Author: mmdjiji (JiJi)
# GitHub: https://github.com/mmdjiji/re0-webserver
# License: GPL v3.0
# Author's Blog: https://mmdjiji.com

TAR = re0-webserver
OBJ = cJSON.o config.o http.o tcp.o main.o
CC = gcc
CFLAGS = -lwsock32

$(TAR): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.c
	$(CC) -c $^ -o $@
