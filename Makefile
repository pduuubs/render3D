# Definition des variables :
CC = c++
EXEC = render
DEBUG = no
OBJ = main.o
FILES = main.cpp
HEADERS =

ifeq ($(DEBUG), yes)
	CFLAGS = -g -W -Wall
else
	CFLAGS =
endif

all: bin main.o
	${CC} ./bin/${OBJ} -o ${EXEC} ${CFLAGS}

bin:
	mkdir -p bin

main.o : ./src/${FILES}
	${CC} -c ./src/${FILES} -o ./bin/${OBJ}

clean:
		rm -rf ./bin/*.o

mrpropre:
		rm -rf bin
		rm render
