#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "SDL.h"
#include <vector>
#include "Particle.h"
#include <iostream>
#include <random>

void applyRule(std::vector<Particle>* particle1, std::vector<Particle>* particle2, float strength);
void GenerateParticles(int red_cout, int blue_count, int green_count);


//std::uniform_int_distribution<> range()
std::uniform_real_distribution<> range(-2.10f, 2.10f);


float R2R = 0.0f;
float R2G = 0.0f;
float R2B = 0.0f;

float G2G = 0.0f;
float G2R = 0.0f;
float G2B = 0.0f;

float B2B = 0.0f;
float B2R = 0.0f;
float B2G = 0.0f;

int amount_r;
int amount_g;
int amount_b;

void ClearVector(std::vector<Particle>* particles) {
	particles->clear();
}

void RefreshParticles(std::vector<Particle>* particle1, std::vector<Particle>* particle2, std::vector<Particle>* particle3) {
	ClearVector(particle1);
	ClearVector(particle2);
	ClearVector(particle3);

	GenerateParticles(amount_r, amount_b, amount_g);
}

void PrepareGUIComponent(std::vector<Particle>* particle1, std::vector<Particle>* particle2, std::vector<Particle>* particle3) {

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Rules", 0);   
	if (ImGui::Button("Clear All", ImVec2(100, 40))) {
		{
			ClearVector(particle1);
			ClearVector(particle2);
			ClearVector(particle3);
			amount_r = amount_g = amount_b = 0;
		}
	}

	if (ImGui::Button("Reset", ImVec2(100, 40))) {
		R2R = R2G = R2B = G2G = G2R = G2B = B2G = B2B = B2R = 0.0f;
		
	}
	
	if (ImGui::Button("Random", ImVec2(100, 40))) {
		std::random_device rd;
		std::mt19937 gen(rd()); // seed the generator

		
		R2R = range(gen);
		R2G = range(gen);
		R2B = range(gen);
		G2G = range(gen);
		G2R = range(gen);
		G2B = range(gen);
		B2B = range(gen);
		B2R = range(gen);
		B2G = range(gen);

	}



	ImGui::SetWindowFontScale(2.0f);


	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "RED");
	ImGui::SetWindowFontScale(1.5f);
	
	if (ImGui::Button("ClearR", ImVec2(80, 40))) {
		ClearVector(particle1);
	}
	if (ImGui::SliderInt("AmountR", &amount_r, 0, 1000)) {
		RefreshParticles(particle1, particle2, particle3);
	}
	
	ImGui::SliderFloat("REDxRED", &R2R, -10.10f, 10.10f);
	ImGui::SliderFloat("REDxGREEN", &R2G, -10.10f, 10.10f);
	ImGui::SliderFloat("REDxBLUE", &R2B, -10.10f, 10.10f);
	
	ImGui::SetWindowFontScale(2.0f);
	ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "GREEN");
	ImGui::SetWindowFontScale(1.5f);
	if (ImGui::Button("ClearG", ImVec2(80, 40))) {
		ClearVector(particle2);
	}
	if (ImGui::SliderInt("AmountG", &amount_g, 0, 1000)) {
		RefreshParticles(particle1, particle2, particle3);
	}
	
	ImGui::SliderFloat("GREENxRED", &G2R, -10.10f, 10.10f);
	ImGui::SliderFloat("GREENxGREEN", &G2G, -10.10f, 10.10f);
	ImGui::SliderFloat("GREENxBLUE", &G2B, -10.10f, 10.10f);

	ImGui::SetWindowFontScale(2.0f);
	ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "BLUE");
	ImGui::SetWindowFontScale(1.5f);
	if (ImGui::Button("ClearB", ImVec2(
		80, 40))) {
		ClearVector(particle3);
	}
	if (ImGui::SliderInt("AmountB", &amount_b, 0, 1000)) {
		RefreshParticles(particle1, particle2, particle3);
	}

	ImGui::SliderFloat("BLUExRED", &B2R, -10.10f, 10.10f);
	ImGui::SliderFloat("BLUExGREEN2", &B2G, -10.10f, 10.10f);
	ImGui::SliderFloat("BLUExBLUE", &B2B, -10.10f, 10.10f);



	ImGui::End();

}

void RenderGUI(SDL_Renderer* renderer, ImGuiIO& io) {
	ImGui::Render();
	SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

void ApplyAllRules(std::vector<Particle>* red_particles, std::vector<Particle>* green_particles, std::vector<Particle>* blue_particles) {
	applyRule(red_particles, red_particles, R2R);
	applyRule(red_particles, green_particles, R2G);
	applyRule(red_particles, blue_particles, R2B);

	applyRule(green_particles, red_particles, G2R);
	applyRule(green_particles, green_particles, G2G);
	applyRule(green_particles, blue_particles, G2B);

	applyRule(blue_particles, red_particles, B2R);
	applyRule(blue_particles, green_particles, B2G);
	applyRule(blue_particles, blue_particles, B2B);
}
