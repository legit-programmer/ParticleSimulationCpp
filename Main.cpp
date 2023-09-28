#include <iostream>
#include "SDL.h"
#include "Defs.h"
#include "Input.h"
#include "Particle.h"

using namespace std;

int main(int argc, char* argv[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	SDL_Window* window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Particle p1(10, 10, 50, 60, 0.0f, 0.0f, 255, 255, 255);

	if (!window) {
		cout << "Error loading the window" << endl;
	}
	
	
	
	

	while (1) {
		CheckInputs();
		SDL_RenderClear(renderer);
		p1.Draw(renderer);

		
		
		
		
	}


	cin.get();
	return 0;
}