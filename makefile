
CC = gcc
OBJS = election.o area.o tribe.o map.o electionTestsExample.o
EXEC = HW1Election
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

$(EXEC) : $(OBJS)
    $(CC) $(DEBUG_FLAG) $(OBJS) -L. -lmap -o election

election.o : election.c election.h map.h area.h tribe.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)

area.o: area.c area.h tribe.h map.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)

map.o: map.c map.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)

tribe.o: tribe.c tribe.h
    $(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)

clean:
	rm -f  $(OBJS) HW1Election