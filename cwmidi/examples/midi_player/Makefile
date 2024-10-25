#
# Makefile to build test midi
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
OBJ := test_midi_player.o 
$(PROG): $(OBJ)
	$(CC) $(CCF) $^ -o $@ && $(cleanup)
test_midi_player.o: test_midi_player.c midi_player.h
	$(CC) $(FLAGS) -c $<

