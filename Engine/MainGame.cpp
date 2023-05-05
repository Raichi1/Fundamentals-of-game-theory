#include "MainGame.h"
#include "Error.h"
#include "Window.h"
#include "Sprite.h"
#include <iostream>

using namespace std;
MainGame::MainGame() {
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
	time = 0;
}

MainGame::~MainGame() {

}

void MainGame::initShaders() {
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << event.motion.x << ", " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	//window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	window.create("HOLA", width, height, 0);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("GLEW not initialized");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);//La Candidad de pantallas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//R, G, B, A(Transparencia)
	initShaders();
}

void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.002;
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	sprite.draw();
	program.unuse();
	//si tengo elementos actualizo
	window.swapWindow();//Intercambia las pantallas en cada actualización
}
void MainGame::update() {
	while (gameState != GameState::EXIT) {
		draw();
		processInput();
	}
}
void MainGame::run() {
	init();
	sprite.init(-1, -1, 1, 1, "Textures/pikachu.png");
	update();
}