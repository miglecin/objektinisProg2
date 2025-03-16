# Kompiliatorius ir flagai
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

# Aplankai
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Pagrindiniai failai
SOURCES = v1.cpp studentas.cpp sufailais.cpp rikiavimas.cpp tyrimas3.cpp tyrimas4.cpp LaikoMatavimas.cpp
HEADERS = studentas.h sufailais.h rikiavimas.h tyrimas3.h tyrimas4.h LaikoMatavimas.h
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Programos pavadinimas
EXECUTABLE = $(BIN_DIR)/v1

# Tikrina, ar egzistuoja aplankai
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Kompiliavimas
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Atitinkamų `.o` failų generavimas
$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Paleidimo komanda
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Valymo komandos
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

rebuild: clean $(EXECUTABLE)

