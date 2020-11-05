# directories, must have a 'source' and a 'build' folder in the root directory
source_dir = source
build_dir = build

# add all source files here
source_files = $(source_dir)/main.cpp

# build file name, default here is app
build_file = ./app

# compiler, change here if you have a different compiler
cc = g++

# SDL flags for linux, add lSDL2_image, lSDL2_ttf and others here
sdl_flags_linux = -lSDL2 

# default entry target is build_program, remove the @ symbol if you want to 
# see the command on the command line
build_program:
	@$(cc) $(source_files) -o $(build_file) $(sdl_flags_linux)

# $ make run -> to run the build/executable
run: build_program
	@cd $(build_dir) && $(build_file)

reset:
	rm -rf $(build_dir)/*
