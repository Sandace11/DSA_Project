#ifndef CIRCLE_CLASS_DEFINED
#define CIRCLE_CLASS_DEFINED

#include <SDL2/SDL.h>

class Circle{
  private:
    int centre_x, centre_y, radius;
    int node_weight;

    int stroke_width;
    SDL_Color stroke_color; // default stroke = black
    SDL_Rect text_box;
    
    char node_char;
    SDL_Texture* font_texture;

  public:
    Circle();
    Circle(int x, int y, int r, int node_wt = -1, char node_ch = '*',
        int s_width = 0, SDL_Color s_color = {0x00, 0x00, 0x00, 0xFF});

    ~Circle();

    void render_circle_outline(SDL_Renderer *renderer);

    void set_center(int x, int y);
    void set_radius(int r);
    void set_stroke(SDL_Color color, int width); // stroke is set to inside

    SDL_Texture* load_font(SDL_Renderer* renderer, const char *font_path, int font_size, 
        const SDL_Color font_color = {0x00, 0x00, 0x00, 0xFF});
    SDL_Point get_center();
    int get_radius();
};

#endif
