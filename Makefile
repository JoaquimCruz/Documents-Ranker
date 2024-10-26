CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17
LDFLAGS  := -lcurl -lsqlite3  # Linkando com cURL e SQLite
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/
TARGET   := app
INCLUDE  := -Iinclude/
SRC      := $(wildcard src/*.cpp)  

OBJECTS := $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)  


all: build $(APP_DIR)/$(TARGET)


$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)  # Cria o diretório de objetos se não existir
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)  # Cria o diretório do executável se não existir
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $(@) $(LDFLAGS)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O3
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

run:
	./$(BUILD)/$(TARGET)

r: clean all run