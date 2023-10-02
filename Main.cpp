#include <iostream>
#include "SDL.h"
#include "Defs.h"
#include "Input.h"
#include "Particle.h"
#include <vector>
#include <cmath>
#include <random>

using namespace std;

vector<Particle> red_particles;
vector<Particle> blue_particles;
vector<Particle> green_particles;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator
std::uniform_int_distribution<> wdistr(0, WIDTH);
std::uniform_int_distribution<> hdistr(0, HEIGHT);// define the range

//Particle* red_particles_arr[10000];
//Particle* blue_particles_arr[10000];

SDL_Window* window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


void GenerateParticles(int red_cout, int blue_count, int green_count) {

	for (int i = 0; i < red_cout; i++)
		red_particles.push_back(Particle(wdistr(gen), hdistr(gen), 5, 5, 1.0f, 1.0f, 255, 0, 0));
		

	for (int i = 0; i < green_count; i++)
		green_particles.push_back(Particle(wdistr(gen),hdistr(gen), 5, 5, 0.0f, 0.0f, 0, 255, 0));

	for (int i = 0; i < blue_count; i++)
		blue_particles.push_back(Particle(wdistr(gen), hdistr(gen), 5, 5, 0.0f, 0.0f, 255, 255, 255));
		

}

void DrawAllParticles(SDL_Renderer* renderer) {
	if (red_particles.size()>0)
		for (int i = 0; i <= red_particles.size() - 1; i++)
			red_particles[i].DrawCircle(renderer, 5);
		
	if (blue_particles.size() > 0)
		for (int i = 0; i <= blue_particles.size() - 1; i++)
			blue_particles[i].DrawCircle(renderer, 5);
		

	if (green_particles.size() > 0)
		for (int i = 0; i <= green_particles.size() - 1; i++)
			green_particles[i].DrawCircle(renderer, 5);
}

void applyRule(vector<Particle>* particle1, vector<Particle>* particle2, float strength) {

	for (int i = 0; i < particle1->size(); i++) {
		for (int j = 0; j < particle2->size(); j++) {
			if (&particle1->at(i) != &particle2->at(j)) {
				Particle* p1 = &particle1->at(i);
				Particle* p2 = &particle2->at(j);

				float dx = p2->x - p1->x;
				float dy = p2->y - p1->y;
				float distance = sqrt(pow(dx, 2) + pow(dy, 2));
				if (distance < 50) {

					float force = 1 / distance;
					float fx = dx / force;
					float fy = dy / force;
					
					
					p1->x_vel += fx * strength * 0.005;
					p1->y_vel += fy * strength * 0.005;
					
					if (p1->x <= 0 || p1->x >= WIDTH)
						p1->x_vel *= -1;
					if (p1->y <= 0 || p1->y >= HEIGHT)
						p1->y_vel *= -1;
					
					
					
						p1->x += p1->x_vel;
						p1->y += p1->y_vel;
					
				}

				
			}
		}
	}

	
}



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


	
	if (!window) {
		cout << "Error loading the window" << endl;
	}

	
	GenerateParticles(100, 1000, 0);
	while (1) {
		CheckInputs();
		SDL_RenderClear(renderer);
		DrawAllParticles(renderer);
		applyRule(&blue_particles, &red_particles, 10);
		applyRule(&green_particles, &blue_particles, -0.001);
		
		
		//applyRule(&red_particles, &blue_particles, -0.001);
		/*applyRule(&red_particles, &red_particles, 5);*/
		applyRule(&blue_particles, &blue_particles, 0.001);
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}

	cin.get();
	return 0;
}