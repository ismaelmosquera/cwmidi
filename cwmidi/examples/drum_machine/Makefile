#
# Makefile to build test drum machine
#
# Macro to perform cleanup
#
define cleanup
	mv prog bin
	rm *.o
endef
#
vpath %.h ../../include
CC := gcc
FLAGS := -I ../../include
CCF := -L../../lib -lcwmidi -O2 -s -DNDEBUG
PROG := prog
OBJ := test_drum_machine.o 
$(PROG): $(OBJ)
	$(CC) $(CCF) $^ -o $@ && $(cleanup)
test_drum_machine.o: test_drum_machine.c drum_machine.h
	$(CC) $(FLAGS) -c $<

