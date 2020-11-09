#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int MULTIPLIER = 10;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect rects[SCREEN_WIDTH/MULTIPLIER];

int random_Values[SCREEN_WIDTH/MULTIPLIER];


void render(int idd) {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );		
	for(int i = 0; i < SCREEN_WIDTH/MULTIPLIER; i++) {	
        if(i == idd) {
            SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
        } else {
            SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
        }
		SDL_RenderFillRect( renderer, &(rects[i]) );
	}
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

void swap(SDL_Rect arr[], int a, int b) {
    int tempY = arr[a].y;
    int tempH = arr[a].h;
    arr[a].h = arr[b].h;
    arr[a].y = arr[b].y;
    arr[b].h = tempH;
    arr[b].y = tempY;
} 

int partition(SDL_Rect arr[], int start, int end, int pivot, int idd) {

    render(idd);
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
        }
        
    }
    render(idd);
    return start;

}

void quick_sort(SDL_Rect arr[], int start, int end) {
    if(start >= end) {
        return;
    }
    start = static_cast<double>(start);
    end = static_cast<double>(end);
    double id = floor((start + end)/2);
    int idd = static_cast<int>(id);

    int pivot = arr[idd].h;
    int index = partition(arr, start, end, pivot, idd);
    quick_sort(arr, start, index-1);
    render(idd);
    quick_sort(arr, index, end);

}

bool initialize() {
    for(int i = 0; i < SCREEN_WIDTH/MULTIPLIER; i++) {
        random_Values[i] = rand() % ((SCREEN_HEIGHT) - 10 + 1) + 10;
    }

    for(int i = 0; i < SCREEN_WIDTH/MULTIPLIER; i++) {
        rects[i] = { i * MULTIPLIER, SCREEN_HEIGHT - random_Values[i], 7, random_Values[i]};
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to initialize : %s", SDL_GetError());
        return false;
    } else {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

        window = SDL_CreateWindow("SDL_Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
        
        if(window == nullptr) {
            printf("Failed to create window : %s", SDL_GetError());
            return false;
        } else {
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if(renderer == nullptr)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                return false;
			}
			else
			{
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					return false;
				}
			}
        }
    }
    return true;
}

void close() {
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
	SDL_Quit();
}

int main(int argc, char* args[]) {
    if(initialize()) {
        bool quit = false;
        SDL_Event e;

        quick_sort(rects, 0, SCREEN_WIDTH/MULTIPLIER - 1);

        while(!quit) {
            while(SDL_PollEvent(&e) != 0) {
                if(e.type == SDL_QUIT )  {
                    quit = true;
                }
            }
        
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		    SDL_RenderClear( renderer );
			SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );		
		    for(int i = 0; i < SCREEN_WIDTH/MULTIPLIER; i++) {		
			    SDL_RenderFillRect( renderer, &(rects[i]) );
		    }
            SDL_RenderPresent(renderer);
            
        }
    }
}



