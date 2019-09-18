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
	int x, y, dx, dy;
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

void DrawCircle(Vector2& const v1, Vector2& const v2) {
	int x, y, p;
	int r;
	r = sqrt(((v1.GetScreenX() - v2.GetScreenX()) * (v1.GetScreenX() - v2.GetScreenX())) + ((v1.GetScreenY() - v2.GetScreenY()) * (v1.GetScreenY() - v2.GetScreenY())));
	x = 0;
	y = r;
	p = 1 - r;
	do {
		if (p <= 0)
		{
			x = x + 1;
			p = p + (2 * x) + 3;
		}
		else if (p > 0)
		{
			x = x + 1;
			y = y - 1;
			p = (2 * x) - (2 * y) + 5 + p;
		}

		SDL_RenderDrawPoint(gRenderer, x + v1.GetScreenX(), y + v1.GetScreenY());
		SDL_RenderDrawPoint(gRenderer, x + v1.GetScreenX(), -y + v1.GetScreenY());
		SDL_RenderDrawPoint(gRenderer, -x + v1.GetScreenX(), y + v1.GetScreenY());
		SDL_RenderDrawPoint(gRenderer, -x + v1.GetScreenX(), -y + v1.GetScreenY());
		SDL_RenderDrawPoint(gRenderer, y + v1.GetScreenX(), x + v1.GetScreenY());
		SDL_RenderDrawPoint(gRenderer, y + v1.GetScreenX(), -x + v1.GetScreenY());
		SDL_RenderDrawPoint(gRenderer, -y + v1.GetScreenX(), x + v1.GetScreenY());
		SDL_RenderDrawPoint(gRenderer, -y + v1.GetScreenX(), -x + v1.GetScreenY());
	} while (x <= y);
	
}

float Power(float num, int pow) 
{
	if (pow == 0) {
		return 1;
	}
	else {
		return num * Power(num, pow - 1);
	}
}

int Factorial(int n) 
{
	if (n <= 1) {
		return 1;
	}
	else {
		return n * Factorial(n - 1);
	}
}

void BezierCurve(Vector2&const v1, Vector2& const v2, Vector2& const v3, Vector2& const v4)
{
	Vector2 v_draw;

	for (float t = 0; t <= 1; t += .0001) {
		v_draw = (v1 * Power(1 - t, 3)) + (v2 * 3 * t * Power(1 - t, 2)) + (v3 * 3 * Power(t, 2) * (1 - t)) + (v4 * Power(t, 3));
		v_draw.Draw(gRenderer);
	}
}

void BezierCurve(Vector2& const v1, Vector2& const v2, Vector2& const v3, Vector2& const v4, Vector2& const v5, Vector2& const v6, Vector2& const v7) {
	Vector2 v_draw;
	for (float t = 0; t <= 1; t += .0001) {
		v_draw = (v1 * Power(1 - t, 6)) + (v2* 6 * t * Power(1 - t, 5)) + (v3 * 15 * Power(t, 2) * Power(1 - t, 4)) + (v4 * 20 * Power(t, 3) * Power(1 - t, 3)) + (v5 * 15 * Power(t, 4) * Power(1 - t, 2)) + (v6 * 6 * Power(t, 5) * (1 - t)) + (v7 * Power(t, 6));
		v_draw.Draw(gRenderer);
	}
}

void BezierCurve(std::vector<Vector2> v) {
	int n = v.size() - 1;
	Vector2 v_draw;

	for (float t = 0; t <= 1; t += .0001) {
		v_draw = Vector2(0, 0);
		for (int k = 0; k <= n; k++) {
			int b = Factorial(n) / (Factorial(k) * (Factorial(n - k)));
			v_draw = v_draw + (v[k] * b * Power(t, k) * Power(1 - t, n - k));
		}
		v_draw.Draw(gRenderer);
	}
}

