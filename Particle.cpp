#include "Particle.h"
#include "SDL.h"
#include <iostream>
Particle::Particle(int x_, int y_, int w_, int h_, float x_vel_, float y_vel_, int R_, int G_, int B_)
{
	std::cout << "Constructor running, chainging values" << std::endl;
	x = x_;	y = y_;	w= w_; h = h_;
	x_vel = x_vel_;	y_vel = y_vel_;
	R = R_; G = G_; B = B_;
}

void Particle::Draw(SDL_Renderer *renderer)
{	
	
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	

	SDL_SetRenderDrawColor(renderer, R, G, B, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
}
