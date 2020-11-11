#ifndef LINE_CLASS_DEFINED
#define LINE_CLASS_DEFINED

#include <SDL2/SDL.h>

class Line{
  private:
    int start_x, start_y; 
    int end_x, end_y;
    int thickness;

    int arrow_x, arrow_y;
    int arrow_direction;
    int arrow_length;

    enum direction { normal=0, reverse };
    enum arrow_point { beginning=0, middle, end}; 
    SDL_Color line_color;

  public:
    Line();
    Line(int sx, int sy, int ex, int ey, int t = 0, 
        SDL_Color color = {0x00, 0x00, 0x00, 0xff});
    ~Line();

    void set_line_starting_point(int x, int y);
    void set_line_ending_point(int x, int y);
    void set_line_thickness(int t);
    void set_line_color(SDL_Color color);
    
    void set_arrow_direction(int a_dir);
    void set_arrow_by_position(int pos);
    void set_arrow_by_point(int x, int y);
    void set_arrow_length(int len);

    void render_line(SDL_Renderer* renderer);
};

#endif
