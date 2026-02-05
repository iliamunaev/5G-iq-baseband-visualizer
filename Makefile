APP := viz_iq
CPP := g++
CXXFLAGS := -std=c++23 -O2 -Wall -Wextra -Iinclude

SRCS := src/main.cpp \
		src/calculatePoint.cpp \
		src/plotComplexSignalPoint.cpp

OBJDIR := obj
OBJS := $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean fclean re

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

re: fclean all
