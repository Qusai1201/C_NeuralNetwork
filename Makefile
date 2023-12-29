C_SOURCES = $(wildcard matrix/*.c neural/*.c util/*.c graphics/*.c *.c)
HEADERS = $(wildcard matrix/*.h neural/*.h util/*.h graphics/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}
CFLAGS = -I/path/to/raylib/include  # Include raylib headers
LDFLAGS = -L/path/to/raylib/lib     # Specify the directory containing raylib library
LIBS = -lraylib -lglfw -ldl -lpthread -lm -lrt -lX11

MAIN = main
CC = /usr/bin/gcc
LINKER = /usr/bin/ld

run: ${MAIN}
	./${MAIN}

main: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@ ${LDFLAGS} ${LIBS}

# Generic rules
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm matrix/*.o *.o neural/*.o util/*.o ${MAIN}
