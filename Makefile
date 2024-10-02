# Compiler
CXX := g++

CXXFLAGS := -std=c++20 -fdiagnostics-color=always -g -ggdb \
            -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror

# Default source file
SRC := main.cpp

OUT := $(basename $(SRC))

.PHONY: run
run: $(OUT)
	@./$(OUT)  # Suppress command output for the run command

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

.PHONY: clean
clean:
	rm -f $(OUT)

ifeq ($(SRC),)
SRC := main.cpp
endif
