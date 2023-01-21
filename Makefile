LIBJIT_PATH = /Users/amuthanmannan/Documents/personal/libjit
LIBJIT_INCLUDE_PATH = $(LIBJIT_PATH)/include
LIBJIT_LIB_PATH = $(LIBJIT_PATH)/jit/.libs
LIBJIT_AR = $(LIBJIT_LIB_PATH)/libjit.a

CC = gcc
LD = gcc
CCOPT = -g -O0
CCFLAGS = -c $(CCOPT)
LDFLAGS = -lpthread -lm -ldl


engine: engine.o hashmap.o
	$(LD) $^ $(LIBJIT_AR) $(LDFLAGS) -o $@

engine.o: engine.c
	$(CC) -I$(LIBJIT_INCLUDE_PATH) -I. $(CCFLAGS) $^ -o $@

hashmap.o: hashmap.c
	$(CC) -I$(LIBJIT_INCLUDE_PATH) -I. $(CCFLAGS) $^ -o $@

clean:
	rm -rf *.o engine 
