####################################################
#      BENDEM'S MAKEFILE (NOT YOURS D: !)          #
####################################################
#
# Regex to fix CLion const declaration
# ([^\n( ,]+) const& (.+)[^);\n{ ]
# const $1& $2
####################################################

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRC=src
OUT=target
HDR=header
FLA=-I$(HDR) -Wall -Wextra
CXX=g++ $(FLA)

# Get all files from the header dir
FILES:=$(call rwildcard,$(HDR)/,*.hpp)
# Transform files (change .hpp to .o)
OBJ:=$(FILES:$(HDR)/%.hpp=$(OUT)/%.o)

# Get all folders
SRC_DIRS:=$(sort $(rwildcard $(HDR)/*/))
# Transform tree structure to out dir
OUT_DIRS:=$(SRC_DIRS:$(HDR)%=$(OUT)%)

.PHONY: build clean debug mkdir
.SILENT:

build: $(OUT)/main

$(OUT)/main: main.cpp $(OBJ)
	echo Compiling $@...
	$(CXX) -o $@ $^

$(OUT)/Test%: Test%.cpp $(OBJ)
	echo Compiling $@...
	$(CXX) -o $@ $^

$(OUT)/%.o: $(SRC)/%.cpp $(HDR)/%.hpp
	echo Compiling $@...
	$(CXX) -c -o $@ $<

clean: | del mkdir

del:
	echo Cleaning...
	rm -rf $(OUT)/

mkdir:
	echo Recreating empty tree...
ifeq ($(OS),Windows_NT)
	mkdir $(OUT)
	xcopy /T $(HDR) $(OUT)
else
	python fix_files.py
endif

debug:
	echo Obj
	echo $(OBJ)
	echo OS
	echo $(OS)
	echo Out_dirs
	echo $(OUT_DIRS)
	echo Flags
	echo $(FLA)
