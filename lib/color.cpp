#include "color.h"
#include <cstdint>
#include <iostream>
#include <algorithm>

SDL_Color convert_HSL_to_RGB(double hue, double saturation, double lightness){
  SDL_Color rgba;
  uint8_t rgb_red, rgb_blue, rgb_green;
  double hue_val = hue / 365.0, 
         sat_val = saturation / 100.0,
         lit_val = lightness / 100.0;

  if (saturation <= 0.0){
    rgb_blue = rgb_green = rgb_red = lit_val * 255;
    return {rgb_red, rgb_blue, rgb_green, 255};
  }

  // temporary variables
  double temp_1, temp_2;
  temp_1 = lit_val < 0.5 ? lit_val * (1.0 + sat_val):
    lit_val + sat_val - lit_val * sat_val; 
  temp_2 = 2.0 * lit_val - temp_1;

  rgb_red = hue_to_rgb(temp_1, temp_2, hue_val + 1.0/3.0);
  rgb_green = hue_to_rgb(temp_1, temp_2, hue_val);
  rgb_blue = hue_to_rgb(temp_1, temp_2, hue_val - 1.0/3.0);

  return {rgb_red, rgb_blue, rgb_green, 255};
}

uint8_t hue_to_rgb(double p, double q, double t){
  // formula for final coversion
  if (t < 0) t++;
  if (t > 1) t--;

  if (6*t < 1) return (q + (p-q) * 6 * t) * 255;
  if (2*t < 1) return p * 255;
  if (3*t < 2) return (q + (p-q) * (2.0/3.0 - t) * 6) * 255;
  return q * 255;
}

void convert_RGB_to_HSL(int rgb_red, int rgb_green, int rgb_blue){
  double hue, saturation, lightness;

  unsigned int color_max = std::max(std::max(rgb_red, rgb_green),rgb_blue); 
  unsigned int color_min = std::min(std::min(rgb_red, rgb_green),rgb_blue); 

  double max_val = color_max / 255.0, min_val = color_min / 255.0;

  lightness = (max_val + min_val)/2;

  if (color_max == color_min){
    hue = saturation = 0; //achromatic
    return;
  }

  if (lightness <= 0.5){
    saturation = (max_val - min_val)/(max_val + min_val);
  }
  else {
    saturation = (max_val - min_val)/(2.0 - max_val - min_val);
  }

  if (color_max == rgb_red){
    hue = (rgb_green - rgb_blue) * 1.0 / (color_max - color_min) +
      (rgb_green < rgb_blue ? 6 : 0);      
  }
  else if (color_max == rgb_blue){
    hue =  (rgb_red - rgb_green) * 1.0 / (color_max - color_min) + 4; 
  }  
  else {
    hue = (rgb_blue - rgb_red) * 1.0 / (color_max - color_min) + 2;
  }

  std::cout << "hue : " << hue * 60 << " saturation : " << saturation * 100
    << " lightness : " << lightness * 100 << "\n";
}

