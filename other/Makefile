SRC_DIR=./src
BIN_DIR=./bin
LIB_DIR=./lib
all:
	gcc -g3 ${SRC_DIR}/hello.c -o ${BIN_DIR}/hello
	gcc -g3 ${SRC_DIR}/server.c -o ${BIN_DIR}/server
	gcc -g3 ${SRC_DIR}/first_so.c -fPIC -shared -o ${LIB_DIR}/libfirst_so.so
	gcc -g3 ${SRC_DIR}/ldtest.c -o ${BIN_DIR}/ldtest -L./lib -lfirst_so -ldl
