            #include "gui.hpp"

void GuiRenderer::render() {
	auto const config = Configuration::getInstance();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Info", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("FPS: %.2f", Frametime::getInstance()->getFramerate());
	ImGui::End();

	ImGui::Begin("Light", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SliderFloat3("Position", value_ptr(config->getLight()->lightPosition), -50, 50, "%.0f", ImGuiSliderFlags_None);
	ImGui::SliderFloat("Ambient Strength", &config->getLight()->ambientLightStrength, 0, 1, "%.2f", ImGuiSliderFlags_None);
	ImGui::SliderFloat("Difffuse Strength", &config->getLight()->diffuseLightStrength, 0, 1, "%.2f", ImGuiSliderFlags_None);
	ImGui::End();

	ImGui::Begin("Simulation", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SliderFloat("Gravity Modifier", &config->getSimulationParams()->gravityModifier, 0.00001f, 2.0f, "%.5f", ImGuiSliderFlags_Logarithmic);
	ImGui::SliderInt("Solver Iterations", &config->getSimulationParams()->iterations, 1, 10, "%d", ImGuiSelectableFlags_None);
	ImGui::SliderFloat("Stiffness", &config->getSimulationParams()->stiffness, 0.01, 0.99, "%.2f", ImGuiSelectableFlags_None);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GuiRenderer::GuiRenderer(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
	ImGui::StyleColorsDark();
}
