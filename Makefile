CC = gcc	
CFLAGS = -Wall -g
SOURCES = $(wildcard ./src/*.c)
SOURCES += $(wildcard ./test/*.c)
HEADS = $(wildcard ./src/*.h)
OBJECTS = $(SOURCES:.c=.o)
TARGET = $(patsubst %.c,%,$(wildcard ./test/*.c))
INC = -I ./src

.PHONY: all clean
all:$(TARGET)
clean:
	rm -rf $(OBJECTS)
	rm -rf $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(INC) $(CFLAGS) $^ -o $@

$(OBJECTS):%.o:%.c $(HEADS)
	$(CC) $(INC) -c $(CFLAGS) $< -o $@


