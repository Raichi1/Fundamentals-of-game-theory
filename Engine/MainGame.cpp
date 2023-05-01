#include "MainGame.h"
#include "Error.h"
#include <iostream>
using namespace std;
MainGame::MainGame() {
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}

MainGame::~MainGame() {

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

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.linkShader();//Puente entre código y shader que tiene como función cerrar el puente
}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		fatalError("SDL not initialized");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
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
	//sprite.draw();
	//sprite1.draw();
	for (int i = 0; i < sprites.size(); i++)
		sprites.at(i).draw();
	program.unuse();
	//si tengo elementos actualizo
	SDL_GL_SwapWindow(window);//Intercambia las pantallas en cada actualización
}
void MainGame::update() {
	srand(time(NULL));
	int aux;
	time_t ti = time(NULL);
	while (gameState != GameState::EXIT) {
		time_t tf = time(NULL);
		if (difftime(tf, ti) >= 1 && sprites.size() < 10) {
			((rand() % 10) % 2 == 0) ? aux = 1 : aux = -1;
			sprites.push_back(Sprite());
			sprites.back().init(((float)(rand() % 8 + 1) / 10) * aux, ((float)(rand() % 8 + 1) / 10) * aux, 1, 1);
			ti = time(NULL);
		}
		draw();
		processInput();
	}
}
void MainGame::run() {
	init();
	update();
}