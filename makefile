# Compiler and flags
CXX = g++
CXXFLAGS += -std=c++17 -Iinclude

# Directories
SRC_DIR = Src
BUILD_DIR = build
BIN_DIR = bin
RESULTS_DIR = results

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Test files (excluding catch_amalgamated.cpp)
TEST_SOURCES = $(wildcard $(SRC_DIR)/*_test.cpp)
TEST_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SOURCES))

# Executable file
EXECUTABLE = $(BIN_DIR)/programa
TEST_EXECUTABLE = $(BIN_DIR)/test_programa

# Target - main program
all: sukurti_dirs $(EXECUTABLE)

sukurti_dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(RESULTS_DIR)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile tests (without catch_amalgamated.cpp)
$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile individual .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(RESULTS_DIR)

# Run tests
tests: $(TEST_EXECUTABLE)
	$(TEST_EXECUTABLE)  # Run Catch2 tests

test: tests
	./$(TEST_EXECUTABLE)
