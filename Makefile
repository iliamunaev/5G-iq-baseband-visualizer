APP := iq_app
CPP := g++
CXXFLAGS := -std=c++23 -O2 -Wall -Wextra -Iinclude
SRCS := src/main.cpp src/calculatePoint.cpp
OBJDIR := obj
OBJS := $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean fclean

all: $(APP)

$(APP): $(OBJS)
	$(CPP) $(CXXFLAGS) $(OBJS) -o $(APP)

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CPP) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(APP)
	rm -rf build $(OBJDIR)
