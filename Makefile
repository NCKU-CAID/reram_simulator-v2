INST := instruction_input
OUT := out.log

OUT_DIR := build
SRC_DIR := src
TEST_DIR := test

CC := g++
CFLAG := -O2 -g -Wall -I

SRC := $(wildcard ./$(SRC_DIR)/*.cpp)
SRC2 := $(notdir $(SRC))
OBJ := $(SRC2:%.cpp=%.o)
# https://sites.google.com/site/mymakefile/makefile-yu-fa-jian-jie

test: all
	$(OUT_DIR)/reram_simulator < $(TEST_DIR)/$(INST) > $(OUT_DIR)/$(OUT)

all: init format $(OBJ)
	$(CC) -o $(OUT_DIR)/reram_simulator $(OUT_DIR)/$(OBJ)

# basic environment(commit message check, build dir)
init:
	@if [ ! -d $(OUT_DIR) ]; then \
		ln -sf ../../script/commit-msg .git/hooks/commit-msg || exit 1; \
		chmod +x .git/hooks/commit-msg; \
		mkdir $(OUT_DIR); \
	fi

format:
	@echo "format all files"
	@find . -name '*.h' -or -name '*.hpp' -or -name '*.cpp' | xargs clang-format -i -style=file $1

clean:
	rm $(OUT_DIR)/*

%.o: $(SRC_DIR)/%.cpp init
	$(CC) -o $(OUT_DIR)/$@ -c $(CFLAGS) $<
