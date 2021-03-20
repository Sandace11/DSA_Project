# DSA_Project
Data Structure and Algorithm Project, 4th Semester

## Visualization of Quicksort Algorithm & Huffman Tree

![screenshot.gif](https://raw.githubusercontent.com/Sandace11/DSA_Project/main/screenshots/output.gif)

### Requirements
- SDL2
- SDL2_ttf (for rendering fonts)
- GNU Make (for building executable)

### Project Initialization
Run the `init.sh` to initialize the directory structure.
```
chmod +x init.sh
./init.sh
```
If your default shell does not support bash scripting, create two 
new directories manually : `build` and `bin`. That is what `init.sh`
essentially does. For more details, see **Directory Structure** below.

### Make Instructions
`make` - to compile the program\
`make run` - to run the build/executable\
`make clean` - delete the created object files, for cleanup

### Directory Structure
`init.sh` creates two new directories 
- `build` (to store object files)
- `bin` (to store the final binary) 

These directories are essential as all object files and the final
created executable use them as path. This is done to keep the root
project directory clean.

The names can be manually edited inside the `MakeFile` and 
`init.sh` (just change the variable values inside):
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
├── init.sh                 # The initialization script
├── MakeFile                # MakeFile for compilation/build instructions
└── README.md               # README file
```

### Notes:
- Not Windows compatible for now, mostly due to path changes required for SDL.
- Need to work on a script to auto-install all the required libraries.
- External contributions/pull requests will not be accepted as of 
now, since this is a college project.

### Primary Contributors:
[@pranjalpokharel7](https://github.com/pranjalpokharel7)\
[@Sandace11](https://github.com/Sandace11)\
[@UdeshyaDhungana](https://github.com/UdeshyaDhungana)

