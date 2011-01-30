CC	:= g++
IFLAGS 	:= -I include/
CFLAGS	:= -Wall -Wextra -Wno-unused-parameter
DFLAGS	:= -g -DDEBUG
LNFLAGS	:= -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system -lm
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
