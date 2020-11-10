#include "circle.h"
#include <SDL2/SDL.h>

// constructors and destructors
Circle::Circle(int x, int y, int r):centre_x(x), centre_y(y),radius(r){}
Circle::Circle(){}
Circle::~Circle(){}

// setters
void Circle::set_center(int x, int y){ centre_x = x; centre_y = y; }
void Circle::set_radius(int r) { radius = r; }
void Circle::set_fill(SDL_Color color){ fill_color = color; } 
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
}
