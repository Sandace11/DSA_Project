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
  double p1_x, p1_y, p2_x, p2_y;


  int multiplier = 1;
  if (arrow_direction == reverse){
    multiplier = -1;
  }

  //Make unit vector along the line
  double magnitude = sqrt((pow(end_x-start_x, 2)) + pow(end_y-start_y, 2));
  double uvec_x = multiplier * (end_x - start_x)/magnitude;
  double uvec_y = multiplier * (end_y - start_y)/magnitude;
  //This retarded graphics library uses a coordinate system where y axis is reversed
  //Who does that?
  //


  //Turn that vector by 150degrees in clockwise and anti-c/w direction
  //We're setting it to 30 degrees for now
  double d1_x = (-0.866) * uvec_x + (-0.5) * uvec_y;
  double d1_y = (0.5) * uvec_x + (-0.866) * uvec_y;

  double d2_x = (-0.866) * uvec_x + 0.5 * uvec_y;
  double d2_y = (-0.5) * uvec_x + (-0.866) * uvec_y;

  double mid_x = (start_x + end_x)/2;
  double mid_y = (start_y + end_y)/2;

  p1_x = mid_x + arrow_length * d1_x;
  p2_x = mid_x + arrow_length * d2_x;
  p1_y = mid_y + arrow_length * d1_y;
  p2_y = mid_y + arrow_length * d2_y;

  SDL_RenderDrawLine(renderer, arrow_x, arrow_y, p1_x, p1_y);
  SDL_RenderDrawLine(renderer, arrow_x, arrow_y, p2_x, p2_y);
}
