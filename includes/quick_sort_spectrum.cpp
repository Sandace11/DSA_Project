#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <iostream>
#include <cmath>
#include <ctime>

#include "./quick_sort_spectrum.h"
#include "../lib/color.h"

#define PI 3.14159265358979323846

namespace sort_window_spectrum{
	// window properties
	bool window_open;
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 600;
	SDL_Event event;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
}

namespace sort_params_spectrum {
	// sorting array rendering properties
	bool sorted;
	bool paused;
	int delay_rate;
	const float INCREMENTS = 1;
	const int RADIUS = 200;
	const int NO_OF_VALUES = 360 / INCREMENTS;
	int random_color_values[NO_OF_VALUES];
}

void init_parameters_spectrum() {
	srand(time(nullptr));

	//Assigning random values to random_color_values array
	for(int i = 0; i < 360 / sort_params_spectrum::INCREMENTS; i++) {
		sort_params_spectrum::random_color_values[i] = rand() % (359 + 1);
	}

	sort_params_spectrum::sorted = false;
	sort_params_spectrum::paused = false;
	sort_params_spectrum::delay_rate = 50; // 50 milliseconds

	sort_window_spectrum::window_open = true;
}

bool initialize_spectrum() {
	//Initializing SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize : %s", SDL_GetError());
		return false;
	} 

	//Setting texture filtering to linear
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	sort_window_spectrum::window = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, sort_window_spectrum::SCREEN_WIDTH, 
			sort_window_spectrum::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	if(sort_window_spectrum::window == nullptr) {
		printf("Failed to create window : %s", SDL_GetError());
		return false;
	} 

	sort_window_spectrum::renderer = SDL_CreateRenderer( sort_window_spectrum::window, -1, SDL_RENDERER_ACCELERATED );
	if(sort_window_spectrum::renderer == nullptr)
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	init_parameters_spectrum();
	return true;
}

void close_window_spectrum() {
	SDL_DestroyWindow(sort_window_spectrum::window);
	sort_window_spectrum::window = nullptr;
	SDL_DestroyRenderer(sort_window_spectrum::renderer);
	sort_window_spectrum::renderer = nullptr;

	SDL_Quit();
}

void render_spectrum() {
	SDL_SetRenderDrawColor( sort_window_spectrum::renderer, 0x12, 0x12, 0x12, 0xFF );
	SDL_RenderClear( sort_window_spectrum::renderer);	

	for(float ang = 0; ang <= 360 - sort_params_spectrum::INCREMENTS; 
			ang += sort_params_spectrum::INCREMENTS) {
		int x = sort_params_spectrum::RADIUS * cos(ang * (PI / 180.0)) + 
			sort_window_spectrum::SCREEN_WIDTH / 2;
		int y = sort_params_spectrum::RADIUS * sin(ang * (PI / 180.0)) + 
			sort_window_spectrum::SCREEN_HEIGHT / 2;
		int v = ang / sort_params_spectrum::INCREMENTS;	

		SDL_Color color = convert_HSL_to_RGB(sort_params_spectrum::random_color_values[v], 90, 50);
		SDL_SetRenderDrawColor( sort_window_spectrum::renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(sort_window_spectrum::renderer, sort_window_spectrum::SCREEN_WIDTH/2, 
				sort_window_spectrum::SCREEN_HEIGHT/2, x, y);
	}

	SDL_RenderPresent(sort_window_spectrum::renderer);
	SDL_Delay(sort_params_spectrum::delay_rate);
}

void swap_spectrum(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
} 

int partition_spectrum(int arr[], int start, int end, int pivot_index) {
	int pivot = arr[pivot_index];
	while(start <= end) {
		while(arr[start] < pivot) {
			start++;
		}

		while(arr[end] > pivot) {
			end--;
		}

		if(start <= end) {
			swap_spectrum(&arr[start], &arr[end]);
			start++;
			end--;
			render_spectrum();
		}
	}
	return start;

}

void quick_sort_spectrum(int arr[], int start, int end) {
	// poll for events while in the quick sort recursive calls
	while(SDL_PollEvent(&sort_window_spectrum::event) != 0) {
		if(sort_window_spectrum::event.type == SDL_QUIT )  {
			sort_window_spectrum::window_open = false;
			sort_params_spectrum::sorted = true;
		}

		if (sort_window_spectrum::event.type == SDL_KEYDOWN) {
			SDL_Keysym key_pressed = sort_window_spectrum::event.key.keysym;

			if (key_pressed.scancode == SDL_SCANCODE_RIGHT) {
				if (sort_params_spectrum::delay_rate > 0)
					sort_params_spectrum::delay_rate -= 10;
			}

			if (key_pressed.scancode == SDL_SCANCODE_LEFT) {
				sort_params_spectrum::delay_rate += 10;
			}

			if (key_pressed.scancode == SDL_SCANCODE_SPACE) {
				sort_params_spectrum::paused = !sort_params_spectrum::paused;
			}
		}
	}

	if (sort_params_spectrum::paused || sort_params_spectrum::sorted)
		return;

	if(start >= end) {
		return;
	}
	int pivot_index = floor((start + end)/2);
	int index = partition_spectrum(arr, start, end, pivot_index);
	quick_sort_spectrum(arr, start, index-1);
	quick_sort_spectrum(arr, index, end);
}

void visualize_quick_sort_spectrum(){
	if(initialize_spectrum()) {
		while(sort_window_spectrum::window_open) {
			while(SDL_PollEvent(&sort_window_spectrum::event) != 0) {
				if(sort_window_spectrum::event.type == SDL_QUIT )  {
					sort_window_spectrum::window_open = false;
					sort_params_spectrum::sorted = true;
				}

				if (sort_window_spectrum::event.type == SDL_KEYDOWN) {
					SDL_Keysym key_pressed = sort_window_spectrum::event.key.keysym;

					if (key_pressed.scancode == SDL_SCANCODE_SPACE) {
						sort_params_spectrum::paused = !sort_params_spectrum::paused;
					}

					if (key_pressed.scancode == SDL_SCANCODE_R) {
						init_parameters_spectrum();
					}
				}
			}

			if (!sort_params_spectrum::sorted){
				quick_sort_spectrum(sort_params_spectrum::random_color_values, 0, 360 / sort_params_spectrum::INCREMENTS - 1);
				if (!sort_params_spectrum::paused)
					sort_params_spectrum::sorted = true;
			}
			render_spectrum();
		}
	}
	close_window_spectrum();
}
