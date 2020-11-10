#ifndef CIRCLE_CLASS_DEFINED
#define CIRCLE_CLASS_DEFINED

#include <SDL2/SDL.h>

class Circle{
  private:
    int centre_x, centre_y, radius;
    
    SDL_Color fill_color;
    SDL_Color stroke_color = {0x00, 0x00, 0x00, 0xFF}; // default stroke = black
    int stroke_width;

  public:
    Circle();
    Circle(int x, int y, int r);

    ~Circle();

    void render_circle_outline(SDL_Renderer *renderer);
    void render_circle_fill(SDL_Renderer *renderer); // implementation remains

    void set_center(int x, int y);
    void set_radius(int r);
    void set_fill(SDL_Color color);
    void set_stroke(SDL_Color color, int width); // stroke is set to inside

    SDL_Point get_center();
    int get_radius();
};

#endif
