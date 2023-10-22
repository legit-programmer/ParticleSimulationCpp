#include <iostream>
#include "SDL.h"
#include "Defs.h"
#include "Input.h"
#include "Particle.h"
#include <vector>
#include <cmath>
#include <random>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "GUI.h"
#include <stdio.h>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif


using namespace std;


vector<Particle> red_particles;
vector<Particle> blue_particles;
vector<Particle> green_particles;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd());		// seed the generator
std::uniform_int_distribution<> wdistr(0, WIDTH);
std::uniform_int_distribution<> hdistr(0, HEIGHT);// define the range

SDL_Window* window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


void GenerateParticles(int red_cout, int blue_count, int green_count) {

	for (int i = 0; i < red_cout; i++)
		red_particles.push_back(Particle(wdistr(gen), hdistr(gen), 10, 10, 0.0f, 0.0f, 255, 0, 0));
		

	for (int i = 0; i < green_count; i++)
		green_particles.push_back(Particle(wdistr(gen),hdistr(gen), 1, 1, 0.0f, 0.0f, 0, 255, 0));

	for (int i = 0; i < blue_count; i++)
		blue_particles.push_back(Particle(wdistr(gen), hdistr(gen), 1, 1, 0.0f, 0.0f, 0, 0, 255));
		

}


void DrawAllParticles(SDL_Renderer* renderer) {
	if (red_particles.size() > 0)
		for (int i = 0; i <= red_particles.size() - 1; i++)
			red_particles[i].Draw(renderer);
			//red_particles[i].DrawCircle(renderer, 5);
		
	if (blue_particles.size() > 0)
		for (int i = 0; i <= blue_particles.size() - 1; i++)
			blue_particles[i].Draw(renderer);

			//blue_particles[i].DrawCircle(renderer, 5);
		

	if (green_particles.size() > 0)
		for (int i = 0; i <= green_particles.size() - 1; i++)
			green_particles[i].Draw(renderer);

			//green_particles[i].DrawCircle(renderer, 5);
}

void applyRule(vector<Particle>* particle1, vector<Particle>* particle2, float strength) {

	for (int i = 0; i < particle1->size(); i++) {
		float fx = 0;
		float fy = 0;
		Particle* p1 = &particle1->at(i);
		for (int j = 0; j < particle2->size(); j++) {
			
				Particle* p2 = &particle2->at(j);

				float dx = p1->x - p2->x ;
				float dy = p1->y - p2->y;
				float distance = sqrt(pow(dx, 2) + pow(dy, 2));

				if (distance < 80 && distance>0) {

					float force = 1 / distance * strength;


					fx += dx * force;
					fy += dy * force;

				}
		}
		p1->x_vel = (p1->x_vel + fx)*0.5;
		p1->y_vel = (p1->y_vel + fy) * 0.5;
		
		p1->x += p1->x_vel;
		p1->y += p1->y_vel;
										
		if (p1->x <= 0 || p1->x >= WIDTH)
			p1->x_vel = p1->x_vel* (-5);
			

		if (p1->y <= 0 || p1->y >= HEIGHT)
			p1->y_vel = p1->y_vel * (-1);
					
					
					
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

#ifdef SDL_HINT_IME_SHOW_UI
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif


	
	if (!window) {
		cout << "Error loading the window" << endl;
	}

	if (!renderer) {
		cout << "No renderer"<<endl;
	}
	else {
		cout << "renderer initialized" << endl;
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;    
	

	
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
	
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	
	
	while (1) {
		CheckInputs(window, renderer);
		
		PrepareGUIComponent(&red_particles, &green_particles, &blue_particles);
		
		SDL_RenderClear(renderer);

		DrawAllParticles(renderer);

		RenderGUI(renderer, io);
		
		ApplyAllRules(&red_particles, &green_particles, &blue_particles);
		SDL_RenderPresent(renderer);
		
	}

	std::cin.get();
	return 0;
}


