
COMPILER = clang
COMPILER_FLAGS = -g -Wall -Werror -Wextra
LINKER_FLAGS = -lncursesw -lm

PROG_NAME = log
SOURCE_FILES = $(wildcard ../src/*.c) \
     	       $(wildcard ../examples/*.c)

build:
	$(COMPILER) -o $(PROG_NAME) $(SOURCE_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS)
clean:
	rm $(PROG_NAME)
run:
	./$(PROG_NAME)
