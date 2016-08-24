SRC=./src
BIN=./bin
all:
	cd ${SRC} && gcc -g3 -c ./ser_*.c && gcc -g3 ./ser_*.o -o ../${BIN}/ser_main && cd ..
	cd ${SRC} && gcc -g3 -c ./cli_*.c && gcc -g3 ./cli_*.o -o ../${BIN}/cli_main && cd ..
clean:
	rm -rf ${BIN}/*
	rm -rf ${SRC}/*.o
