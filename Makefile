CXX	:= clang++
CXXFLAGS := -Wall -Wextra -std=c++17 -I$(INCDIR) -c

LIBNAME := libmylib.a

SRCDIR := src
INCDIR := include
OBJDIR := obj

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	ar rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR) $(LIBNAME)

.PHONY: all clean
