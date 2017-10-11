UV_PATH=$(shell pwd)/libuv
UV_LIB=$(UV_PATH)/.libs/libuv.a
CFLAGS=-g -Wall -I$(UV_PATH)/include
LIBS=

uname_S=$(shell uname -s)

ifeq (Darwin, $(uname_S))
	CFLAGS+=-framework CoreServices
endif

ifeq (Linux, $(uname_S))
	LIBS=-lrt -ldl -lm -pthread
endif

uvcat: uvcat.c
	gcc $(CFLAGS) -o uvcat uvcat.c $(UV_LIB) $(LIBS)

uvtee: uvtee.c
	gcc $(CFLAGS) -o uvtee uvtee.c $(UV_LIB) $(LIBS)
