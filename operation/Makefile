SRC=./src
BIN=./bin
all:
	cd ${SRC} && gcc -g3 -c ./*.c && gcc -g3 ./*.o -o ../${BIN}/main && cd ..
clean:
	rm -rf ${BIN}/*
	rm -rf ${SRC}/*.o
