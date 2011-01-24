CC	:= g++
IFLAGS 	:= -I include/
CFLAGS	:= -Wall -Wextra
DFLAGS	:= -g -DDEBUG
LNFLAGS	:= -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
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


.PHONY= clean
