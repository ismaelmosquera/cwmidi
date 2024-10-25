#
# Makefile to build cwmidi library.
#
# Macro to perform reordering and cleanup
#
define cleanup
	mv cwmidi.dll lib
	rm *.o
endef
#
vpath %.h include
VPATH := src
CC := gcc
FLAGS := -I include
SLIB := cwmidi.dll
OBJ := midi_file.o midi_song.o midi_track.o midi_event.o midi_message.o midi_tempo.o midi_track_merger.o \
midi_player.o midi_out.o midi_out_dev_list.o rand.o drum_machine.o
$(SLIB): $(OBJ)
	$(CC) $^ -shared -lm -lwinmm -lpthread -O2 -s -DNDEBUG -o $@ && $(cleanup)
midi_file.o: midi_file.c midi_file.h midi_track.h midi_event.h midi_message.h
	$(CC) $(FLAGS) -c $<
midi_song.o: midi_song.c midi_song.h
	$(CC) $(FLAGS) -c $<
midi_track.o: midi_track.c midi_track.h
	$(CC) $(FLAGS) -c $<
midi_event.o: midi_event.c midi_event.h
	$(CC) $(FLAGS) -c $<
midi_message.o: midi_message.c midi_message.h
	$(CC) $(FLAGS) -c $<
midi_tempo.o: midi_tempo.c midi_tempo.h
	$(CC) $(FLAGS) -c $<
midi_track_merger.o: midi_track_merger.c midi_track_merger.h
	$(CC) $(FLAGS) -c $<
midi_player.o: midi_player.c midi_player.h midi_file.h midi_track_merger.h midi_tempo.h midi_event.h
	$(CC) $(FLAGS) -c $<
midi_out.o: midi_out.c midi_out.h
	$(CC) $(FLAGS) -c $<
midi_out_dev_list.o: midi_out_dev_list.c midi_out_dev_list.h
	$(CC) $(FLAGS) -c $<
rand.o: rand.c rand.h
	$(CC) $(FLAGS) -c $<
drum_machine.o: drum_machine.c midi_out.h midi_message.h rand.h drum_machine.h
	$(CC) $(FLAGS) -c $<


