CC	:= g++
IFLAGS 	:= -I include/ -IBox2D/Box2D
CFLAGS	:= -Wall -Wextra -Wno-unused-parameter
DFLAGS	:= -g -DDEBUG
# $(shell find Box2D/Build/Box2D -name "*.o" -type f)

BOX2D   := -lBox2D Box2D/Build/Box2D/libBox2D.a
LNFLAGS	:= -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lm $(BOX2D)
EXE 	:= blocks

.SUFFIXES=.cpp

SRC 	:= $(shell find 'src' -name '*.cpp' )
OBJ 	:= $(SRC:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(IFLAGS) $(LNFLAGS) -o$(EXE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

debug:
	@$(MAKE) $(MFLAGS) CFLAGS="$(CFLAGS) $(DFLAGS)"

.PHONY= clean
