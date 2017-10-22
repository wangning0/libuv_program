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

onchange: onchange.c
	gcc $(CFLAGS) -o onchange onchange.c $(UV_LIB) $(LIBS)

tcp-echo-server: tcp-echo-server.c
	gcc $(CFLAGS) -o tcp-echo-server tcp-echo-server.c $(UV_LIB) $(LIBS)

get-ip: get-ip.c
	gcc $(CFLAGS) -o get-ip get-ip.c $(UV_LIB) $(LIBS)

dns: dns.c
	gcc $(CFLAGS) -o dns dns.c $(UV_LIB) $(LIBS)

interfaces: interfaces.c
	gcc $(CFLAGS) -o interfaces interfaces.c $(UV_LIB) $(LIBS)

thread-create: thread-create.c
	gcc $(CFLAGS) -o thread-create thread-create.c $(UV_LIB) $(LIBS)

idle-basic: idle-basic.c
	gcc $(CFLAGS) -o idle-basic idle-basic.c $(UV_LIB) $(LIBS)

locks: locks.c
	gcc $(CFLAGS) -o locks locks.c $(UV_LIB) $(LIBS)

queue-work: queue-work.c
	gcc $(CFLAGS) -o queue-work queue-work.c $(UV_LIB) $(LIBS)

queue-cancel: queue-cancel.c
	gcc $(CFLAGS) -o queue-cancel queue-cancel.c $(UV_LIB) $(LIBS)

progress: progress.c
	gcc $(CFLAGS) -o progress progress.c $(UV_LIB) $(LIBS)