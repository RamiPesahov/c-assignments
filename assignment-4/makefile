TARGET = a.out
SOURCE = $(wildcard *.c *.h)
CC = gcc
FLAGS = -Wall -Wextra 
DEBUG_FLAGS = -Wall -Wextra -g -O0 -DDEBUG -fanalyzer -fsanitize=address

# Default rule: build the program
all: $(TARGET)

$(TARGET): $(SOURCE) $(INCLUDE)
	@$(CC) $(FLAGS) -o $(TARGET) $(SOURCE)

run: $(TARGET)
	@./$(TARGET)

debug:
	@echo "Compiling with debug flags..."
	@$(CC) $(DEBUG_FLAGS) -o $(TARGET) $(SOURCE)

gdb: debug
	@echo "Launching gdb..."
	@gdb ./$(TARGET)

clean:
	@rm -f $(TARGET)	

.PHONY: debug clean


