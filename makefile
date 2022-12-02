CC = clang++
CFLAGS = -std=c++11
SOURCES = img_to_ascii.cpp
LDFLAGS =

all:
	$(CC) $(CFLAGS) $(SOURCES) -o t 