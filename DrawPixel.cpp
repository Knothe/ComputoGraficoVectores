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
#include <stack>
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

Matriz AskMatriz()
{
	std::queue<Matriz> q;
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
			q.push(t);
			numMatriz++;
		}
	}

	for (int i = 0; i < numMatriz; i++)
	{
		m = m * q.front();
		q.pop();
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

void DrawLine(Vector2* const v1, Vector2* const v2)
{
	Vector2 v;
	v = *v1;

	float n = 0;
	float m = (v2->GetY() - v1->GetY()) / (v2->GetX() - v1->GetX());
	float c = v1->GetY() - (m * v1->GetX());
	
	if (abs(m) < 1)
	{
		n = v2->GetX() - v1->GetX();
		n = n / 10;
		while (v.GetX() < v2->GetX())
		{
			v.SetX(v.GetX() + n);
			v.SetY((m * v.GetX()) + c);
			v.Draw(gRenderer);
		}

	}
	else if (abs(m) > 1)
	{
		n = v2->GetY() - v1->GetY();
		n = n / 10;
		
		while (v.GetY() < v2->GetY())
		{
			v.SetY(v.GetY() + n);
			v.SetX((v.GetY() - c) / m);
			v.Draw(gRenderer);
		}
	}
}

void DrawLine2(Vector2* const v1, Vector2* const v2)
{
	float dx, dy;
	int deno = 1;
	Vector2 v_Incr;
	Vector2 v;
	int i;

	dx = v2->GetX() - v1->GetX();
	dy = v2->GetY() - v1->GetY();

	if (abs(dy) < abs(dx))
		deno = abs(dx);
	else if (abs(dy) > abs(dx))
		deno = abs(dy);

	v_Incr.SetX(dx / deno);
	v_Incr.SetY(dy / deno);
	v = *v1;
	i = 0;

	for (int i = 0; i < deno; i++)
	{
		v = v + v_Incr;
		v.Draw(gRenderer);
	}

}


void DLHelpler(int x, int y, int dx, int dy, int modX, int modY)
{
	int i = 0;
	int p  = (2 * dy) - dx;
	if (dx > dy)
	{
		while (i < dx)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			x += modX;
			if (p < 0)
			{
				p = p + (2 * dy);
			}
			else
			{
				y += modY;
				p = p + (2 * (dy - dx));
			}
			i++;
		}
	}
	else
	{
		while (i < dy)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			y += modY;
			if (p < 0)
			{
				p = p + (2 * dx);
			}
			else
			{
				x += modX;
				p = p + (2 * (dx - dy));
			}
			i++;
		}
	}
}

void DrawLine3(Vector2 & const v1, Vector2 & const v2) 
{
	int x, y, p, dx, dy, i;
	i = 0;
	dx = v2.GetScreenX() - v1.GetScreenX();
	dy = v2.GetScreenY() - v1.GetScreenY();

	x = v1.GetScreenX();
	y = v1.GetScreenY();
	if (dx < 0)
	{
		if (dy < 0)
		{
			DLHelpler(x, y, abs(dx), abs(dy), -1, -1);
		}
		else
		{
			DLHelpler(x, y, abs(dx), abs(dy), -1, 1);
		}
	}
	else
	{
		if (dy < 0)
		{
			DLHelpler(x, y, abs(dx), abs(dy), 1, -1);
		}
		else
		{
			DLHelpler(x, y, abs(dx), abs(dy), 1, 1);
		}
	}
}

int main(int argc, char* args[])
{
	SetScreen(argc, args);

	
	std::stack<Matriz> i;
	Matriz change;
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
					std::cout << e.key.keysym.sym << std::endl;
					if (e.key.keysym.sym == 13 && v.size() != 0)
					{
						change = AskMatriz();
						SetVectores(&v, change);
						i.push(change.Inversa());
					}

					if (e.key.keysym.sym == 122 && i.size() > 0)
					{
						SetVectores(&v, i.top());
						i.pop();
					}
					
				}
			}

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);

			//Aqui puse todo lo del Draw para mejor orden
			DrawPlain();

			for (int i = 1; i < v.size(); i++)
			{
				DrawLine3(v[i-1], v[i]);
			}

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