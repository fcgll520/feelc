CXX = g++ 

CFLAGS = -g -O0 -w -Wall

INC = -I./

RECV_BIN = recv
SEND_BIN = send

RECV_OBJS = recv.o 
SEND_OBJS = send.o 

LIB =

all: clean ${RECV_BIN} ${SEND_BIN} 

${SEND_BIN}: ${SEND_OBJS}
	${CXX} ${CFLAGS} -o ${SEND_BIN} ${SEND_OBJS} ${INC} ${LIB}

${RECV_BIN}: ${RECV_OBJS}
	${CXX} ${CFLAGS} -o ${RECV_BIN} ${RECV_OBJS} ${INC} ${LIB}

clean:
	-mv -f *.o /tmp/rm
	-mv -f ${RECV_BIN} /tmp/rm
	-mv -f ${SEND_BIN} /tmp/rm

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<
%.o: %.c
	$(CXX) $(CFLAGS) $(INC) -c -o $@ $<
