CXX = g++
CXXFLAGS = -Wall -Wextra -I./$(INCLDIR)

SRCDIR = src
INCLDIR = include
BUILDDIR = build

PROG = $(BUILDDIR)/snake
SRC = main.cpp human.cpp model.cpp tview.cpp gview.cpp view.cpp
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean depend

all: $(PROG)

$(PROG): $(addprefix $(BUILDDIR)/, $(OBJ))
	$(CXX) $(CXXFLAGS) $^ -o $@

$(addprefix $(BUILDDIR)/, $(OBJ)) : $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp $(INCLDIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILDDIR)/*.o

depend: 
	$(CXX) $(CXXFLAGS) $(addprefix $(SRCDIR)/, $(SRC)) -MM > $(BUILDDIR)/.depend

-include $(BUILDDIR)/.depend