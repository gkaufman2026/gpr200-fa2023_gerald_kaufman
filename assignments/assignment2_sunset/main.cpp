#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <gk/shader.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

struct Vertex {
	float x, y, z;
	float u, v;
};

Vertex vertices[4] = {
//    x      y      z      u     v
   {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f }, // Bottom left
   { 0.5f, -0.5f, -0.5f, 1.0f, 0.0f }, // Bottom right
   { 0.5f,  0.5f, -0.5f, 1.0f, 1.0f }, // Top right
   {-0.5f,  0.5f, -0.5f, 0.0f, 1.0f }  // Top left
};

unsigned int indices[6]{
	0, 1, 2, // TRIANGLE 1
	0, 2, 3 // TRIANGLE 2
};


bool showImGUIDemoWindow = true;

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned int* indicesData, int numIndices);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	//Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	shaderLib::ShaderLibrary shader("assets/vertexShader.vert", "assets/fragmentShader.frag");
	shader.use();

	unsigned int vao = createVAO(vertices, 4, indices, 6);

	float scale = 1.75;
	float sunColor[3] = {1.0, 0.5, 0.0};
	float sunPosY = 18.0;
	float sunSpeed = 0.5;
	float sunGlow = 5.0;
	float sunGlowBlur = 0.25;
	float sunGlowRadius = 0.05;
	float sunPosX = -1.75;
	float strength = 0.5;
	float frontForegroundHeight = 2.5;
	float backForegroundHeight = 3.0;
	float foregroundSlope = 0.1;
	float frontForegroundVary = 3.5;
	float backForegroundVary = 4.0;
	float foregroundColor[3] = {0.55, 0.3, 0.1};
	float foregroundTopColor[3] = {1.0, 1.0, 1.0};
	float sunGradient[3] = {1.0, 0.8, 0.6};

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		shader.setFloat("iScale", scale);
		shader.setFloat("iSunPosY", sunPosY);
		shader.setFloat("iSunSpeed", sunSpeed);
		shader.setFloat("iSunGlow", sunGlow);
		shader.setFloat("iSunGlowBlur", sunGlowBlur);
		shader.setFloat("iSunGlowRadius", sunGlowRadius);
		shader.setFloat("iSunPosX", sunPosX);
		shader.setFloat("iStrength", strength);
		shader.setFloat("iFrontForegroundHeight", frontForegroundHeight);
		shader.setFloat("iBackForegroundHeight", backForegroundHeight);
		shader.setFloat("iForegroundSlope", foregroundSlope);
		shader.setFloat("iFrontForegroundVary", frontForegroundVary);
		shader.setFloat("iBackForegroundVary", backForegroundVary);
		shader.setFloat("iTime", glfwGetTime());
		shader.setVec2("iResolution", SCREEN_WIDTH, SCREEN_HEIGHT);
		shader.setVec3("iSunColor", sunColor[0], sunColor[1], sunColor[2]);
		shader.setVec3("iForegroundColor", foregroundColor[0], foregroundColor[1], foregroundColor[2]);
		shader.setVec3("iForegroundTopColor", foregroundTopColor[0], foregroundTopColor[1], foregroundTopColor[2]);
		shader.setVec3("iSunGradient", sunGradient[0], sunGradient[1], sunGradient[2]);

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::Checkbox("Show Demo Window", &showImGUIDemoWindow);
			// SUN/MOUNTAIN SHAPING
			ImGui::SliderFloat("Sun Scale", &scale, 0.0f, 2.0f);
			ImGui::SliderFloat("Sun Pos (X)", &sunPosX, -2.0f, 18.0f);
			ImGui::SliderFloat("Sun Pos (Y)", &sunPosY, 0.0f, 18.0f);
			ImGui::SliderFloat("Sun Speed", &sunSpeed, 0.0f, 2.0f);
			ImGui::SliderFloat("Sun Glow", &sunGlow, 0.0f, 5.0f);
			ImGui::SliderFloat("Sun Glow Radius", &sunGlowRadius, 0.0f, 1.0f);
			ImGui::SliderFloat("Sun Glow Blur", &sunGlowBlur, 0.0f, 1.0f);
			ImGui::SliderFloat("Glow Strength", &strength, 0.0f, 1.0f);
			ImGui::SliderFloat("Mountain Height", &frontForegroundHeight, 0.0f, 3.0f);
			ImGui::SliderFloat("Top Mountain Height", &backForegroundHeight, 0.0f, 3.0f);
			ImGui::SliderFloat("Moutain Slope", &foregroundSlope, 0.0f, 1.0f);
			ImGui::SliderFloat("Montain Slope Vary", &frontForegroundVary, 0.0f, 5.0f);
			ImGui::SliderFloat("Top Montain Slope Vary", &backForegroundVary, 0.0f, 5.0f);
			// COLORS
			ImGui::ColorEdit3("Sun Color", sunColor);
			ImGui::ColorEdit3("Mountain Color", foregroundColor);
			ImGui::ColorEdit3("Top Mountain Color", foregroundTopColor);
			ImGui::ColorEdit3("Sun Gradient", sunGradient);

			ImGui::End();
			if (showImGUIDemoWindow) {
				ImGui::ShowDemoWindow(&showImGUIDemoWindow);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned int* indicesData, int numIndices) {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Define a new buffer id
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Allocate space for + send vertex data to GPU.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, vertexData, GL_STATIC_DRAW);

	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indicesData, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, x));
	glEnableVertexAttribArray(0);

	//UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, u));
	glEnableVertexAttribArray(1);

	return vao;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}