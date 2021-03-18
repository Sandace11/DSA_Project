# directories, must have 'build' folder in the root directory
build_dir =build
includes_dir =includes
lib_dir =lib

# add all source files here
source_files =main.cpp $(includes_dir)/*.cpp $(lib_dir)/*.cpp
object_files =main.o \
							circle.o color.o line.o \
							quick_sort_spectrum.o quick_sort_rectangles.o \
							huffman.o huffman_data_structure.o huffman_maths.o

# build file name, default here is app
build_file =app

# compiler, change here if you have a different compiler
cc =g++
co =g++ -c

# SDL flags for linux
sdl_flags_linux =-lSDL2 -lSDL2_ttf

# default entry target is build_program, remove the @ symbol if you want to 
# see the command on the command line

app: $(object_files)
	@$(cc) $(object_files) -o $(build_file) $(sdl_flags_linux) && \
		mv $(build_file) $(build_dir)

main.o: main.cpp ./includes/huffman.* \
	./includes/quick_sort_spectrum.* \
	./includes/quick_sort_rectangles.*

huffman.o: ./includes/huffman.*
	@$(co) ./includes/huffman.cpp

quick_sort_rectangles.o: ./includes/quick_sort_rectangles.*
	@$(co) ./includes/quick_sort_rectangles.cpp

quick_sort_spectrum.o: ./includes/quick_sort_spectrum.*
	@$(co) ./includes/quick_sort_spectrum.cpp

color.o: ./lib/color.*
	@$(co) ./lib/color.cpp

line.o: ./lib/line.*
	@$(co) ./lib/line.cpp

circle.o: ./lib/circle.*
	@$(co) ./lib/circle.cpp

huffman_data_structure.o: ./includes/huffman_data_structure.*
	@$(co) ./includes/huffman_data_structure.cpp 

huffman_maths.o: ./includes/huffman_maths.*
	@$(co) ./includes/huffman_maths.cpp

# $ make run -> to run the build/executable
run: app 
	@cd $(build_dir) && ./$(build_file)

.PHONY : clean
clean:
	rm -f $(object_files) 
