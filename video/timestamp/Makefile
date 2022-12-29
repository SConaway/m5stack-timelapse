CXX = g++

CXXFLAGS  = -g -Wall $(shell Magick++-config --cppflags --cxxflags --ldflags --libs) -I/opt/homebrew/Cellar/boost/1.80.0/include/ -std=gnu++20

TARGET = timestamp

.PHONY: all clean run
all: $(TARGET)

$(TARGET): timestamp.cpp
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
