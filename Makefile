CC=gcc
CFLAGS=-Wall -static-libgcc -g -std=c99
MACROS=-D MAKEFILECOMPILE
INCLUDES=./headers
SRC=./src
TEST=./test
TEST_OUT=$(TEST)/out
BUILD_D=./build/debug
BUILD_R=./build/release
OBJECTS=./objects
AR=ar



all: create_dir basex.a
	
test: create_test_out_dir base64_test.o base32_test.o
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) $(OBJECTS)/base64_test.o $(BUILD_D)/basex.a -o $(TEST_OUT)/base64_test
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) $(OBJECTS)/base32_test.o $(BUILD_D)/basex.a -o $(TEST_OUT)/base32_test

create_test_out_dir:
	mkdir -p $(TEST_OUT)

create_dir:
	mkdir -p $(OBJECTS)
	mkdir -p $(BUILD_D)
	mkdir -p $(BUILD_R)


install: base64.o base32.o
	$(AR) -rcs $(BUILD_R)/basex.a $(OBJECTS)/base64.o $(OBJECTS)/base32.o
	$(CC) $(MACROS) -fPIC -O2 -shared -o $(BUILD_R)/libbasex.so $(OBJECTS)/base64.o $(OBJECTS)/base32.o && strip $(BUILD_R)/libbasex.so


basex.a: base64.o base32.o
	$(AR) -rc $(BUILD_D)/basex.a $(OBJECTS)/base64.o $(OBJECTS)/base32.o
	$(CC) $(MACROS) -fPIC -O2 -shared -o $(BUILD_D)/libbasex.so $(OBJECTS)/base64.o $(OBJECTS)/base32.o

base64.o: $(SRC)/base64.c
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) -c $(SRC)/base64.c -o $(OBJECTS)/base64.o

base64_test.o: $(TEST)/base64_test.c
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) -c $(TEST)/base64_test.c -o $(OBJECTS)/base64_test.o

base32.o: $(SRC)/base32.c
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) -c $(SRC)/base32.c -o $(OBJECTS)/base32.o

base32_test.o: $(TEST)/base32_test.c
	$(CC) $(CFLAGS) $(MACROS) -I$(INCLUDES) -c $(TEST)/base32_test.c -o $(OBJECTS)/base32_test.o


clean:
	rm -rf $(OBJECTS)/*.o
	rm -rf $(BUILD_R)/*.a
	rm -rf $(BUILD_D)/*.a
	rm -rf $(BUILD_D)/*.dll	
	rm -rf $(BUILD_D)/*.so
	rm -rf $(BUILD_R)/*.dll
	rm -rf $(BUILD_R)/*.so
	rm -rf $(TEST_OUT)/*