int main(int argc, char* args[])
{
	SetScreen(argc, args);
	std::cout << Power(6, 3) << std::endl;
	
	std::stack<Matriz> line_stack;
	std::stack<Matriz> circle_stack;
	std::stack<Matriz> curve_stack;
	

	std::vector<Vector2> line_v;
	std::vector<Vector2> curve_v;
	std::vector<Vector2> circle_v;
	

	std::cout << "Presione enter para ingresar su matriz de transformacion " << std::endl;
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		std::cout << "--- Indicaciones ---" << std::endl;
		std::cout << "Las lineas se ingresan con boton izquierdo y se borran con z" << std::endl;
		std::cout << "Las curvas se ingresan con boton derecho y se borran con q"<< std::endl;
		std::cout << "Los ojos se ingresan con el boton de en medio y se borran con a" << std::endl;
		std::cout << "Todo se puede modificar ingresando enter" << std::endl;
		std::cout << "Cuando ingrese enter, podrá ingresar los cambios y en el MISMO ORDEN se ejecutaran" << std::endl;
		std::cout << "Presionar finalizar cuando se terminen los cambios, y ahi se podra elegir a quien modificar" << std::endl;
		std::cout << "=======================================" << std::endl;

		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					if (e.button.button == SDL_BUTTON_MIDDLE) {
						std::cout << "Recibimos : " << e.button.x << ", " << e.button.y << std::endl;
						std::cout << "Type id: " << typeid(e.button.x).name() << std::endl;
						circle_v.push_back(Vector2(e.button.x, e.button.y, SCREEN_HEIGHT, SCREEN_WIDTH, tam));
					}
					if (e.button.button == SDL_BUTTON_LEFT) {
						std::cout << "Recibimos : " << e.button.x << ", " << e.button.y << std::endl;
						std::cout << "Type id: " << typeid(e.button.x).name() << std::endl;
						line_v.push_back(Vector2(e.button.x, e.button.y, SCREEN_HEIGHT, SCREEN_WIDTH, tam));
					}
					if (e.button.button == SDL_BUTTON_RIGHT) {
						std::cout << "Recibimos : " << e.button.x << ", " << e.button.y << std::endl;
						std::cout << "Type id: " << typeid(e.button.x).name() << std::endl;
						curve_v.push_back(Vector2(e.button.x, e.button.y, SCREEN_HEIGHT, SCREEN_WIDTH, tam));
					}
					
				}
				else if (e.type == SDL_KEYDOWN)
				{
					std::cout << e.key.keysym.sym << std::endl;
					if (e.key.keysym.sym == 13)
					{
						Matriz change;
						int v = 0;
						change = AskMatriz();
						std::cout << "A que matriz quiere aplicar el cambio?" << std::endl;
						std::cout << "1) Linea" << std::endl;
						std::cout << "2) Curva" << std::endl;
						std::cout << "3) Circulo" << std::endl;
						std::cin >> v;
						switch (v) {
						case 1:
							SetVectores(&line_v, change);
							line_stack.push(change.Inversa());
							break;
						case 2:
							SetVectores(&curve_v, change);
							curve_stack.push(change.Inversa());
							break;
						case 3:
							SetVectores(&circle_v, change);
							circle_stack.push(change.Inversa());
							break;
						default:
							std::cout << "No ingresaste una opcion correcta, no se cambiara nada" << std::endl;
						}
						
					}
					
					if (e.key.keysym.sym == 120 && line_v.size() > 0)
					{
						line_v.pop_back();
					}

					if (e.key.keysym.sym == 122 && line_stack.size() > 0)
					{
						SetVectores(&line_v, line_stack.top());
						line_stack.pop();
					}

					if (e.key.keysym.sym == 113 && curve_stack.size() > 0)
					{
						SetVectores(&curve_v, curve_stack.top());
						curve_stack.pop();
					}

					if (e.key.keysym.sym == 97 && circle_stack.size() > 0)
					{
						SetVectores(&circle_v, circle_stack.top());
						circle_stack.pop();
					}



					if (e.key.keysym.sym == 99 && circle_v.size() > 0)
					{
						circle_v.pop_back();
					}	
					
					if (e.key.keysym.sym == 118 && curve_v.size() > 0) {
						curve_v.pop_back();
					}
				}
			}

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);

			DrawPlain();

			BezierCurve(curve_v);

			for (int i = 1; i < line_v.size(); i++)
			{
				DrawLine3(line_v[i-1], line_v[i]);
				
			}

			for (int i = 1; i < circle_v.size(); i++)
			{
				DrawCircle(circle_v[0], circle_v[i]);
			}

			for (auto object : line_v)
			{
				object.Draw(gRenderer);
			}

			for (auto object : curve_v)
			{
				object.Draw(gRenderer);
			}

			for (auto object : circle_v)
			{
				object.Draw(gRenderer);
			}
			
			SDL_RenderPresent(gRenderer);
		}

	}

	close();

	return 0;
}