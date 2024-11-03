TARGET	:= controller-manager

BLD_DIR := ./out
RES_DIR := ./res

$(TARGET):
	cd $(BLD_DIR) &&\
	cmake .. &&\
	cmake --build .
	mkdir $(BLD_DIR)/ttf
	cp $(RES_DIR)/ttf/arial.ttf $(BLD_DIR)/ttf/arial.ttf

config:
	mkdir $(BLD_DIR)

clean:
	rm -rf $(BLD_DIR)/*
