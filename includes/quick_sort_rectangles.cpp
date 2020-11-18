#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <cmath>
#include <ctime>

#include "../lib/color.h"
#include "./quick_sort_rectangles.h"

namespace sort_window_rects{
	// window properties
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 600;
	bool window_open;
	SDL_Event event;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
}

namespace sort_params_rects {
	// sorting array rendering properties
	bool sorted;
	bool paused;
	const int MULTIPLIER = 10;
	const int number_of_rects = sort_window_rects::SCREEN_WIDTH/MULTIPLIER;
	int delay_rate;
	int random_value_array[number_of_rects];
	SDL_Rect rects[number_of_rects];
}

void init_parameters_rects(){
	// intitialize array containing random values
	srand(time(NULL));

	for(int i = 0; i < sort_params_rects::number_of_rects; i++) {
		sort_params_rects::random_value_array[i] = 
			rand() % ((sort_window_rects::SCREEN_HEIGHT) - 10 + 1) + 10;
	}

	for(int i = 0; i < sort_params_rects::number_of_rects; i++) {
		sort_params_rects::rects[i] = { i * sort_params_rects::MULTIPLIER, 
			sort_window_rects::SCREEN_HEIGHT -	sort_params_rects::random_value_array[i], 
			7, sort_params_rects::random_value_array[i]};
	}

	// reset parameters to default before starting 
	sort_params_rects::paused = false;
	sort_params_rects::delay_rate = 50;
	sort_params_rects::sorted = false;

	sort_window_rects::window_open = true;
}

bool initialize_window_rects() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize : %s", SDL_GetError());
		return false;
	} 

	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	sort_window_rects::window = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, sort_window_rects::SCREEN_WIDTH, 
			sort_window_rects::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	if(sort_window_rects::window == nullptr) {
		printf("Failed to create window : %s", SDL_GetError());
		return false;
	} 

	sort_window_rects::renderer = SDL_CreateRenderer( sort_window_rects::window, 
			-1, SDL_RENDERER_ACCELERATED );

	if(sort_window_rects::renderer == nullptr)
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	init_parameters_rects();
	return true;
}


void close_window_rects() {
	SDL_DestroyWindow(sort_window_rects::window);
	sort_window_rects::window = nullptr;
	SDL_DestroyRenderer(sort_window_rects::renderer);
	sort_window_rects::renderer = nullptr;

	SDL_Quit();
}

void render_rects(int pivot_index, bool sorted) {
	SDL_SetRenderDrawColor( sort_window_rects::renderer, 0x12, 0x12, 0x12, 0xFF );
	SDL_RenderClear( sort_window_rects::renderer );

	double t_hue;
	SDL_Color t_color;
	for(int i = 0; i < sort_params_rects::number_of_rects; i++) {	
		if(i == pivot_index && sorted == false) 
			SDL_SetRenderDrawColor( sort_window_rects::renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		else{ 
			t_hue = double(sort_params_rects::rects[i].h - 10) * 360 / 590;
			t_color = convert_HSL_to_RGB(t_hue, 55, 40);
			SDL_SetRenderDrawColor( sort_window_rects::renderer, t_color.r, t_color.g, 
					t_color.b, 0xFF );
		}

		SDL_RenderFillRect( sort_window_rects::renderer, &(sort_params_rects::rects[i]) );
	}
	if (!sorted) {
		SDL_RenderPresent(sort_window_rects::renderer);
	}
	SDL_Delay(sort_params_rects::delay_rate);
}

void swap_rects(SDL_Rect arr[], int a, int b) {
	int tempY = arr[a].y;
	int tempH = arr[a].h;
	arr[a].h = arr[b].h;
	arr[a].y = arr[b].y;
	arr[b].h = tempH;
	arr[b].y = tempY;
} 

int partition_rects(SDL_Rect arr[], int start, int end, int pivot_index) {
	int pivot = arr[pivot_index].h;
	while(start <= end) {
		while(arr[start].h < pivot) {
			start++;
		}

		while(arr[end].h > pivot) {
			end--;
		}

		if(start <= end) {
			swap_rects(arr, start, end);
			start++;
			end--;
			render_rects(pivot_index);
		}
	}
	return start;
}

void quick_sort_rects(SDL_Rect arr[], int start, int end) {
	while(SDL_PollEvent(&sort_window_rects::event) != 0) {

		if(sort_window_rects::event.type == SDL_QUIT )  {
			sort_window_rects::window_open = false;
			sort_params_rects::sorted = true;
		}

		if (sort_window_rects::event.type == SDL_KEYDOWN) {
			SDL_Keysym key_pressed = sort_window_rects::event.key.keysym;

			if (key_pressed.scancode == SDL_SCANCODE_RIGHT) {
				if (sort_params_rects::delay_rate > 0)
					sort_params_rects::delay_rate -= 10;
			}

			if (key_pressed.scancode == SDL_SCANCODE_LEFT) {
				sort_params_rects::delay_rate += 10;
			}

			if (key_pressed.scancode == SDL_SCANCODE_SPACE) {
				sort_params_rects::paused = !sort_params_rects::paused;
			}
		}
	}

	if (sort_params_rects::paused || sort_params_rects::sorted)
		return;

	if(start >= end) {
		return;
	}
	int pivot_index = floor((start + end)/2);
	int index = partition_rects(arr, start, end, pivot_index);
	quick_sort_rects(arr, start, index-1);
	quick_sort_rects(arr, index, end);

}

void visualize_quick_sort_rects(){
	if(initialize_window_rects()) {
		while(sort_window_rects::window_open) {
			while(SDL_PollEvent(&sort_window_rects::event) != 0) {
				if(sort_window_rects::event.type == SDL_QUIT )  {
					sort_window_rects::window_open = false;
					sort_params_rects::sorted = true;
				}
				
				if (sort_window_rects::event.type == SDL_KEYDOWN) {
					SDL_Keysym key_pressed = sort_window_rects::event.key.keysym;

					if (key_pressed.scancode == SDL_SCANCODE_SPACE) {
						sort_params_rects::paused = !sort_params_rects::paused;
					}

					if (key_pressed.scancode == SDL_SCANCODE_R) {
						init_parameters_rects();
					}
				}
			}

			SDL_SetRenderDrawColor( sort_window_rects::renderer, 0x12, 0x12, 0x12, 0xFF );
			SDL_RenderClear( sort_window_rects::renderer );

			if (!sort_params_rects::sorted){
				quick_sort_rects(sort_params_rects::rects, 0, sort_params_rects::number_of_rects - 1);
				if (!sort_params_rects::paused)
					sort_params_rects::sorted = true;
			}

			render_rects(0, true);
			SDL_RenderPresent(sort_window_rects::renderer);
		}
	}
	close_window_rects();
}
