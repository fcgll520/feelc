CC      = gcc
CPP     = g++
RM      = rm -rf

## debug flag
DBG_ENABLE   = 1
CPPFLAGS = -w -Wall -D__STDC_FORMAT_MACROS -DLINUX -Wno-invalid-offsetof -DCU_USE_OTHER_DOWN_ENGINE -DUNIT_TEST
CPPFLAGS += -isystem -Wextra
CPPFLAGS += -fprofile-arcs -ftest-coverage
LINKERCXX = -fprofile-arcs -ftest-coverage


BASE_PATH := ..
MEDIA_PATH := $(BASE_PATH)/src
UT_PATH := ./src

## need libs, add at here
LIBS := rt ssl crypto pthread
LIBS += gtest gtest_main gmock_main
LIBS += gcov

## used headers  file path
INCLUDE_PATH := $(BASE_PATH)/output/include
INCLUDE_PATH += $(MEDIA_PATH)
INCLUDE_PATH += ./include

## used include librarys file path
LIBRARY_PATH := 

## debug for debug info, when use gdb to debug
ifeq (1, ${DBG_ENABLE}) 
    CPPFLAGS += -O0 -g
endif
ifeq (0, ${DBG_ENABLE}) 
    CPPFLAGS += -O3
endif

## get all include path
HEADERFLAGS := $(foreach dir, $(INCLUDE_PATH), -I$(dir))

## get all library path
LDFLAGS += $(foreach lib, $(LIBRARY_PATH), -L$(lib))

## get all librarys
LDFLAGS += $(foreach lib, $(LIBS), -l$(lib))

SRC_FILES := $(wildcard $(MEDIA_PATH)/add/*.cpp)
SRC_FILES += $(wildcard $(MEDIA_PATH)/sub/*.cpp)

SRC_FILES += $(wildcard ./$(UT_PATH)/add/*.cpp)
SRC_FILES += $(wildcard ./$(UT_PATH)/sub/*.cpp)

TARGET ?= run_test
PROJ_NAME= run_test

#SOURCES := $(wildcard $(SRC_PATH)/*.cpp $(SRC_PATH)/*.cc $(SRC_PATH)/*.c)
SOURCES := $(SRC_FILES)
OBJECTS := $(addsuffix .o,$(basename $(SOURCES)))

ifneq (v$(V),v1)
hide?=@
else
hide?=
endif

.PHONY : all clean hello build post-build

all: hello build post-build
clean:
	${RM} ${TARGET}
	find ${BASE_PATH} -name "*.o" -exec ${RM} -rf {} \;
	find ${BASE_PATH} -name "*.o.d" -exec ${RM} -rf {} \;
	find ${BASE_PATH} -name "*.gcno" -exec ${RM} -rf {} \;
	find ${BASE_PATH} -name "*.gcda" -exec ${RM} -rf {} \;
hello: ;@ echo ==== start compile $(PROJ_NAME), $(shell date) ====
post-build: ;@ echo ==== done compile $(PROJ_NAME), $(shell date) ====
build: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(info LD $@)
	$(hide) $(CPP) $(OBJECTS) ${LINKERCXX} $(LDFLAGS) -o $@

define make-cmd-cc
$2 : $1
	$$(info CPP $$<)
	$$(hide) $$(CPP) $$(CPPFLAGS) $$(HEADERFLAGS) -MMD -MT $$@ -MF $$@.d -c -fPIC -o $$@ $$<
endef

$(foreach afile,$(SOURCES),\
	$(eval $(call make-cmd-cc,$(afile),\
		$(addsuffix .o,$(basename $(afile))))))

