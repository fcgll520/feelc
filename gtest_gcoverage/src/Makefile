CC = g++

DIR_INC = ./include
DIR_SRC = .

SRC := $(wildcard ${DIR_SRC}/*.cpp)
SRC += $(wildcard ${DIR_SRC}/add/*.cpp)
SRC += $(wildcard ${DIR_SRC}/sub/*.cpp)

OBJ = $(patsubst %.cpp,%.o,${SRC})

TARGET = main
BIN_TARGET = ${TARGET}

CFLAGS = -g -O2 -Wall

${BIN_TARGET} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ}  -o $@

$(OBJ):%.o:%.cpp
	${CC} ${CFLAGS} -c $< -o $@

.PHONY : clean run
clean:
	-rm -rf ${BIN_TARGET} ${OBJ}

run:
	${BIN_TARGET}