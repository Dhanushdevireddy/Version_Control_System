SOURCES = $(wildcard *.cpp)
EXECUTABLE = test_folder/mygit
all: clean $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ -std=c++17 -Wall -o $@ $(SOURCES) -lssl -lcrypto -lz

clean:
	rm -f $(EXECUTABLE)