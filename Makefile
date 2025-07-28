CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11

build_folder = ../build

TARGET = $(build_folder)/cipher

cipher: $(TARGET)

$(TARGET): cipher.o
	$(CC) $(CFLAGS) -o $@ $<

cipher.o: cipher.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o

clang:
	clang-format -i *.c