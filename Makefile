CC = clang-14
AR = llvm-ar-14

CC_FLAGS = --std=c11

OBJ_DIR=build/objs
LIB_DIR=build/libs

#
# Plumb Elab Lib
#
PLUMB_ELAB_OBJS=$(addprefix $(OBJ_DIR)/plumb-elab/,lex.o tokens.o)

plumb-elab: $(LIB_DIR)/libplumb-elab.a $(LIB_DIR)/libcommon.a

# Build Plumb Elab static lib
$(LIB_DIR)/libplumb-elab.a : $(PLUMB_ELAB_OBJS) | $(LIB_DIR)
	$(AR) rc $(LIB_DIR)/libplumb-elab.a $(PLUMB_ELAB_OBJS)

# Build Plumb Elab Object Files
$(OBJ_DIR)/plumb-elab/%.o : src/plumb-elab/%.c include/plumb-elab/%.h | $(OBJ_DIR)/plumb-elab
	$(CC) $(CC_FLAGS) -c -Iinclude/ $< -o $@

# Create directory for plumb elab object files
$(OBJ_DIR)/plumb-elab: | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/plumb-elab

#
# Common Lib
#
COMMON_OBJS=$(addprefix $(OBJ_DIR)/common/,kassert.o str.o utf8.o) \
			$(addprefix $(OBJ_DIR)/common/mem-,arena.o mem.o)

common: $(LIB_DIR)/libcommon.a

# Build Common static lib
$(LIB_DIR)/libcommon.a : $(COMMON_OBJS) | $(LIB_DIR)
	$(AR) rc $(LIB_DIR)/libcommon.a $(COMMON_OBJS)

# Build Common Object Files
$(OBJ_DIR)/common/%.o : src/common/%.c include/common/%.h | $(OBJ_DIR)/common
	$(CC) $(CC_FLAGS) -c -Iinclude/ $< -o $@

$(OBJ_DIR)/common/mem-%.o : src/common/mem/%.c include/common/mem/%.h | $(OBJ_DIR)/common/mem
	$(CC) $(CC_FLAGS) -c -Iinclude/ $< -o $@

# Create directory for plumb elab object files
$(OBJ_DIR)/common: | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/common

$(OBJ_DIR)/common/mem: | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/common/mem

# 
# Build Directory Stuff
#
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# .SILENT: build/exe
# build/libs:
#	mkdir -p build/exe

#
#
#
.PHONY: clean
clean:
	rm -r build/
