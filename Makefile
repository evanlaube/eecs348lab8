CC := g++
CFLAGS = -Wall -Wextra -O2

OBJECT_DIR = obj
$(shell mkdir -p $(OBJECT_DIR))

OBJECTS = $(OBJECT_DIR)/matrix.o $(OBJECT_DIR)/main.o 

TARGET = matrix

all: $(TARGET) 

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) 

$(OBJECT_DIR)/%.o: %.cpp | $(OBJECT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECT_DIR) $(TARGET)
