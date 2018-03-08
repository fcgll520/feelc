GFS_SOURCE_PATH=$(shell pwd)/../..
SEARCH_LIB_SOURCE_HOME=$(GFS_SOURCE_PATH)/lib

include $(SEARCH_LIB_SOURCE_HOME)/makefile.incl

API_OBJS = condition.o  fast_mutex.o    monitor.o    thread.o 


SOCK_CLIENT_OBJS=sock_client.o

API_LIB=$(DIR_LIBRARY)/libxthread.a
API_INCLUDES:=$(wildcard ./*.h ./*.hpp)

SOCK_SERVER=sock_server
SOCK_CLIENT=sock_client

.PHONEY = all clean install unstall

all: $(API_LIB)

$(API_LIB): $(API_OBJS)
	$(AR) $@ $^
$(SOCK_CLIENT):$(SOCK_CLIENT_OBJS)
	$(CXX)  $(CXXFLAGS) -o $@  $^ -L.  -lniosocket
clean:
	$(RM) $(API_LIB) $(API_OBJS)
install:
	$(CP) -f $(API_LIB)  /usr/local/lib
	mkdir -p /usr/local/include/xthread/
	$(CP) -f $(API_INCLUDES) /usr/local/include/xthread/
unstall:
	rm -rf /usr/local/lib/libxthread.a
	rm -rf /usr/local/include/xthread/
