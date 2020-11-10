#ifndef COLORS_LIBRARY_DEFINED
#define COLORS_LIBRARY_DEFINED

#include <SDL2/SDL.h>
#include <cstdint>

uint8_t hue_to_rgb(double p, double q, double t);

// rgb to hsl has no use as of yet, just for checking/testing purpose
void convert_RGB_to_HSL(unsigned int red, unsigned int green, unsigned int blue);
SDL_Color convert_HSL_to_RGB(double hue, double saturation, double lightness);

#endif
