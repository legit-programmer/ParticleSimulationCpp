#pragma once
#include "SDL.h"
class Particle
{	
public:Particle(int x, int y, int w, int h, float x_vel, float y_vel, int R, int G, int B);
public:
	int x, y, w, h;
	float x_vel, y_vel;
	int R, G, B;
public:
	void Draw(SDL_Renderer* renderer);
};

