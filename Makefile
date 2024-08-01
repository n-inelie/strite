TARGET := strite

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

$(shell mkdir -p $(BUILD_DIR))

CC := clang
C_FLAGS := -Wall -Werror -Wextra -Wpedantic -std=c23
INCLUDE_FLAGS := -I$(INCLUDE_DIR)
LIB_FLAGS := -lm -lncurses -L.

sources := $(wildcard $(SRC_DIR)/*.c)
objects := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(sources))

$(TARGET): $(objects)
	$(CC) $(C_FLAGS) $(INCLUDE_FLAGS) $(LIB_FLAGS) -fuse-ld=mold $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(C_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

.PHONY: clean debug optimize

clean:
	rm -rf $(TARGET) $(BUILD_DIR)

DEBUG_FLAGS := -glldb
debug: C_FLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

OPTIMIZE_FLAGS := -O3
optimize: C_FLAGS += $(OPTIMIZE_FLAGS)
optimize: $(TARGET)
