# Kompiliatorius ir vėliavos
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 -g -Iinclude

# Katalogai
SRC_DIR = Src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
RESULTS_DIR = results
TEST_FILES_DIR = test_files
REZULTATAI_DIR = rezultatai

# Failų sąrašas
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Vykdomasis failas
EXECUTABLE = $(BIN_DIR)/programa

# Tikslas - pagrindinė programa
all: sukurti_dirs $(EXECUTABLE)

# Sukurti katalogus
sukurti_dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(RESULTS_DIR) $(TEST_FILES_DIR) $(REZULTATAI_DIR)

# Kompiliuoti programą
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Kompiliuoti atskirus .o failus
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Išvalyti sukurtus failus
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(RESULTS_DIR) $(REZULTATAI_DIR)

# Debug režimas
debug: CXXFLAGS += -DDEBUG
debug: clean all
