#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <math.h>
#include "Matriz.h"
#include "Vector2.h"
#include "Escalamiento.h"
#include "Traslacion.h"
#include "Rotacion.h"
#include <queue>
#include <vector>

//Screen dimension constants
int SCREEN_WIDTH = 720;
int SCREEN_HEIGHT = 480;
int tam = 30;

//Starts up SDL and creates window
bool init();


//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


			}
		}
	}

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	SDL_Quit();
}

void SetScreen(int argc, char* args[])
{
	std::cout << "Argc: " << argc << std::endl;

	//Si se inicia desde la consola, simplemente pasamos por todas las opciones posibles
	for (int i = 0; i < argc; i++)
	{
		//Las imprimimos para verificar
		std::cout << "args[" << i << "]: " << args[i];
	
		//Como no siempre van a ingresar valores, usamos este para saber cuales son los que ingresaron
		//atoi tiene definido que, si tiene un char y lo pasamos a int, lo va a meter como 0
		switch (i)
		{
		case 1: SCREEN_WIDTH = atoi(args[i]);
			std::cout << "    " << SCREEN_WIDTH;
			break;
		case 2: SCREEN_HEIGHT = atoi(args[i]);
			std::cout << "    " << SCREEN_HEIGHT;
			break;
		case 3: tam = atoi(args[i]);
			break;
		}
		std::cout << std::endl;
	}

	//En el caso que alguien ingrese un char en alguno de los 3 valores posibles, los pasamos al predeterminado
	if (SCREEN_WIDTH == 0 || SCREEN_HEIGHT == 0)
	{
		SCREEN_WIDTH = 720;
		SCREEN_HEIGHT = 480;
	}
	if (tam == 0)
	{
		tam = 32;
	}

}

void DrawPlain()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Dibujamos en y desde la mitad
	SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	for (int i = SCREEN_HEIGHT / 2; i < SCREEN_HEIGHT;)
	{
		i += tam;
		SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT - i);
		SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
	}

	//Dibujamos en x desde la mitad
	for (int i = SCREEN_WIDTH / 2; i < SCREEN_WIDTH;)
	{
		i += tam;
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, SCREEN_HEIGHT/2);
		SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT / 2);
	}

	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x44, 0x44, 0xFF);
	for (int i = (SCREEN_WIDTH / 2) + tam; i < SCREEN_WIDTH; i += tam)
	{
		for (int j = (SCREEN_HEIGHT / 2) + tam; j < SCREEN_HEIGHT; j += tam)
		{
			SDL_RenderDrawPoint(gRenderer, i, j);
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, j);
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, SCREEN_HEIGHT - j);
			SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT - j);
		}
	}

	
}

void DrawPoint(float x, float y)
{
	x = (SCREEN_WIDTH/2 ) + (tam * x);
	y = (SCREEN_HEIGHT/2 ) - (tam * y);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoint(gRenderer, x, y);
}

void PrintMenu()
{
	std::cout << "Seleccione una Matriz :" << std::endl;
	std::cout << "1) Traslacion" << std::endl;
	std::cout << "2) Escalamiento" << std::endl;
	std::cout << "3) Rotacion" << std::endl;
	std::cout << "4) Finalizar" << std::endl;
}

Matriz AskMatriz(std::queue<Matriz>* q)
{
	float x, y;
	unsigned n, numMatriz;
	Matriz m;
	Matriz t;

	numMatriz = n = 0;

	while (n != 4)
	{
		PrintMenu();
		std::cin >> n;
		switch (n)
		{
		case 1:
			std::cout << "Ingrese la traslación en x : ";
			std::cin >> x;
			std::cout << "Ingrese la traslación en y : ";
			std::cin >> y;
			t = Traslacion(x, y);
			break;
		case 2:
			std::cout << "Ingrese el escalamiento en x : ";
			std::cin >> x;
			std::cout << "Ingrese el escalamiento en y : ";
			std::cin >> y;
			t = Escalamiento(x, y);
			break;
		case 3:
			std::cout << "Ingrese la rotacion : ";
			std::cin >> x;
			t = Rotacion(x);
			break;
		case 4:
			std::cout << "Se ingresaron todas las modificaciones" << std::endl;
			break;
		}
		if (n < 4)
		{
			q->push(t);
			numMatriz++;
		}
	}

	for (int i = 0; i < numMatriz; i++)
	{
		m = m * q->front();
		q->pop();
	}
	m.Print();
	return m;
}

void SetVectores(std::vector<Vector2>* v, Matriz m)
{
	for (auto i = v->begin(); i != v->end(); i++)
	{
		*i = *i * m;
	}

	for (auto object : *v)
	{
		object.Print();
	}
}

int main(int argc, char* args[])
{
	SetScreen(argc, args);

	std::queue<Matriz> q;
	
	std::vector<Vector2> v;
	//v.resize(0);

	std::cout << "Presione enter para ingresar su matriz de transformacion " << std::endl;
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					std::cout << "Recibimos : " << e.button.x << ", " << e.button.y << std::endl;
					std::cout << "Type id: " << typeid(e.button.x).name() << std::endl;
					v.push_back(Vector2(e.button.x, e.button.y, SCREEN_HEIGHT, SCREEN_WIDTH, tam));
				}
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == 13 && v.size() != 0)
					{
						SetVectores(&v, AskMatriz(&q));
						std::cout << q.size();
					}
					
				}
			}

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);

			//Aqui puse todo lo del Draw para mejor orden
			DrawPlain();

			for (auto object : v)
			{
				object.Draw(gRenderer);
			}
			
			SDL_RenderPresent(gRenderer);
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}