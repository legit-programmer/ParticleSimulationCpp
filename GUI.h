#pragma once
#include "SDL.h"
#include "imgui.h"



void PrepareGUIComponent(std::vector<Particle>* particle1, std::vector<Particle>* particle2, std::vector<Particle>* particle3);
void RenderGUI(SDL_Renderer* renderer, ImGuiIO& io);
void ApplyAllRules(std::vector<Particle>* red_particles, std::vector<Particle>* green_particles, std::vector<Particle>* blue_particles);