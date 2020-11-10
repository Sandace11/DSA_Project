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
- convert_HSL_to_RGB
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
    must be run before calling the function, else stroke defaults to black
    - can define the width of the stroke through set_stroke
    - stroke applied to the inside of the circle as of now

### Notes:
Ongoing development, currently fill circles.
