CXX	:= clang++
CXXFLAGS := -Wall -Wextra -std=c++20 -I$(INCDIR) -c

LIBNAME := libmylib.a

SRCDIR := src
INCDIR := include
OBJDIR := obj

SRCS := $(wildcard $(SRCDIR)/*.cpp)
HDRS := $(wildcard $(INCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

format:
	clang-format -i -style='{BasedOnStyle: Microsoft, IndentAccessModifiers: true, AccessModifierOffset: 0, IndentWidth: 4}' $(SRCS) $(HDRS)

clean:
	rm -rf $(OBJDIR) $(LIBNAME)

.PHONY: all clean
