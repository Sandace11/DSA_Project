# DSA_Project
Data Structure and Algorithm Project, 4th Semester

## Visualization of Quicksort Algorithm & Huffman Tree

![screenshot.gif](https://raw.githubusercontent.com/Sandace11/DSA_Project/main/screenshots/output.gif)

### Requirements
- SDL2
- SDL2_ttf (for rendering fonts)
- GNU Make (for building executable)

### Directory structure (important pre-requisite)
Make sure to create two new directories 
- `build` (to store object files)
- `bin` (to store the final binary) 

The names of the binaries can be manually edited
through the MakeFile (just change the variable values inside):
```
build_dir=build
binary_dir=bin
```
Your final project structure should look something like this:
```
.
├── assets/                 # Fonts and other resources
├── bin/                    # Final working binary
├── build/                  # Compiled object files
├── includes/               # Headers and their source files
├── lib/                    # Custom files that fall under 'library'
├── screenshots/            # If and any screenshots for preview
├── main.cpp                # Entry point into the program
├── MakeFile                # MakeFile for compilation/build instructions
└── README.md               # README file
```

### Make instructions
`make` - to compile the program\
`make run` - to run the build/executable\
`make clean` - delete the created object files, for cleanup

### Notes:
- Not Windows compatible for now, mostly due to path changes required for SDL.
- Need to work on a script to auto-install all the required libraries.

### Primary Contributors:
[@pranjalpokharel7](https://github.com/pranjalpokharel7)\
[@Sandace11](https://github.com/Sandace11)\
[@UdeshyaDhungana](https://github.com/UdeshyaDhungana)

