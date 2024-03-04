# Build
NAME = main

# Command To Build, Clean, Make
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
LIBS =

# For Building Application
.PHONY: directories
.PHONY: run 
.PHONY: clean
all: directories $(BIN_DIR)/$(NAME)

directories: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR):
	@echo Making Folder: $@
	@mkdir -p $@
	@echo ===============================================================

$(BIN_DIR):
	@echo Making Folder: $@
	@mkdir -p $@
	@echo ===============================================================

# Build Executable Files
$(BIN_DIR)/$(NAME): directories $(OBJS)
	@echo Building Executable Files: $@.exe
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)
	@echo ===============================================================

# Build Objects Files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Building Object Files: $@
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo ===============================================================

# To Run Application
run: $(BIN_DIR)/$(NAME)
	@echo Running: $<.exe 
	@./$<
	@echo ===============================================================

# Clean All Files
clean:
	@echo Cleaning...
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo ===============================================================