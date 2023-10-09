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
	rect.w = 2;
	rect.h = 2;
	
    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}


void Particle::DrawCircle(SDL_Renderer* renderer, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        
	    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
        SDL_RenderDrawPoint(renderer, this->x + x, this->y - y);
        SDL_RenderDrawPoint(renderer, this->x + x, this->y + y);
        SDL_RenderDrawPoint(renderer, this->x - x, this->y - y);
        SDL_RenderDrawPoint(renderer, this->x - x, this->y + y);
        SDL_RenderDrawPoint(renderer, this->x + y, this->y - x);
        SDL_RenderDrawPoint(renderer, this->x + y, this->y + x);
        SDL_RenderDrawPoint(renderer, this->x - y, this->y - x);
        SDL_RenderDrawPoint(renderer, this->x - y, this->y + x);
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
