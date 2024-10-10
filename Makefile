# Compiler
CXX := g++

CXXFLAGS := -std=c++20 -fdiagnostics-color=always -g -ggdb -pedantic \
            -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -Wpedantic

# Default source directory and files
SRCDIR := src
SRC := $(wildcard $(SRCDIR)/*.cpp)

# Output file name
OUT := $(basename $(SRC))

.PHONY: run
run: $(OUT)
	@./$(OUT)  # Suppress command output for the run command

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

.PHONY: clean
clean:
	rm -f $(OUT)
