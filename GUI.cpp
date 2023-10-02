#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "SDL.h"
#include <vector>
#include "Particle.h"

void applyRule(std::vector<Particle>* particle1, std::vector<Particle>* particle2, float strength);

float R2R = 0.0f;
float R2G = 0.0f;
float R2B = 0.0f;

float G2G = 0.0f;
float G2R = 0.0f;
float G2B = 0.0f;

float B2B = 0.0f;
float B2R = 0.0f;
float B2G = 0.0f;

void ClearVector(std::vector<Particle>* particles) {
	particles->clear();
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
		}
	}
	ImGui::SetWindowFontScale(2.0f);


	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "RED");
	ImGui::SetWindowFontScale(1.5f);
	
	if (ImGui::Button("ClearR", ImVec2(80, 40))) {
		ClearVector(particle1);
	}

	ImGui::SliderFloat("REDxRED", &R2R, -3.0f, 3.0f);
	ImGui::SliderFloat("REDxGREEN", &R2G, -3.0f, 3.0f);
	ImGui::SliderFloat("REDxBLUE", &R2B, -3.0f, 3.0f);
	
	ImGui::SetWindowFontScale(2.0f);
	ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "GREEN");
	ImGui::SetWindowFontScale(1.5f);
	if (ImGui::Button("ClearG", ImVec2(80, 40))) {
		ClearVector(particle2);
	}
	ImGui::SliderFloat("GREENxRED", &G2R, -3.0f, 3.0f);
	ImGui::SliderFloat("GREENxGREEN", &G2G, -3.0f, 3.0f);
	ImGui::SliderFloat("GREENxBLUE", &G2B, -3.0f, 3.0f);
	
	ImGui::SetWindowFontScale(2.0f);
	ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "BLUE");
	ImGui::SetWindowFontScale(1.5f);
	if (ImGui::Button("ClearB", ImVec2(
80, 40))) {
		ClearVector(particle3);
	}
	ImGui::SliderFloat("BLUExRED", &B2R, -3.0f, 3.0f);
	ImGui::SliderFloat("BLUExGREEN2", &B2G, -3.0f, 3.0f);
	ImGui::SliderFloat("BLUExBLUE", &B2B, -3.0f, 3.0f);



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
