# directories, must have 'build' and 'bin' folder in the root directory
build_dir=build
binary_dir=bin

# binary file name, default here is app
binary_file=app

# add all source files here
source_files=main.cpp includes/*.cpp lib/*.cpp
object_files=$(build_dir)/main.o \
							$(build_dir)/circle.o $(build_dir)/color.o $(build_dir)/line.o \
							$(build_dir)/quick_sort_spectrum.o \
							$(build_dir)/quick_sort_rectangles.o \
							$(build_dir)/huffman.o $(build_dir)/huffman_data_structure.o \
							$(build_dir)/huffman_maths.o

# compiler, change here if you have a different compiler
cc=g++
co=g++ -c

# SDL flags for linux
sdl_flags_linux =-lSDL2 -lSDL2_ttf

# default entry target is build_program, remove the @ symbol if you want to 
# see the command on the command line

$(binary_dir)/$(binary_file): $(object_files)
		@$(cc) $(object_files) -o $@ $(sdl_flags_linux)

$(build_dir)/main.o: main.cpp ./includes/huffman.* \
	./includes/quick_sort_spectrum.* \
	./includes/quick_sort_rectangles.*
	$(co) main.cpp -o $@

$(build_dir)/huffman.o: ./includes/huffman.* ./includes/huffman_maths.* \
	./includes/huffman_data_structure.* ./lib/circle.* ./lib/line.*
	$(co) ./includes/huffman.cpp -o $@

$(build_dir)/quick_sort_rectangles.o: ./includes/quick_sort_rectangles.* \
	./lib/color.h
	$(co) ./includes/quick_sort_rectangles.cpp -o $@

$(build_dir)/quick_sort_spectrum.o: ./includes/quick_sort_spectrum.* \
	./lib/color.*
	$(co) ./includes/quick_sort_spectrum.cpp -o $@

$(build_dir)/color.o: ./lib/color.*
	$(co) ./lib/color.cpp -o $@

$(build_dir)/line.o: ./lib/line.*
	$(co) ./lib/line.cpp -o $@

$(build_dir)/circle.o: ./lib/circle.*
	$(co) ./lib/circle.cpp -o $@

$(build_dir)/huffman_data_structure.o: ./includes/huffman_data_structure.*
	$(co) ./includes/huffman_data_structure.cpp -o $@

$(build_dir)/huffman_maths.o: ./includes/huffman_maths.*
	$(co) ./includes/huffman_maths.cpp -o $@

# $ make run -> to run the $(build_dir)/executable
run: $(binary_dir)/$(binary_file)
	@cd $(binary_dir) && ./$(binary_file)

.PHONY : clean
clean:
	@cd $(build_dir) && rm -f $(object_files) && echo "All object files removed!"
