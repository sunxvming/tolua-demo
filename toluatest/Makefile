TARGET = main
OBJ_PATH = objs
PREFIX_BIN =


CC = gcc
CPP = g++ -std=c++11
INCLUDES += -I./ -I./include 
LIBS = $(CRYPTOPP_LIB)  $(ROCKSDB_LIB) $(PROTOBUF_LIB) /usr/lib64/libpthread.so 

G = -g
CFLAGS :=-Wall  $(G) 
LINKFLAGS = -L./lib -ltolua -llua -ldl -lm


SRCDIR =. ./src

C_SRCDIR = $(SRCDIR)
C_SOURCES = $(foreach d,$(C_SRCDIR),$(wildcard $(d)/*.c) )
C_OBJS = $(patsubst %.c, $(OBJ_PATH)/%.o, $(C_SOURCES))
C_DEPEND = $(patsubst %.c, $(OBJ_PATH)/%.d, $(C_SOURCES))


CC_SRCDIR = $(SRCDIR)
CC_SOURCES = $(foreach d,$(CC_SRCDIR),$(wildcard $(d)/*.cc) )
CC_OBJS = $(patsubst %.cc, $(OBJ_PATH)/%.o, $(CC_SOURCES))
CC_DEPEND = $(patsubst %.cc, $(OBJ_PATH)/%.d, $(CC_SOURCES))


CPP_SRCDIR = $(SRCDIR)
CPP_SOURCES = $(foreach d,$(CPP_SRCDIR),$(wildcard $(d)/*.cpp) )
CPP_OBJS = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(CPP_SOURCES))
CPP_DEPEND = $(patsubst %.cpp, $(OBJ_PATH)/%.d, $(CPP_SOURCES))


default:genproto  compile

genproto:
	# sh ./tools/gen_proto.sh

$(C_OBJS):$(OBJ_PATH)/%.o:%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(CC_OBJS):$(OBJ_PATH)/%.o:%.cc
	$(CPP) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(CPP_OBJS):$(OBJ_PATH)/%.o:%.cpp
	$(CPP) -c $(CFLAGS) $(INCLUDES) $< -o $@


init:
	$(foreach d,$(SRCDIR), mkdir -p $(OBJ_PATH)/$(d);)


test:
	@echo "C_SOURCES: $(C_SOURCES)"
	@echo "C_OBJS: $(C_OBJS)"
	@echo "CPP_SOURCES: $(CPP_SOURCES)"
	@echo "CPP_OBJS: $(CPP_OBJS)"
	@echo "CC_SOURCES: $(CC_SOURCES)"
	@echo "CC_OBJS: $(CC_OBJS)"

compile:$(C_OBJS) $(CC_OBJS) $(CPP_OBJS)
	$(CPP)  $^ -o $(TARGET)  $(LINKFLAGS) $(LIBS)

clean:
	rm -rf $(OBJ_PATH)
	rm -rf $(TARGET)
cleand:
	find ./objs -name *.d | xargs rm -rf

cleanall:subdirs_clean
	rm -rf $(OBJ_PATH)
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) $(PREFIX_BIN)

uninstall:
	rm -f $(PREFIX_BIN)/$(TARGET)

rebuild: clean compile




subdirs_clean:
	cd $(CRYPTOPP_DIR) && make clean
	cd $(ROCKSDB_DIR) && make clean
	cd $(PROTOBUF_DIR) && make clean



ifeq ($(MAKECMDGOALS),)
include $(CPP_DEPEND) init
endif

# $* 不带后缀的target
# $< target
# $@ depend
# $$xx  变量要用两个$$表示
# $$$$  进程号
# sed中的变量用 '"包围， 's,\('"$$BASESRC"'\)\.o[ :]*,\objs\/$*.o $@ : ,g'
$(CPP_DEPEND):$(OBJ_PATH)/%.d:%.cpp
	BASESRC=`basename $*`;\
	set -e; rm -f $@; \
	$(CPP) $(INCLUDES) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\('"$$BASESRC"'\)\.o[ :]*,\objs\/$*.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

