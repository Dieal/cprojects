# Variables
CC      = gcc
CFLAGS  = -std=c23
STRICT_FLAGS  = -Wall -Wextra -std=c23 -pedantic
TARGET  = program
SRC     = main.c

# The default 'target' when you just type 'make'
all: $(TARGET)
	./$(TARGET)

# Linking the executable
$(TARGET): $(SRC)
	$(CC) $(STRICT_FLAGS) $(SRC) -o $(TARGET) $(LIBS)

normal: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean up the build
clean:
	rm -f $(TARGET)

# Helper to run the game
run: all
	./$(TARGET)
