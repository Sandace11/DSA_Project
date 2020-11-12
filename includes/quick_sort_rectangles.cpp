#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

#include "./quick_sort_rectangles.h"

namespace sort_window_rects{
	// window properties
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 600;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
}

namespace sort_params_rects {
	// sorting array rendering properties
	const int MULTIPLIER = 10;
	int random_value_array[sort_window_rects::SCREEN_WIDTH/MULTIPLIER];
	SDL_Rect rects[sort_window_rects::SCREEN_WIDTH/MULTIPLIER];
}

bool initialize_window_rects() {
	srand(time(NULL));

	for(int i = 0; i < sort_window_rects::SCREEN_WIDTH/sort_params_rects::MULTIPLIER; i++) {
		sort_params_rects::random_value_array[i] = 
			rand() % ((sort_window_rects::SCREEN_HEIGHT) - 10 + 1) + 10;
	}

	for(int i = 0; i < sort_window_rects::SCREEN_WIDTH/sort_params_rects::MULTIPLIER; i++) {
		sort_params_rects::rects[i] = { i * sort_params_rects::MULTIPLIER, 
			sort_window_rects::SCREEN_HEIGHT -	sort_params_rects::random_value_array[i], 
			7, sort_params_rects::random_value_array[i]};
	}

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
	SDL_SetRenderDrawColor( sort_window_rects::renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	return true;
}

void close_window_rects() {
	SDL_DestroyWindow(sort_window_rects::window);
	sort_window_rects::window = nullptr;
	SDL_DestroyRenderer(sort_window_rects::renderer);
	sort_window_rects::renderer = nullptr;
	SDL_Quit();
}

void render_rects(int pivot_index) {
	SDL_SetRenderDrawColor( sort_window_rects::renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( sort_window_rects::renderer );
	SDL_SetRenderDrawColor( sort_window_rects::renderer, 0x00, 0x00, 0x00, 0xFF );		
	for(int i = 0; i < sort_window_rects::SCREEN_WIDTH/sort_params_rects::MULTIPLIER; i++) {	
		if(i == pivot_index) 
			SDL_SetRenderDrawColor( sort_window_rects::renderer, 0x00, 0xFF, 0x00, 0xFF );
		else 
			SDL_SetRenderDrawColor( sort_window_rects::renderer, 0x00, 0x00, 0x00, 0xFF );

		SDL_RenderFillRect( sort_window_rects::renderer, &(sort_params_rects::rects[i]) );
	}
	SDL_RenderPresent(sort_window_rects::renderer);
	SDL_Delay(20);
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
				quick_sort_rects(sort_params_rects::rects, 0, sort_window_rects::SCREEN_WIDTH/sort_params_rects::MULTIPLIER - 1);
				sorted = true;
			}
			SDL_SetRenderDrawColor( sort_window_rects::renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( sort_window_rects::renderer );
			SDL_SetRenderDrawColor( sort_window_rects::renderer, 0x00, 0xFF, 0x00, 0xFF );		
			for(int i = 0; i < sort_window_rects::SCREEN_WIDTH/sort_params_rects::MULTIPLIER; i++) {		
				SDL_RenderFillRect( sort_window_rects::renderer,
						&(sort_params_rects::rects[i]) );
			}
			SDL_RenderPresent(sort_window_rects::renderer);
		}
	}
	close_window_rects();
}
