CXX = g++
CXXFLAGS = -Wall -Wextra -I./$(INCLDIR)
LDFLAGS = 
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCDIR = src
INCLDIR = include
BUILDDIR = build

PROG = $(BUILDDIR)/tetris
SRC = main.cpp Game.cpp View.cpp Human.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean depend

all: $(PROG)

$(PROG): $(addprefix $(BUILDDIR)/, $(OBJ))
	$(CXX) $(LDFLAGS) $^ -o $@ $(LIBFLAGS)

$(addprefix $(BUILDDIR)/, $(OBJ)) : $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp $(INCLDIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILDDIR)/*.o

depend: 
	$(CXX) $(CXXFLAGS) $(addprefix $(SRCDIR)/, $(SRC)) -MM > $(BUILDDIR)/.depend

-include $(BUILDDIR)/.depend