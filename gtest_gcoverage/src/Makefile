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
	@echo 链接生成文件目标文件
	${CC} ${CFLAGS} ${OBJ}  -o $@

$(OBJ):%.o:%.cpp
	@echo "Compiling $< ==> $@"
	${CC} ${CFLAGS} -c $< -o $@

.PHONY : clean run
clean:
	@echo 删除编译结果文件
	-rm -rf ${DIR_SRC}/*.o ${BIN_TARGET}

run:
	@echo 执行文件
	${BIN_TARGET}