
using namespace std;

#include <iostream>
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <string>

float previousTime = SDL_GetTicks();
float currentTime = 0.0;
float DeltaTime = 0.0;

int window_w = 1280;
int window_h = 768;

SDL_Window* window = SDL_CreateWindow("Clase de Programacion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

SDL_Texture* texture_start;
SDL_Texture* texture_ball;
SDL_Texture* texture_powerStr;
SDL_Texture* texture_powerSpe;
SDL_Texture* texture_powerSlo;

SDL_Surface* text_surface;
SDL_Texture* text_texture;

int game_stage = 0;
int gamemode = 0;

struct GameObject
{
	int width, height;
	float x, y, speedX, speedY;
};

GameObject ball{ 0, 0, (window_w / 2), (window_h / 2), 400, 400 };
GameObject p1{ 25, 110, 5, 10, 0, 300 };
GameObject p2{ 25, 110, (window_w - (p2.width + 5)), (window_h / 2), 0, 300};

bool gameStarted = false;

bool key_w = false, key_s = false, key_UP = false, key_DOWN = false, key_SPACE = false, key_1 = false, key_2 = false;

TTF_Font* Font;

string textTimer = "Timer";
float timer = 0.0;
float timer1 = 0.0;
float timerInicio = 0.0;

string text_score1 = "Score";
int score_p1 = 0;

string text_score2 = "Score";
int score_p2 = 0;


int difficulty = 0;

bool powerUpActive = false;
float lastSpawnTime = 0;
float IntervalPowerUP = 7;
bool powerUpTaken = false;
int powerTakenBy = 0;
float powerUpSpawnTime = 0;
float blinkTime = 5000; // 5s before blink starts
int blinkDuration = 2000; // blink for 2 seconds
float blinkTotalTime = blinkTime + blinkDuration;
float x_powerUp = 0;
float y_powerUp = 0;
int width_powerUp[3] = {0, 0, 0}; //Str, Spe, Slo
int heigth_powerUp[3] = {0, 0, 0}; //Str, Spe, Slo
int powerSelected = 0;
bool drawPowerUp;
int age;

bool lastTouched = 0;

void Input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
			if (event.key.keysym.sym == SDLK_SPACE) key_SPACE = true;
			if (event.key.keysym.sym == SDLK_1) key_1 = true;
			if (event.key.keysym.sym == SDLK_2) key_2 = true;
			if (event.key.keysym.sym == SDLK_w) key_w = true;
			if (event.key.keysym.sym == SDLK_s) key_s = true;
			if (event.key.keysym.sym == SDLK_UP) key_UP = true;
			if (event.key.keysym.sym == SDLK_DOWN) key_DOWN = true;
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) exit(0);
			if (event.key.keysym.sym == SDLK_SPACE) key_SPACE = false;
			if (event.key.keysym.sym == SDLK_1) key_1 = false;
			if (event.key.keysym.sym == SDLK_2) key_2 = false;
			if (event.key.keysym.sym == SDLK_w) key_w = false;
			if (event.key.keysym.sym == SDLK_s) key_s = false;
			if (event.key.keysym.sym == SDLK_UP) key_UP = false;
			if (event.key.keysym.sym == SDLK_DOWN) key_DOWN = false;
			break;
		}
	}
}
void Timer()
{
	timer = (SDL_GetTicks() / 1000);
	timer1 = (SDL_GetTicks() / 1000) - timerInicio; //Timer when Game Started
}
void StartMenu() // to do
{
	int hi = 0;
}
void ScoreSystem()
{
	if ((ball.x >= (window_w - ball.width) && ball.y <= window_h) || (ball.x <= 0 && ball.y <= window_h)) // score system
	{
		ball.x = (window_w/2);
		ball.y = (window_h/2);
		if (ball.x >= (window_w - ball.width) && ball.y <= window_h)
		{
			score_p1 += 1;
			ball.x = (window_w/2);
			ball.y = (window_h/2);
		}
	else if (ball.x <= 0 && ball.y <= window_h)
	{
			score_p2 +=1;
			ball.x = (window_w/2);
			ball.y = (window_h/2);
	 }
	}
}
void IA()
{
	if (p2.y < ball.y)
	{
		key_UP = false;
		key_DOWN = true;
	}
	if (p2.y > ball.y)
	{
		key_DOWN = false;
		key_UP = true;
	}
}
void Difficulty() // not done
{
	if (gamemode == 1 || gamemode == 0)
	{
		if (difficulty == 1)
		{
			ball.speedX = ball.speedX;
			ball.speedY = ball.speedY;
			p2.speedY = p2.speedY * 1.5;

		}
	}
	if (gamemode == 2)
	{
		if (difficulty == 1)
		{
			ball.speedX == ball.speedX;
			ball.speedY == ball.speedY;
		}
	}
	
}
int RandNumber(int N)
{
	return rand() % (N+1); //between 0 and N (inclusive)
}
int RandRange(int RandMin, int RandMax)
{
	return (rand() % (RandMax - RandMin + 1)) + RandMin;
}
void PowerUps() // to do
{
	
}
void PowerUpSpawn(int Min, int Max)
{
	if (powerUpActive = false && (timer1 - lastSpawnTime >= IntervalPowerUP))
	{
		powerUpActive = true; // "Spawns" PowerUp
		lastSpawnTime = SDL_GetTicks();
		powerUpSpawnTime = SDL_GetTicks();
		IntervalPowerUP = (RandRange(Min, Max) * 1000); //Set Next interval to a Random number from a Specified Range
		x_powerUp = RandRange((p1.width+ball.width+10), (window_w-(p2.width+ball.width+10)));
		y_powerUp = RandRange(ball.height, (window_h-(ball.height+7)));
		
		if (powerUpActive)
		{
			age = (timer1 - powerUpSpawnTime);
			if (powerTakenBy != 0)
			{
				powerUpActive = false;
			}
			else if (age >= blinkTotalTime)
			{
				powerUpActive = false;
			}
			else
			{
				drawPowerUp = true;
				if (age >= blinkDuration)
				{
					if ((((age - blinkDuration) / 200) % 2 == 0))
					{drawPowerUp = false; 
						
					}
				}
			}
			if (drawPowerUp)
			{
				powerSelected = RandNumber(2);
			}
		}
	}		
}
void Movement()
{
	if (key_SPACE)
	{
		game_stage = 1;
	}
	if (key_1)
	{
		gamemode = 1;
	}
	if (key_2)
	{
		gamemode = 2;
	}
	if (key_w)
	{
		if (p1.y >= 5)
		{
			p1.y -= p1.speedY * DeltaTime;
		}

	}
	if (key_s)
	{
		if (p1.y <= (window_h - (p1.height + 5)))
		{
			p1.y += p1.speedY * DeltaTime;
		}
	}
	if (gamemode == 1 || gamemode == 0)
	{
		if (key_UP)
		{
			p2.y -= p2.speedY * DeltaTime;
		}
		if (key_DOWN)
		{
			p2.y += p2.speedY * DeltaTime;
		}
		IA();
	}
	if (gamemode == 2)
	{
		if (key_UP)
		{
			if (p2.y >= 5)
			{
				p2.y -= p2.speedY * DeltaTime;
			}

		}
		if (key_DOWN)
		{
			if (p2.y <= (window_h - (p2.height + 10)))
			{
				p2.y += p2.speedY * DeltaTime;
			}
		}
	}
	//Ball Movement
	ball.x += ball.speedX * DeltaTime;
	ball.y += ball.speedY * DeltaTime;
	// Power Up movement
	for (int i = 0; i < 6; i++)
	{
		y_powerUp += 1;
	}
	for (int i = 0; i < 6; i++)
	{
		y_powerUp -= 1;
	}

}
void Collision()
{
	if (ball.y <= 0) //Collision top
	{
		ball.y = 0;
		ball.speedY *= -1;
		ball.speedY += RandRange(-50, 50);
		
	}
	if (ball.y >= window_h - ball.height) //Collision bot
	{
		ball.y = window_h - ball.height;
		ball.speedY *= -1;
		ball.speedY += RandRange(-50, 50);
		
	}

	//Collision p1 ball
	if (ball.x < p1.x + p1.width && //Collision upper rigth
		ball.x + ball.width > p1.x && //Collision upper left
		ball.y < p1.y + p1.height && //Collision bot right
		ball.y + ball.height > p1.y) //Collision bot left
	{
		if (ball.x < p1.x + p1.width &&
			ball.y < p1.y + p1.height)
		{
			ball.x = p1.x + p1.width;
		}
		else if ((ball.x - (p1.x + p2.width)) > 0.8)
		{
			ball.x -= 2;
		}
		ball.speedX *= -1;
		ball.speedY *= -1;
		lastTouched = 0;
	}
	//Collision p2 ball
	if (ball.x < p2.x + p1.width &&	//Collision upper rigth
		ball.x + ball.width > p2.x &&  //Collision upper left
		ball.y < p2.y + p2.height && //Collision bot right
		ball.y + ball.height > p2.y) //Collision bot left
	{
		if (ball.x + ball.width > p2.x &&
			ball.y + ball.height > p2.y)
		{
			ball.x = p2.x - p2.width;
		}
		else if ((ball.x - (p2.x -p2.width)) > 0.8)
		{
			ball.x += 2;
		}
	
		ball.speedX *= -1;
		ball.speedY *= -1;
		lastTouched = 1;
	}
	//Collision p1 powerUp
	if (x_powerUp < p1.x + p1.width && //Collision upper rigth
		x_powerUp + width_powerUp[powerSelected] > p1.x && //Collision upper left
		y_powerUp < p1.y + p1.height && //Collision bot right
		y_powerUp + heigth_powerUp[powerSelected] > p1.y) //Collision bot left
	{
		powerTakenBy = lastTouched;
	}
	//Collision p2 powerUp
	if (x_powerUp < p2.x + p2.width && //Collision upper rigth
		x_powerUp + width_powerUp[powerSelected] > p2.x && //Collision upper left
		y_powerUp < p2.y + p2.height && //Collision bot right
		y_powerUp + heigth_powerUp[powerSelected] > p2.y) //Collision bot left
	{
		powerTakenBy = lastTouched;
	}

}
void Update()
{
	Timer();
	ScoreSystem();
	Movement();
	Collision();
}
void DrawImage(SDL_Texture* Texture, int x, int y, int w, int h)
{
	SDL_Rect dest; // inicio
	dest.x = x;   //pos x
	dest.y = y;   //pos y
	dest.w = w;   //width (Ancho)
	dest.h = h;   //height (altura)
	SDL_RenderCopy(renderer, Texture, NULL, &dest);
	
}
void RandColorImage(SDL_Texture* Texture)
{
	SDL_SetTextureColorMod(Texture, rand() % 256, rand() % 256, rand() % 256);
	
}
void DrawBlock(int x, int y, int w, int h, int R, int G, int B, int A)
{
	SDL_Rect dest; // Player 1 box
	dest.x = x;   //pos x
	dest.y = y;   //pos y
	dest.w = w;   //width (Ancho)
	dest.h = h;   //height (altura)

	SDL_SetRenderDrawColor(renderer, R, G, B, A);	//pongo color blanco para player 1
	SDL_RenderFillRect(renderer, &dest);


}
void DrawTextInt(int variable, int x, int y, int R, int G, int B, int A)
{
	SDL_Color text_color = { R,G,B,A };
	text_surface = TTF_RenderText_Blended(Font, to_string(variable).c_str(), text_color); //creacion del texto
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	
	SDL_Rect destText;
	destText.x = x;
	destText.y = y;
	SDL_QueryTexture(text_texture, NULL, NULL, &destText.w, &destText.h);
	SDL_RenderCopy(renderer, text_texture, NULL, &destText);
}
void DrawTextString(string variable, int x, int y, int R, int G, int B, int A)
{
	SDL_Color text_color = { R,G,B,A };
	text_surface = TTF_RenderText_Blended(Font,variable.c_str(), text_color); //creacion del texto
	text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	
	SDL_Rect destText;
	destText.x = x;
	destText.y = y;

	SDL_QueryTexture(text_texture, NULL, NULL, &destText.w, &destText.h);
	SDL_RenderCopy(renderer, text_texture, NULL, &destText);
}
void Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Background
	SDL_RenderClear(renderer);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(text_texture);

	switch (game_stage)
	{
	case 0:
		DrawImage(texture_start, 0, 0, window_w, window_h);
		

		break;
	case 1:
		if (gameStarted == false)
		{
			timerInicio = (SDL_GetTicks() / 1000);
			gameStarted = true;
		}
		DrawBlock(p1.x, p1.y, p1.width, p1.height, 255, 255, 255, 0);
		DrawBlock(p2.x, p2.y, p2.width, p2.height, 255, 255, 255, 0);
		DrawImage(texture_ball, ball.x, ball.y, (ball.width -5) , (ball.height -5));
		if (powerUpActive)
		{
			RandColorImage(texture_ball);
			
			if (powerSelected == 0)
				{
					DrawImage(texture_powerStr, x_powerUp, y_powerUp, width_powerUp[0], heigth_powerUp[0]);
				}
			else if (powerSelected == 1)
				{
					DrawImage(texture_powerSpe, x_powerUp, y_powerUp, width_powerUp[1], heigth_powerUp[1]);
				}
			else if (powerSelected == 2)
				{
					DrawImage(texture_powerSlo, x_powerUp, y_powerUp, width_powerUp[2], heigth_powerUp[2]);
				}
		}
		
		DrawTextString(textTimer, (window_w-400), 150, 255,255,255, 0);
		DrawTextInt(timer, (window_w - 250), 150, 255, 255, 255, 0);
		
		DrawTextString(textTimer, (window_w - 100), 150, 255, 255, 255, 0);
		DrawTextInt(timer1, (window_w - 100), 250, 255, 255, 255, 0);
		
		
		DrawTextInt(score_p1, 300, 150, 255, 255, 255, 0);
		
		DrawTextInt(score_p2, (window_w - 480), 150, 255, 255, 255, 0);


		break;
	}

	SDL_RenderPresent(renderer);
}
int main(int argc, char* argv[])
{
	
	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	texture_start = IMG_LoadTexture(renderer, "assets/img/inicio.png");
	texture_ball = IMG_LoadTexture(renderer, "assets/img/Ball.png");
	texture_powerStr = IMG_LoadTexture(renderer, "assets/img/Strong.png");
	texture_powerSpe = IMG_LoadTexture(renderer, "assets/img/Speed.png");
	texture_powerSlo = IMG_LoadTexture(renderer, "assets/img/Slow.png");
	SDL_QueryTexture(texture_ball,NULL,NULL,&ball.width,&ball.height);
	SDL_QueryTexture(texture_powerStr,NULL,NULL,&width_powerUp[0],&heigth_powerUp[0]);
	SDL_QueryTexture(texture_powerSpe,NULL,NULL,&width_powerUp[1],&heigth_powerUp[1]);
	SDL_QueryTexture(texture_powerSlo,NULL,NULL,&width_powerUp[2],&heigth_powerUp[2]);
	Font = TTF_OpenFont("assets/fonts/arial.ttf", 20);


	while (true)
	{
		currentTime = SDL_GetTicks();
		DeltaTime= (currentTime - previousTime) / 1000.0;
		previousTime = currentTime;


		Input();
		Update();
		Render();
	}
	return 0;
}