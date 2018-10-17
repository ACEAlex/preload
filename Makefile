
CFLAGS += -O2 -ggdb -Wall
LDFLAGS += -Wl,--no-as-needed -rdynamic
SO_FLAGS := -ggdb -Wall -fPIC -shared -Wl,--no-as-needed -ldl

all: testprog
	gcc $(SO_FLAGS) -o haxer.so haxer.c

run: all
	LD_PRELOAD=./haxer.so ./testprog

investigate: all
	readelf --dyn-syms testprog

clean:
	rm testprog
	rm haxer.so