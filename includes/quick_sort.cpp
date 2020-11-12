#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

#include "./quick_sort.h"
#include "../lib/color.h"

#define PI 3.14159265358979323846

namespace sort_window{
    // window properties
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 600;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
}

namespace sort_params {
    // sorting array rendering properties
	const float INCREMENTS = 1;
	const int RADIUS = 250;
	const int NO_OF_VALUES = 360 / INCREMENTS;
    int random_color_values[NO_OF_VALUES];
}

bool initialize() {
	srand(time(nullptr));
	
	//Assigning random values to random_color_values array
	for(int i = 0; i < 360 / sort_params::INCREMENTS; i++) {
        sort_params::random_color_values[i] = rand() % (359 + 1);
	}

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

	sort_window::window = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, sort_window::SCREEN_WIDTH, 
			sort_window::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	if(sort_window::window == nullptr) {
		printf("Failed to create window : %s", SDL_GetError());
		return false;
	} 

	sort_window::renderer = SDL_CreateRenderer( sort_window::window, -1, SDL_RENDERER_ACCELERATED );
	if(sort_window::renderer == nullptr)
	{
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	SDL_SetRenderDrawColor( sort_window::renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	return true;
}

void close_window() {
	SDL_DestroyWindow(sort_window::window);
	sort_window::window = nullptr;
	SDL_DestroyRenderer(sort_window::renderer);
	sort_window::renderer = nullptr;
	SDL_Quit();
}


void render() {
	SDL_SetRenderDrawColor( sort_window::renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( sort_window::renderer);	
	for(float ang = 0; ang <= 360 - sort_params::INCREMENTS; ang += sort_params::INCREMENTS) {
		int x = sort_params::RADIUS * cos(ang * (PI / 180.0)) + sort_window::SCREEN_WIDTH / 2;
		int y = sort_params::RADIUS * sin(ang * (PI / 180.0)) + sort_window::SCREEN_HEIGHT / 2;
		int v = ang / sort_params::INCREMENTS;	
		SDL_Color color = convert_HSL_to_RGB(sort_params::random_color_values[v], 100, 50);
		SDL_SetRenderDrawColor( sort_window::renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(sort_window::renderer, sort_window::SCREEN_WIDTH/2, sort_window::SCREEN_HEIGHT/2, x, y);
	}

	SDL_RenderPresent(sort_window::renderer);
	SDL_Delay(10);

}


void swap(int arr[], int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
} 

int partition(int arr[], int start, int end, int pivot_index) {
	int pivot = arr[pivot_index];
	while(start <= end) {
		while(arr[start] < pivot) {
			start++;
		}

		while(arr[end] > pivot) {
			end--;
		}

		if(start <= end) {
			swap(arr, start, end);
			start++;
			end--;
			render();
		}
	}
	return start;

}

void quick_sort(int arr[], int start, int end) {
	if(start >= end) {
		return;
	}
	int pivot_index = floor((start + end)/2);
	int index = partition(arr, start, end, pivot_index);
	quick_sort(arr, start, index-1);
	quick_sort(arr, index, end);
}

void visualize_quick_sort(){
	if(initialize()) {
		bool quit = false;
		SDL_Event e;

		bool sorted = false;
		while(!quit) {
			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT )  {
					quit = true;
				}
			}

			if (!sorted){
				quick_sort(sort_params::random_color_values, 0, 360 / sort_params::INCREMENTS - 1);
				sorted = true;
			}

			render();
		}
	}
	close_window();
}
