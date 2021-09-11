CC = g++ -std=c++11
SOURCE_DIR = source
BUILD_DIR = build

all: $(BUILD_DIR) $(BUILD_DIR)/cipher.out

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/fnameutil.o : $(SOURCE_DIR)/fnameutil.hpp $(SOURCE_DIR)/fnameutil.cpp
	$(CC) -c $(SOURCE_DIR)/fnameutil.cpp -o $(BUILD_DIR)/fnameutil.o

$(BUILD_DIR)/progress.o : $(SOURCE_DIR)/progress.hpp $(SOURCE_DIR)/progress.cpp
	$(CC) -c $(SOURCE_DIR)/progress.cpp -o $(BUILD_DIR)/progress.o

$(BUILD_DIR)/cipher.o : $(SOURCE_DIR)/cipher.hpp $(SOURCE_DIR)/cipher.cpp $(SOURCE_DIR)/progress.hpp $(SOURCE_DIR)/fnameutil.hpp
	$(CC) -c $(SOURCE_DIR)/cipher.cpp -o $(BUILD_DIR)/cipher.o

$(BUILD_DIR)/progbar.o : $(SOURCE_DIR)/console/progbar.hpp $(SOURCE_DIR)/console/progbar.cpp $(SOURCE_DIR)/progress.hpp
	$(CC) -c $(SOURCE_DIR)/console/progbar.cpp -o $(BUILD_DIR)/progbar.o

$(BUILD_DIR)/main.o : $(SOURCE_DIR)/main.cpp $(SOURCE_DIR)/cipher.hpp $(SOURCE_DIR)/console/progbar.hpp
	$(CC) -c $(SOURCE_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/cipher.out : $(BUILD_DIR)/main.o $(BUILD_DIR)/progbar.o $(BUILD_DIR)/cipher.o $(BUILD_DIR)/progress.o $(BUILD_DIR)/fnameutil.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/progbar.o $(BUILD_DIR)/cipher.o  $(BUILD_DIR)/progress.o $(BUILD_DIR)/fnameutil.o -o $(BUILD_DIR)/cipher.out

.PHONY : clean
clean :
	rm -rf $(BUILD_DIR) *.o *.out