TARGET = myprogram

CC = g++
FLAGS = -Wall -std=c++20

SOURCES = src/main.cpp src/Logger/Logger.cpp src/cpu_6502/cpu_6502.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

run: $(TARGET)
	bin/$(TARGET)

# Rule to link object files into an executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o bin/$@

# Pattern rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f bin/$(TARGET) $(OBJECTS)
