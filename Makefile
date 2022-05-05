OUT_DIR := build
SRC_DIR := src
CC := g++
# CFLAG := ???
# SRC := $(wildcard $(SRC_DIR)/*.c)

# remove test_parser to real source code in future
# https://sites.google.com/site/mymakefile/makefile-yu-fa-jian-jie

all: init format test_parser

# basic environment(commit message check, build dir)
init:
	@if [ ! -d $(OUT_DIR) ]; then \
		ln -sf ../../script/commit-msg .git/hooks/commit-msg || exit 1; \
		chmod +x .git/hooks/commit-msg; \
		mkdir $(OUT_DIR); \
	fi

format:
	@echo "format all files"
	@find ./$(SRC_DIR) -name '*.h' -or -name '*.hpp' -or -name '*.cpp' | xargs clang-format -i -style=file $1

clean:
	rm $(OUT_DIR)/*

test_parser: $(SRC_DIR)/test_parser.cpp init
	$(CC) -o $(OUT_DIR)/$@ $<
