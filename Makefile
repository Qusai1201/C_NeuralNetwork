C_SOURCES = $(wildcard matrix/*.c neural/*.c util/*.c graphics/*.c *.c)
HEADERS = $(wildcard matrix/*.h neural/*.h util/*.h graphics/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}
CFLAGS = -I/path/to/raylib/include -Wall -Wextra -Wpedantic -g  # Enable compiler warnings and debugging info
LDFLAGS = -L/path/to/raylib/lib
LIBS = -lraylib -lglfw -ldl -lpthread -lm -lrt -lX11

MAIN = main
CC = /usr/bin/gcc

run: ${MAIN}
	./${MAIN}

${MAIN}: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@ ${LDFLAGS} ${LIBS}

# Generic rules
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f matrix/*.o *.o neural/*.o util/*.o ${MAIN}
