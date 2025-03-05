# Kompiliatorius ir vėliavėlės
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 -Iinclude
LDFLAGS = -std=c++17

# Šaltinio failai
SRC = v0.4.cpp generuoti_failus.cpp LaikoMatavimas.cpp rikiavimas.cpp sufailais.cpp studentas.cpp tyrimas1.cpp tyrimas2.cpp
OBJ = $(SRC:.cpp=.o)

# Vykdomasis failas
BIN = bin/v0.4

all: $(BIN)

$(BIN): $(OBJ)
	mkdir -p bin
	$(CC) $(LDFLAGS) -o $(BIN) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -rf obj bin
