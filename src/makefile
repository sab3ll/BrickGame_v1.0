# Variables
CORE			:=	$(shell uname -s | tr '[:upper:]' '[:lower:]')
CC				:=	gcc

# dirs
BIN_DIR			:=	bin
LIB_DIR			:=	lib
HISCORES_DIR	:=	misc/data
DOCS_DIR		:=	misc/docs
TESTS_DIR		:=	misc/tests
DIST_DIR		:=	misc/dist

SRC_DIR_FRNT	:=	gui/cli/src
OBJ_DIR_FRNT	:=	gui/cli/obj
INC_DIR_FRNT	:=	gui/cli/inc

SRC_DIR_BACK	:=	brick_game/tetris/src
OBJ_DIR_BACK	:=	brick_game/tetris/obj
INC_DIR_BACK	:=	brick_game/tetris/inc

SRC_DIR_SBOX	:=	sandbox/src
OBJ_DIR_SBOX	:=	sandbox/obj
INC_DIR_SBOX	:=	sandbox/inc

# src array
SRC_FILES_BACK	:=	$(wildcard $(SRC_DIR_BACK)/*.c)
SRC_FILES_FRNT	:=	$(wildcard $(SRC_DIR_FRNT)/*.c)
SRC_FILES_SBOX	:=	$(wildcard $(SRC_DIR_SBOX)/*.c)

# obj array
OBJ_FILES_BACK	:=	$(patsubst $(SRC_DIR_BACK)/%.c,$(OBJ_DIR_BACK)/%.o,$(SRC_FILES_BACK))
OBJ_FILES_FRNT	:=	$(patsubst $(SRC_DIR_FRNT)/%.c,$(OBJ_DIR_FRNT)/%.o,$(SRC_FILES_FRNT))
OBJ_FILES_SBOX	:=	$(patsubst $(SRC_DIR_SBOX)/%.c,$(OBJ_DIR_SBOX)/%.o,$(SRC_FILES_SBOX))

# flags
LDFLAGS 		:=	-lncurses \
					-lm
CFLAGS			:=	-Wall \
					-Werror \
					-Wextra \
					-Wpedantic \
					-std=c11
GCOVFLAGS		:=	-fprofile-arcs \
					-ftest-coverage

# targets
TETRIS_LIB		:=	tetris.a
RELEASE			:=	brick_game
DEBUG			:=	brick_game_debug

ifdef CORE
	ifeq ($(CORE), linux)
		CHECKFLAGS=-pthread -lcheck_pic -lrt -lm -lsubunit -lgsl -lgslcblas
	endif

	ifeq ($(CORE), darwin)
		CHECKFLAGS=$(shell pkg-config --cflags --libs check)
	endif
endif

$(shell mkdir -p $(BIN_DIR) $(LIB_DIR) $(OBJ_DIR_BACK) $(OBJ_DIR_FRNT) $(OBJ_DIR_SBOX))

# making tetris.a
$(TETRIS_LIB): $(OBJ_FILES_BACK) $(OBJ_FILES_FRNT)
	ar rcs $(LIB_DIR)/$(TETRIS_LIB) $(OBJ_FILES_BACK) $(OBJ_FILES_FRNT)

# making backend .obj files
$(OBJ_DIR_BACK)/%.o: $(SRC_DIR_BACK)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR_BACK) -c $< -o $@

# making frontend .obj files
$(OBJ_DIR_FRNT)/%.o: $(SRC_DIR_FRNT)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR_FRNT) -I $(INC_DIR_BACK) -c $< -o $@

# making sandbox .obj files
$(OBJ_DIR_SBOX)/%.o: $(SRC_DIR_SBOX)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR_SBOX) -I $(INC_DIR_BACK) -c $< -o $@

.PHONY: all install uninstall clean

all: install tetris.a dvi

install:
	make $(OBJ_FILES_BACK) $(OBJ_FILES_FRNT) $(OBJ_FILES_SBOX)
	$(CC) $(OBJ_FILES_BACK) $(OBJ_FILES_FRNT) $(OBJ_FILES_SBOX) $(LDFLAGS) -o $(BIN_DIR)/$(RELEASE)

uninstall:
	$(RM) $(BIN_DIR)/*

dvi:
	doxygen Doxyfile
	open $(DOCS_DIR)/html/index.html

test: $(TETRIS_LIB)
	$(CC) $(GLFLAGS) $(GCOVFLAGS) $(TESTS_DIR)/tetris_tests.c $(SRC_DIR_BACK)/* -I $(INC_DIR_BACK) -L. $(LIB_DIR)/$(TETRIS_LIB) $(CHECKFLAGS) -o $(TESTS_DIR)/output/tetris_tests
	$(TESTS_DIR)/output/tetris_tests

gcov_report: test
	lcov -o $(TESTS_DIR)/output/tests.info -c -d .
	genhtml -o $(TESTS_DIR)/report $(TESTS_DIR)/output/tests.info
	open $(TESTS_DIR)/report/index.html

dist: all
	cp -r brick_game gui lib sandbox Doxyfile makefile $(DIST_DIR)
	tar -czf tetris-1.0.tar.gz $(DIST_DIR)
clean:
	$(RM) $(OBJ_DIR_BACK)/* $(OBJ_DIR_FRNT)/* $(OBJ_DIR_SBOX)/* $(BIN_DIR)/* $(LIB_DIR)/* $(HISCORES_DIR)/*
	$(RM) -rf $(DOCS_DIR)/* $(TESTS_DIR)/output/* $(TESTS_DIR)/report/* $(DIST_DIR)/*
	clear

clang:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name '*.c' -o -name '*.h' \) -print0 | xargs -0 clang-format -i
	rm .clang-format

cppcheck:
	find . -type f \( -name '*.c' -o -name '*.h' \) -print0 | \
	xargs -0 cppcheck --enable=all --suppress=missingIncludeSystem --force

valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes $(BIN_DIR)/$(RELEASE)

valgrind_deep:
	valgrind --leak-check=full --tool=memcheck --leak-check=full --show-reachable=yes \
	--leak-resolution=high --track-origins=yes --show-leak-kinds=all --verbose bin/brick_game
