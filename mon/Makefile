SRC=./src
OUT_OPT=-o ./bin
OPT_LIB=-g3
OPT_BIN=-g3 -L./lib -lother

all:
	gcc ${OPT_LIB} ${SRC}/other.c --share -o ./lib/libother.so
	gcc ${OPT_LIB} ${SRC}/other.c ${SRC}/getcpu.c ${OUT_OPT}/getcpu
	gcc ${OPT_LIB} ${SRC}/other.c ${SRC}/getdisk.c ${OUT_OPT}/getdisk
