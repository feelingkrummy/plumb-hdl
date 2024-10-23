CC = clang-14
AR = llvm-ar-14

CC_FLAGS = --std=c11

OBJ_DIR=build/objs
LIB_DIR=build/libs

#
# Plumb Elab Lib
#
PLUMB_ELAB_OBJS=$(addprefix $(OBJ_DIR)/plumb_elab/,lex.o tokens.o)

plumb_elab: $(LIB_DIR)/libplumb_elab.a $(LIB_DIR)/libcommon.a

# Build Plumb Elab static lib
$(LIB_DIR)/libplumb_elab.a : $(PLUMB_ELAB_OBJS) | $(LIB_DIR)
	$(AR) rc $(LIB_DIR)/libplumb_elab.a $(PLUMB_ELAB_OBJS)

# Build Plumb Elab Object Files
$(OBJ_DIR)/plumb_elab/%.o : src/plumb_elab/%.c include/plumb_elab/%.h | $(OBJ_DIR)/plumb_elab
	$(CC) $(CC_FLAGS) -c -Iinclude/ $< -o $@

# Create directory for plumb elab object files
$(OBJ_DIR)/plumb_elab: | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/plumb_elab

#
# Common Lib
#
COMMON_OBJS=$(addprefix $(OBJ_DIR)/common/,kassert.o str.o utf8.o) \
			$(addprefix $(OBJ_DIR)/common/mem_,arena.o mem.o)

common: $(LIB_DIR)/libcommon.a

# Build Common static lib
$(LIB_DIR)/libcommon.a : $(COMMON_OBJS) | $(LIB_DIR)
	$(AR) rc $(LIB_DIR)/libcommon.a $(COMMON_OBJS)

# Build Common Object Files
$(OBJ_DIR)/common/%.o : src/common/%.c include/common/%.h | $(OBJ_DIR)/common
	$(CC) $(CC_FLAGS) -c -Iinclude/ $< -o $@

$(OBJ_DIR)/common/mem_%.o : src/common/mem/%.c include/common/mem/%.h | $(OBJ_DIR)/common/mem
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
# 	mkdir -p build/exe

#
#
#
.PHONY: clean
clean:
	rm -r build/