CC=gcc
CFLAGS=-Wall -static-libgcc -g -std=c99
MACROS=-D MAKEFILECOMPILE
INCLUDES=./headers
BUILD_D=./build/debug
BUILD_R=./build/release
OBJECTS=./objects
AR=ar



all: create_dir test.o basex.a
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) $(OBJECTS)/test.o $(BUILD_D)/basex.a -o test.out 

create_dir:
	mkdir -p $(OBJECTS)
	mkdir -p $(BUILD_D)
	mkdir -p $(BUILD_R)


install: base64.o
	$(AR) -rcs $(BUILD_R)/basex.a $(OBJECTS)/base64.o
	$(CC) $(MACROS) -fPIC -O2 -shared -o $(BUILD_R)/libbasex.so $(OBJECTS)/base64.o && strip $(BUILD_R)/libbasex.so


basex.a: base64.o
	$(AR) -rc $(BUILD_D)/basex.a $(OBJECTS)/base64.o
	$(CC) $(MACROS) -fPIC -O2 -shared -o $(BUILD_D)/libbasex.so $(OBJECTS)/base64.o

base64.o: ./src/base64.c
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) -c ./src/base64.c -o $(OBJECTS)/base64.o

test.o: ./main.c
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) -c ./main.c -o $(OBJECTS)/test.o

clean:
	rm -rf $(OBJECTS)/*.o
	rm -rf $(BUILD_R)/*.a
	rm -rf $(BUILD_D)/*.a
	rm -rf $(BUILD_D)/*.dll	
	rm -rf $(BUILD_D)/*.so
	rm -rf $(BUILD_R)/*.dll
	rm -rf $(BUILD_R)/*.so
	rm -f test.*