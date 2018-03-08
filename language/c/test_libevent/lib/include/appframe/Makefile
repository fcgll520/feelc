GFS_SOURCE_PATH=$(shell pwd)/../..
SEARCH_LIB_SOURCE_HOME=$(GFS_SOURCE_PATH)/lib

include $(SEARCH_LIB_SOURCE_HOME)/makefile.incl

API_OBJS =  pid_file.o mbstring.o timer.o config.o application.o config_impl.o \
            shared.o power2_allocator.o yun_allocator.o
API_LIB=$(DIR_LIBRARY)/libappframe.a

TEST_CONFIG=test_config
TEST_CONFIG_OBJS=test_config.o
API_INCLUDES:=$(wildcard ./*.h ./*.hpp)

.PHONEY = all clean install unstall

all: $(API_LIB) #$(TEST_CONFIG)


$(API_LIB): $(API_OBJS) 
	$(AR) $@ $^

$(TEST_CONFIG):$(TEST_CONFIG_OBJS) $(API_LIB)
	$(CXX)  $(CXXFLAGS) -o $@  $^ -L.  -lappframe
clean:
	$(RM) $(API_LIB) $(API_OBJS) $(TEST_CONFIG_OBJS) $(TEST_CONFIG)	
install:
	$(CP) -f $(API_LIB) /usr/local/lib
	mkdir -p /usr/local/include/appframe/
	#cp application.hpp bit_set.hpp circular_array_queue.hpp config.hpp confi_impl.hpp default_message_processor.hpp gb.h list.hpp mbstring.h object_pool_template.hpp pid_file.hpp sample_app.hpp shared_memory.hpp thread_channel.hpp timer.hpp timer_event_handler.hpp /usr/local/include/appframe/
	$(CP) -f $(API_INCLUDES) /usr/local/include/appframe/
unstall:
	rm -rf /usr/local/lib/libappframe.a
	rm -rf /usr/local/include/appframe/
