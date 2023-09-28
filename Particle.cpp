#include "Particle.h"
#include "SDL.h"

Particle::Particle(int x, int y, int w, int h, float x_vel, float y_vel, int R, int G, int B)
{
	Particle::x = x;	Particle::y = y;	Particle::w= w; Particle::h = h;
	Particle::x_vel = x_vel;	Particle::y_vel = y_vel;
	Particle::R = R; Particle::G = G; Particle::B = B;
}

void Particle::Draw(SDL_Renderer *renderer)
{
	SDL_Rect rect;
	rect.x = Particle::x;
	rect.y = Particle::y;
	rect.w = Particle::w;
	rect.h = Particle::h;

	SDL_SetRenderDrawColor(renderer, R, G, B, 255);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}
