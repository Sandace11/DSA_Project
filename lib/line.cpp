#include "line.h"

// constructors and destructors
Line::Line(){}
Line::~Line(){}
Line::Line(int sx, int sy, int ex, int ey, int t, SDL_Color color){
  start_x = sx; start_y = sy;
  end_x = ex; end_y = ey;

  thickness = t;
  line_color = color;

  // by default arrow head originates from the middle of the line
  // default arrow length is 10, change parameters here for now
  arrow_x = (start_x + end_x) / 2;
  arrow_y = (start_y + end_y) / 2;
  arrow_length = 10;
}

// setters
void Line::set_line_starting_point(int x, int y) { start_x = x; start_y = y; }
void Line::set_line_ending_point(int x, int y) { end_x = x; end_y = y;  }
void Line::set_line_thickness(int t) { thickness = t; }
void Line::set_line_color(SDL_Color color) { line_color = color; }

void Line::set_arrow_length(int len){ arrow_length = len;  }
void Line::set_arrow_direction(int a_dir){ arrow_direction = a_dir; }
void Line::set_arrow_by_point(int x, int y){ arrow_x = x; arrow_y = y; }
void Line::set_arrow_by_position(int pos){
  if (pos == beginning){
    arrow_x = start_x;
    arrow_y = start_y;
    arrow_direction = reverse;
  }
  else if (pos == end){
    arrow_x = end_x;
    arrow_y = end_y;
    arrow_direction = normal;
  }
  else {
    arrow_x = (start_x + end_x) / 2;
    arrow_y = (start_y + end_y) / 2;
  }
}

// draw line with arrow
void Line::render_line(SDL_Renderer* renderer){
  // draw line first
  SDL_SetRenderDrawColor(renderer, line_color.r, line_color.g, line_color.b, 
      line_color.a);
  SDL_RenderDrawLine(renderer, start_x, start_y, end_x, end_y);

  // drawing arrow part
  const double cos = 0.866;
  const double sin = 0.5;
  // dx and dy are the lengths of individual arrow, for now equal lengths
  double dx = arrow_length; 
  double dy = arrow_length;
  int p1_x, p1_y, p2_x, p2_y;

  if (arrow_direction == reverse){
    p1_x = arrow_x + (dx * cos - dy * sin);
    p1_y = arrow_y + (dx * sin + dy * cos);
    p2_x = arrow_x + (dx * cos + dy * sin);
    p2_y = arrow_y + (dy * cos - dx * sin);
  }
  else {
    p1_x = arrow_x - (dx * cos - dy * sin);
    p1_y = arrow_y - (dx * sin + dy * cos);
    p2_x = arrow_x - (dx * cos + dy * sin);
    p2_y = arrow_y - (dy * cos - dx * sin);
  }

  SDL_RenderDrawLine(renderer, arrow_x, arrow_y, p1_x, p1_y);
  SDL_RenderDrawLine(renderer, arrow_x, arrow_y, p2_x, p2_y);
}

