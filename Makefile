FLAGS=-ggdb -c

SOURCE_DIR := ./src
BUILD_DIR  := ./build

SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c)
BUILD_FILES  := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_FILES))

all: main

main: $(BUILD_FILES)
	gcc -ggdb -o main $^


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@)
	gcc $(FLAGS) -o $@ $<

clean:
	rm -rf main $(BUILD_DIR)

shared:
	gcc -fPIC -c mem.c
	gcc -shared -o mf.so -fPIC mem.o
