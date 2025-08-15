SRC_DIR := src
INC_DIR := include

OBJ_DIR := obj
OBJ_DIR_TEST := obj_test
 
TEST_DIR := test
BUILD_DIR := build

CXX	:= clang++

CXXFLAGS := -Wall -Wextra -std=c++20 -I$(INC_DIR) -c
CXXFLAGS_TEST := -Wall -Wextra -std=c++20 -I$(INC_DIR)

LIB_NAME := mylib.a

HDRS := $(wildcard $(INC_DIR)/*.hpp)

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

SRCS_TEST := $(wildcard $(TEST_DIR)/*.cpp)

TEST_BINS := $(SRCS_TEST:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%)

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS) $(HDRS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

format:
	clang-format -i -style='{BasedOnStyle: Microsoft, IndentAccessModifiers: true, AccessModifierOffset: 0, IndentWidth: 4}' $(SRCS) $(HDRS)

$(BUILD_DIR)/%: $(TEST_DIR)/%.cpp $(LIB_NAME)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS_TEST) $< -L. -l:$(LIB_NAME) -o $@

test: $(TEST_BINS)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_DIR_TEST) $(BUILD_DIR) $(LIB_NAME)

.PHONY: all clean format test