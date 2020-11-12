# directories, must have a 'source' and a 'build' folder in the root directory
source_dir = source
build_dir = build

# add all source files here
source_files = main.cpp ./includes/quick_sort.cpp ./lib/color.cpp

# build file name, default here is app
build_file = app

# compiler, change here if you have a different compiler
cc = g++

# SDL flags for linux, sdl-config will determine what compiler/linker flags
# are required, cflags will print compiler flags, libs will prink linker flags
sdl_flags_linux = -lSDL2 -lSDL2_image

# default entry target is build_program, remove the @ symbol if you want to 
# see the command on the command line
build_program:
	@$(cc) $(source_files) -o $(build_dir)/$(build_file) $(sdl_flags_linux)

# $ make run -> to run the build/executable
run: build_program
	@cd $(build_dir) && ./$(build_file)

reset:
	rm -rf $(build_dir)/*
