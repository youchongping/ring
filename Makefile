#CROSS = arm-linux-gnueabihf-

MAKE = make

CC = $(CROSS)gcc
LD = $(CROSS)ld
STRIP = $(CROSS)strip


SOURCES = ring.c main.c
OBJS = $(SOURCES:.c=.o)


.SUFFIXES:.c.o
.SILENT:

all: $(OBJS)
	@echo linking... $@
	sudo $(CC) -o $@ $(OBJS)
.c.o:
	@echo CC $<
	sudo $(CC) -c -o $@ $<
clean:
	sudo rm -rf $(CURDIR)/*.o $(CURDIR)/*~ $(CURDIR)/all
