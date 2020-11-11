#ifndef CIRCLE_CLASS_DEFINED
#define CIRCLE_CLASS_DEFINED

#include <SDL2/SDL.h>

class Circle{
  private:
    int centre_x, centre_y, radius;
    
    SDL_Color stroke_color; // default stroke = black
    int stroke_width;

  public:
    Circle();
    Circle(int x, int y, int r, int s_width = 0, 
        SDL_Color s_color = {0x00, 0x00, 0x00, 0xFF});

    ~Circle();

    void render_circle_outline(SDL_Renderer *renderer);

    void set_center(int x, int y);
    void set_radius(int r);
    void set_stroke(SDL_Color color, int width); // stroke is set to inside

    SDL_Point get_center();
    int get_radius();
};

#endif
