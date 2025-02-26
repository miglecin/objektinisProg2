# Makefile projektui

# Kompiliatorius ir flag'ai
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 -Iinclude

# Katalogai
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Failai
SRCS = $(SRC_DIR)/v0.3.cpp \
       $(SRC_DIR)/studentas.cpp \
       $(SRC_DIR)/rikiavimas.cpp \
       $(SRC_DIR)/sufailais.cpp \
       $(SRC_DIR)/LaikoMatavimas.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/programa

# Numatytoji taisyklė
all: $(TARGET)

# Sukuria bin ir obj katalogus, jei jų nėra
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Kompiliacija
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Galutinės programos sujungimas
$(TARGET): $(BIN_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Paleidimas
run: $(TARGET)
	./$(TARGET)

# Išvalymas
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
