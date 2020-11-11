# Using libraries:
SDL custom library, naming to be decided.

### color.h
`#include "color.h"` at the top of your file (make sure path is correct).\
`color.cpp` contains the definition of functions.\
`color_example.cpp` contains an example of the usage of functions.\
`g++ color_example.cpp color.cpp -o color -lSDL2` compilation command for 
color_example.cpp\
`./color` run the executable\

#### functions:
- convert_HSL_to_RGB(double hue, double saturation, double lightness)
    - return value : SDL_Color
    - arguments: double hue, double saturation, double lightness
    - hue_to_rgb : helper function

### circle.h
`#include "circle.h"` at the top of your file. (make sure path is correct)\
`circle.cpp` contains the definition of functions.\
`circle_example.cpp` contains an example of the usage of functions.\
`g++ circle_example.cpp circle.cpp -o circle -lSDL2` compilation command for 
color_example.cpp\
`./circle` run the executable\

#### functions:
-  render_circle_outline(SDL_Renderer*) 
    - no return argument 
    - arguments: pointer to a SDL_Renderer 
    - `set_stroke(SDL_color stroke_color, int stroke_width)` : 
    must be run before calling the function, else stroke = black
    - can define the width of the stroke through set_stroke
    - stroke applied to the inside of the circle as of now

### line.h
`#include "line.h"` at the top of your file (make sure path is correct).\
`line.cpp` contains the definition of functions.\
`line_example.cpp` contains an example of the usage of functions.\
`g++ line_example.cpp line.cpp -o line -lSDL2` compilation command for 
color_example.cpp\
`./line` run the executable\

#### functions:
- render_line(SDL_Renderer*) 
    - return value : void 
    - arguments: pointer to a SDL_Renderer 
    - set_arrow properties using setters, if not used, default arrow drawn 
    - default color of line and arrow is black
    - default position of arrow is at the middle, pointing from start to end
    - arrow directions = normal, reverse : 0,1 : start-end, end-start
    - thickness parameter is unused as of now

### Notes:
Ongoing development:\
- fill circles
- line of varying thickness
