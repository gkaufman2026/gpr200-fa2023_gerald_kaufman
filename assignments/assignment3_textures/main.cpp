#include <stdio.h>
#include <math.h>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <gk/texture.h> 
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ew/shader.h>

struct Vertex {
	float x, y, z;
	float u, v;
};

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned short* indicesData, int numIndices);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

Vertex vertices[4] = {
	{-1.0, -1.0, 0.0, 0.0, 0.0},
	{1.0, -1.0, 0.0, 1.0, 0.0},
	{1.0, 1.0, 0.0, 1.0, 1.0},
	{-1.0, 1.0, 0.0, 0.0, 1.0}
};
unsigned short indices[6] = {
	0, 1, 2,
	2, 3, 0
};

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures", NULL, NULL);
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

	ew::Shader background("assets/background.vert", "assets/background.frag");
	ew::Shader character("assets/character.vert", "assets/character.frag");

	unsigned int quadVAO = createVAO(vertices, 4, indices, 6);

	glBindVertexArray(quadVAO);

	// ORGANIZED TEXTURES INTO TEXTURES SUBDIRECTORY
	unsigned int backgroundTexture = loadTexture("assets/textures/background.png", 2, 0, 1); // replaced brick texture
	unsigned int secondBackgroundTexture = loadTexture("assets/textures/pokeball.png", 1, 1, 1);
	unsigned int noiseTexture = loadTexture("assets/textures/noise.png", 1, 0, 1);
	unsigned int characterTexture = loadTexture("assets/textures/character.png", 1, 1, 1);

	character.use();

	float noiseRate = 0.05;
	float posX = 0, posY = 0;
	int imageSizeWidth = 200;
	int imageSizeHeight = 200;
	float yAxisMovement = 0.0;
	float xAxisMovement = 0.0;
	float transparencyRate = 1.0;

	character.setFloat("_posX", posX);
	character.setFloat("_posY", posY);
	character.setVec2("_aspectRatio", SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		background.use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, backgroundTexture);
		background.setInt("_backgroundTexture", 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);
		background.setInt("_noiseTexture", 1);
		background.setFloat("iTime", float (glfwGetTime()));
		background.setFloat("_noiseRate", noiseRate);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, secondBackgroundTexture);
		background.setInt("_backgroundTexture", 2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		character.use();
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, characterTexture);
		character.setInt("_characterTexture", 3);
		character.setVec2("_imageSize", imageSizeWidth, imageSizeHeight);
		character.setFloat("_yAxisMovement", yAxisMovement);
		character.setFloat("_xAxisMovement", xAxisMovement);
		character.setFloat("iTime", float(glfwGetTime()));
		character.setFloat("_transparencyRate", transparencyRate);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

		//Render UI
		{
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("Settings");
			ImGui::SliderFloat("Distortion Rate", &noiseRate, 0.0f, 0.5f); // lowered it during development. TODO PUT BACK TO 1
			ImGui::InputInt("Img Scale (X-Axis)", &imageSizeWidth, 0, 512);
			ImGui::InputInt("Img Scale (Y-Axis)", &imageSizeHeight, 0, 512);
			ImGui::SliderFloat("Character Movement (X-Axis)", &xAxisMovement, -3.0f, 3.0f);
			ImGui::SliderFloat("Character Movement (Y-Axis)", &yAxisMovement, -1.75f, 1.75f);
			ImGui::SliderFloat("Character Opacity Speed", &transparencyRate, 1.0f, 2.0f);
			ImGui::End();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}

unsigned int createVAO(Vertex* vertexData, int numVertices, unsigned short* indicesData, int numIndices) {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Vertex Buffer Object 
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*numVertices, vertexData, GL_STATIC_DRAW);

	//Element Buffer Object
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * numIndices, indicesData, GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex,x));
	glEnableVertexAttribArray(0);

	//UV attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, u)));
	glEnableVertexAttribArray(1);

	return vao;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}