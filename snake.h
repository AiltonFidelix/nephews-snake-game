#ifndef __SNAKE_H
#define __SNAKE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

#define FIELD_X_MIN 0
#define FIELD_X_MAX 100
#define FIELD_Y_MIN 2
#define FIELD_Y_MAX 30

#define POS_X_MIN ((FIELD_X_MIN) + 1)
#define POS_X_MAX ((FIELD_X_MAX) - 1)
#define POS_Y_MIN ((FIELD_Y_MIN) + 1)
#define POS_Y_MAX ((FIELD_Y_MAX) - 1)

#define SNAKE_HEAD_X snake[0][0]
#define SNAKE_HEAD_Y snake[1][0]

#define X_DELAY 65000
#define Y_DELAY 125000
#define MAX_SCORE 100

void iniciar_jogo(void);
void escreve_titulo(int *pontos, bool gameover);
void desenhar_caixa(void);
void vai_para_direita(int *x, int *y);
void vai_para_esquerda(int *x, int *y);
void vai_para_baixo(int *x, int *y);
void vai_para_cima(int *x, int *y);
void game_over(void);

void posicionar_food(int *x, int *y);
int gerar_numero(int max);

#endif