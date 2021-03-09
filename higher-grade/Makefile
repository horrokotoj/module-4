DEBUG   := n
CC      := gcc
OS      := $(shell uname)
CFLAGS  := -std=gnu99 -Werror -Wall  -Wno-deprecated-declarations
LDFLAGS :=

ifeq ($(DEBUG), y	)
	CFLAGS += -DDEBUG -g
endif

.PHONY: all clean

bin/sthreads_test: obj/sthreads_test.o obj/sthreads.o src/sthreads.h obj/timer.o src/timer.h
	$(CC) $(CFLAGS) $(LDLIBS) $(filter-out src/sthreads.h, $^) -o $@

obj/sthreads.o: src/sthreads.c src/sthreads.h
	$(CC) $(CFLAGS) -c  $(filter-out src/sthreads.h, $^) -o $@

obj/timer.o: src/timer.c src/timer.h
	$(CC) $(CFLAGS) -c  $(filter-out src/timer.h, $^) -o $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	$(RM) *~ src/*~ src/#* obj/*.o bin/*
	$(RM) -rf bin/*.dSYM

