#ifndef GAME_H
#define GAME_H

#define FRAMETIME 0.01

typedef struct{
	float time;
	int frame;
}game_t;

extern game_t gm;

void G_Init();
void G_Think();
void G_AdvanceFrame();

#endif //GAME_H