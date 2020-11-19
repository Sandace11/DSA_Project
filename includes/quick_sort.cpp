#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

#include "./quick_sort.h"

namespace sort_window{
    // window properties
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 600;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
}

namespace sort_params {
    // sorting array rendering properties
    const int MULTIPLIER = 10;
    int random_value_array[sort_window::SCREEN_WIDTH/MULTIPLIER];
    SDL_Rect rects[sort_window::SCREEN_WIDTH/MULTIPLIER];
}

bool initialize_window() {
	srand(time(NULL));

	for(int i = 0; i < sort_window::SCREEN_WIDTH/sort_params::MULTIPLIER; i++) {
		sort_params::random_value_array[i] = rand() % ((sort_window::SCREEN_HEIGHT) - 10 + 1) + 10;
	}

	for(int i = 0; i < sort_window::SCREEN_WIDTH/sort_params::MULTIPLIER; i++) {
		sort_params::rects[i] = { i * sort_params::MULTIPLIER, sort_window::SCREEN_HEIGHT -
			sort_params::random_value_array[i], 7, sort_params::random_value_array[i]};
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize : %s", SDL_GetError());
		return false;
	} 

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

void render(int pivot_index) {
	SDL_SetRenderDrawColor( sort_window::renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( sort_window::renderer );
	SDL_SetRenderDrawColor( sort_window::renderer, 0x00, 0x00, 0x00, 0xFF );		
	for(int i = 0; i < sort_window::SCREEN_WIDTH/sort_params::MULTIPLIER; i++) {	
		if(i == pivot_index) 
			SDL_SetRenderDrawColor( sort_window::renderer, 0x00, 0xFF, 0x00, 0xFF );
		else 
			SDL_SetRenderDrawColor( sort_window::renderer, 0x00, 0x00, 0x00, 0xFF );

		SDL_RenderFillRect( sort_window::renderer, &(sort_params::rects[i]) );
	}
	SDL_RenderPresent(sort_window::renderer);
	SDL_Delay(20);
}

void swap(SDL_Rect arr[], int a, int b) {
	int tempY = arr[a].y;
	int tempH = arr[a].h;
	arr[a].h = arr[b].h;
	arr[a].y = arr[b].y;
	arr[b].h = tempH;
	arr[b].y = tempY;
} 

int partition(SDL_Rect arr[], int start, int end, int pivot_index) {
	int pivot = arr[pivot_index].h;
	while(start <= end) {
		while(arr[start].h < pivot) {
			start++;
		}

		while(arr[end].h > pivot) {
			end--;
		}

		if(start <= end) {
			swap(arr, start, end);
			start++;
			end--;
			render(pivot_index);
		}
	}
	return start;

}

void quick_sort(SDL_Rect arr[], int start, int end) {
	if(start >= end) {
		return;
	}
	int pivot_index = floor((start + end)/2);
	int index = partition(arr, start, end, pivot_index);
	quick_sort(arr, start, index-1);
	quick_sort(arr, index, end);
}

void visualize_quick_sort(){
	if(initialize_window()) {
		bool quit = false;
		SDL_Event e;

		bool sorted = false;
		while(!quit) {
			while(SDL_PollEvent(&e) != 0) {
				if(e.type == SDL_QUIT || e.type == SDL_KEYUP )  {
					quit = true;
				}
			}

			if (!sorted){
				quick_sort(sort_params::rects, 0, sort_window::SCREEN_WIDTH/sort_params::MULTIPLIER - 1);
				sorted = true;
			}

			SDL_SetRenderDrawColor( sort_window::renderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( sort_window::renderer );
			SDL_SetRenderDrawColor( sort_window::renderer, 0x00, 0xFF, 0x00, 0xFF );		
			for(int i = 0; i < sort_window::SCREEN_WIDTH/sort_params::MULTIPLIER; i++) {		
				SDL_RenderFillRect( sort_window::renderer, &(sort_params::rects[i]) );
			}
			SDL_RenderPresent(sort_window::renderer);
		}
	}
	close_window();
}
