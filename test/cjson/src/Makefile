TAR = test
OBJ = test.o cJSON.o
CC = gcc

$(TAR): $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^ -o $@
