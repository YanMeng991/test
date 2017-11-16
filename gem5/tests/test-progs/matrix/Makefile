ARGS=
CFLAGS=-g -Wall -Werror

matrix:
	gcc matrix.c -o matrix.o ${CFLAGS} ${ARGS}

matrix-inst:
	gcc matrix.c ../../../util/m5/m5op_x86.S -I../../../util/m5 -o matrix.o ${CFLAGS} ${ARGS}

clean:
	rm *.o
