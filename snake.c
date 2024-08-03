#include "snake.h"

void init_game(void)
{
    WINDOW *win = initscr();
    
    keypad(win, true);
    nodelay(win, true);

    int foodX = 0;
    int foodY = 0;

    food_position(&foodX, &foodY);

    int dirX = 1;
    int dirY = 0;

    int screen_delay = X_DELAY;
    int pontos = 0;
    bool rodando = true;
    bool gameover = false;

    int **snake = (int**)malloc(sizeof(int*) * SNAKE_ROWS);

    for (int i = 0; i < SNAKE_ROWS; ++i)
    {
        snake[i] = (int*)malloc(sizeof(int));

        if (snake[i] == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    snake[0][0] = POS_X_MIN;
    snake[1][0] = POS_Y_MIN;
 
    while (rodando) 
    {
        int pressed = wgetch(win);

        if (((SNAKE_HEAD_X > POS_X_MAX) || (SNAKE_HEAD_X < POS_X_MIN) 
        || (SNAKE_HEAD_Y > POS_Y_MAX) || (SNAKE_HEAD_Y < POS_Y_MIN))
            && !gameover)
        {
            SNAKE_HEAD_X = POS_X_MIN;
            SNAKE_HEAD_Y = POS_Y_MIN;
            pontos = 0;
            gameover = true;
            vai_para_direita(&dirX, &dirY);
        }
        
        if (pressed == KEY_LEFT)
        {
            screen_delay = X_DELAY;
            vai_para_esquerda(&dirX, &dirY);
        }
        if (pressed == KEY_RIGHT) 
        {  
            screen_delay = X_DELAY;
            vai_para_direita(&dirX, &dirY);
        }
        if (pressed == KEY_UP) 
        {
            screen_delay = Y_DELAY;
            vai_para_cima(&dirX, &dirY);
        }
        if (pressed == KEY_DOWN) 
        {
            screen_delay = Y_DELAY;
            vai_para_baixo(&dirX, &dirY);
        }
        if (pressed == KEY_DC) 
        {
            rodando = false;
        }
        if (pressed == KEY_BACKSPACE) 
        {
            gameover = false;
        }
 
        erase();

        if (!gameover)
        {
            for (int i = pontos; i >= 0; --i)
            {
                if (i == 0)
                {
                    snake[0][i] += dirX;
                    snake[1][i] += dirY;
                }
                else if (i > 0)
                {
                    snake[0][i] = snake[0][i - 1];
                    snake[1][i] = snake[1][i - 1];
                }
            }

            for (int i = 0; i < (pontos + 1); ++i)
            {
                mvaddstr(snake[1][i], snake[0][i], "*");
            }

            mvaddstr(foodY, foodX, "O");
        }
        else
        {
            game_over();
        }

        draw_header(&pontos, gameover);
        draw_field();

        if (foodX == snake[0][0] && foodY == snake[1][0]) 
        {
            food_position(&foodX, &foodY);
            pontos++;

            if (pontos == MAX_SCORE)
            {

            }
            else
            {
                for (int i = 0; i < SNAKE_ROWS; ++i)
                {
                    snake[i] = (int*)realloc(snake[i], sizeof(int*) * pontos);

                    if (snake[i] != NULL)
                    {
                        snake[i][pontos] = snake[i][0] + dirX;
                    }

                }
            }
        }
        
        usleep(screen_delay);
    }

    // Free memory
    for (int i = 0; i < SNAKE_ROWS; i++) 
    {
        free(snake[i]);
    }
    
    free(snake);

    erase();
    endwin();
}

void draw_header(int *score, bool gameover)
{
    mvaddstr(0, 0, "Snake Game, press DEL to quit.");

    char score_phrase[20];
    sprintf(score_phrase, "Score: %d ", *score);

    if (gameover)
    {
        mvaddstr(1, 0, "Press BACKSPACE to restart.");
    }
    else
    {
        mvaddstr(1, 0, score_phrase);
    }

}

void draw_field(void)
{
    for (int i = FIELD_X_MIN; i < FIELD_X_MAX; ++i)
    {
        mvaddstr(FIELD_Y_MIN, i + 1, "#");
        mvaddstr(FIELD_Y_MAX, i, "#");
    }

    for (int i = FIELD_Y_MIN; i < FIELD_Y_MAX; ++i)
    {
        mvaddstr(i, FIELD_X_MIN, "#");
        mvaddstr(i + 1, FIELD_X_MAX, "#");
    } 
}

void vai_para_direita(int *x, int *y)
{
    *x = 1;
    *y = 0;
}

void vai_para_esquerda(int *x, int *y)
{
    *x = -1;
    *y = 0;
}

void vai_para_baixo(int *x, int *y)
{
    *x = 0;
    *y = 1;
}

void vai_para_cima(int *x, int *y)
{
    *x = 0;
    *y = -1;
}

void game_over(void)
{
    char text[] = "GAME OVER!!!";
    int y = FIELD_Y_MAX / 2;
    int x = (FIELD_X_MAX / 2) - (strlen(text) / 2);
    mvaddstr(y, x, text);
}

void food_position(int *x, int *y)
{
    int foodX = get_random(POS_X_MAX);
    int foodY = get_random(POS_Y_MAX);

    if (foodX < POS_X_MIN)
    {
        foodX = POS_X_MIN;
    }

    if (foodY < POS_Y_MIN)
    {
        foodY = POS_Y_MIN;
    }

    *x = foodX;
    *y = foodY;
}

int get_random(int max)
{
    int numero = rand() % max;

    return numero;
}
