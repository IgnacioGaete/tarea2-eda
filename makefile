SRC_DIR=./sources
HDR_DIR=./headers
OBJ_DIR=./objects

./elo320_tarea2: $(OBJ_DIR)/main.o $(OBJ_DIR)/functions.o
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/functions.o -o ./elo320_tarea2
	
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(HDR_DIR)/functions.h
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o
	
$(OBJ_DIR)/functions.o: $(SRC_DIR)/functions.c $(HDR_DIR)/functions.h
	gcc -c $(SRC_DIR)/functions.c -o $(OBJ_DIR)/functions.o 
	
clean:
	rm ./elo320_tarea2 $(OBJ_DIR)/*.o
