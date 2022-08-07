#$gcc xeuclid.c -L.. -lcrypto  -I../include/crypto -o xeuclid
CC = gcc
TARGET = xeuclid
LDLIBS += -lcrypto

all: xeuclid

xeuclid: xeuclid.c

clean:
        rm -f xeuclid *.o