#include "circle.h"
#include <cstring>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// constructors and destructors
Circle::Circle(int x, int y, int r, int node_wt, char node_ch, 
    int s_width, SDL_Color s_color){
  centre_x = x; centre_y = y;
  radius = r;
  stroke_width = s_width;
  stroke_color = s_color;

  // node properties
  node_weight = node_wt;
  node_char = node_ch;
}
Circle::Circle(){}
Circle::~Circle(){
}

// setters
void Circle::set_center(int x, int y){ centre_x = x; centre_y = y; }
void Circle::set_radius(int r) { radius = r; }
void Circle::set_stroke(SDL_Color color, int width = 0){
  stroke_color = color; 
  stroke_width = width;
}

// getters
SDL_Point Circle::get_center(){ return {centre_x, centre_y}; }
int Circle::get_radius(){ return radius; }

// circle rendering functions
void Circle::render_circle_outline(SDL_Renderer *renderer){
  if (!renderer) return;

  font_texture = load_font(renderer, "../assets/Helvetica45Light_22437.ttf", 
      radius/1.5);
  if (!font_texture){
    printf("Failed to load font_texture in render_circle_outline : %s\n",
        SDL_GetError());
    return;
  }
  // query texture will fill in the w and h attributes of text_box
  SDL_QueryTexture(font_texture, nullptr, nullptr, &text_box.w, &text_box.h);

  SDL_SetRenderDrawColor(renderer, stroke_color.r, stroke_color.g,
      stroke_color.b, stroke_color.a);

  int temp = stroke_width; 
  while (stroke_width >= 0){
    // starting drawing the first octant at (x + radius, y)
    int x = radius - stroke_width, y = 0;

    // setting the initial value for decision parameter 'p'
    int p = 1 - radius + stroke_width;

    SDL_RenderDrawPoint(renderer, x+centre_x, y+centre_y);
    if (radius > 0){
      // first draw all points lying on tha major axes XX' and YY' 
      SDL_RenderDrawPoint(renderer, x+centre_x, -y+centre_y);
      SDL_RenderDrawPoint(renderer, y+centre_x, x+centre_y);
      SDL_RenderDrawPoint(renderer, -y+centre_x, x+centre_y);
    }

    // this loop will be skipped in case radius <= 0 since x = radius and y = 0
    while (x > y){
      y++;

      // set decision parameter based on it's previous value
      // if p <=0, it means the midpoint between (x, y+1) and (x-1, y+1) lies
      // inside the circle, else it lies outside.
      if (p <= 0){
        // select (x, y+1) as the next closest point
        p = p + 2*y + 1;
      }
      else{ 
        // select (x-1, y+1) as the next closest point
        x--;
        p = p + 2*y - 2*x + 1;
      }

      if (x < y) break;

      // draw corresponding points of all octants
      SDL_RenderDrawPoint(renderer, x+centre_x, y+centre_y);
      SDL_RenderDrawPoint(renderer, -x+centre_x, y+centre_y);
      SDL_RenderDrawPoint(renderer, x+centre_x, -y+centre_y);
      SDL_RenderDrawPoint(renderer, -x+centre_x,-y+centre_y);

      // skip the points lying on the line y = x
      if (x != y) {
        SDL_RenderDrawPoint(renderer,y+centre_x, x+centre_y);
        SDL_RenderDrawPoint(renderer,-y+centre_x, x+centre_y);
        SDL_RenderDrawPoint(renderer,y+centre_x, -x+centre_y);
        SDL_RenderDrawPoint(renderer,-y+centre_x,-x+centre_y);
      }
    }
    stroke_width--;
  }
  stroke_width = temp;

  // draw text over circle
  text_box.x = centre_x - radius/2;
  text_box.y = centre_y - radius/2;
  SDL_RenderCopy(renderer, font_texture, nullptr, &text_box);
  SDL_DestroyTexture(font_texture);
}

SDL_Texture* Circle::load_font(SDL_Renderer* renderer, const char* font_path, 
    int font_size, SDL_Color font_color){

  TTF_Font *font = TTF_OpenFont(font_path, font_size);
  if (!font){
    printf("Failed to load font! : %s\n", SDL_GetError());
    return nullptr;
  }

  std::string render_text; 
  if (node_char != '*'){
    std::string s(1, node_char);
    render_text = s + "\n(" + std::to_string(node_weight) + ")";
  }
  else {
    render_text = std::to_string(node_weight);
  }

  SDL_Surface* text_surface = TTF_RenderText_Solid(font, render_text.c_str(), 
      font_color);
  if (!text_surface) {
    printf("Failed to load font surface! : %s\n", SDL_GetError());
    return nullptr;
  }

  TTF_CloseFont(font);

  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer,
      text_surface);
  if (!text_texture) {
    printf("Failed to create font texture! : %s\n", SDL_GetError());
    return nullptr;
  }

  SDL_FreeSurface(text_surface);
  return text_texture;
}
