TARGET	:= controller-manager

CC 	:= g++
CFLAGS 	:= -g -Wall -Wextra
LDFLAGS := -lSDL2 -lSDL2_ttf

BLD_DIR := ./out
SRC_DIR := ./src

SRC_FILES = $(SRC_DIR)/Main.cpp\
	    $(SRC_DIR)/MainState.cpp\
	    $(SRC_DIR)/sdl/sdl_boiler.cpp

$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(BLD_DIR)/$@

config:
	mkdir $(BLD_DIR)

clean:
	rm -rf $(BLD_DIR)/*
