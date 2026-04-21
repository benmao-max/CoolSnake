#include <graphics.h>
#include <windows.h>
#include "Snake.h"
#include "Food.h"

#define DELAY 200

class Game {
private:
    deque<Snake> snake;
    Food food;

    int score;
    int hp;
    int delay;

public:
    Game()
    {
        initgraph(WIDTH, HEIGHT);

        snake.push_front({ WIDTH / SIZE / 2, HEIGHT / SIZE / 2, RIGHT });

        generateFood(food, snake);

        score = 0;
        hp = 5;
        delay = DELAY;
    }

    void cutSnake(deque<Snake>& snake)
    {
        Snake head = snake.front();

        for (auto it = snake.begin() + 1; it != snake.end(); ++it)
        {
            if (it->x == head.x && it->y == head.y)
            {
                // 清掉「撞到點之後的所有身體」
                snake.erase(it + 1, snake.end());
                break;
            }
        }
    }

    void resetSnake()
    {
        snake.clear();
        snake.push_front({ WIDTH / SIZE / 2, HEIGHT / SIZE / 2, RIGHT });
    }

    void gameOver()
    {
        settextcolor(RED);
        settextstyle(80, 0, _T("Consolas"));

        outtextxy(WIDTH / 3, HEIGHT / 3, _T("Game Over"));

        Sleep(3000);
        closegraph();
        exit(0);
    }

    void drawUI()
    {
        settextcolor(YELLOW);
        settextstyle(20, 0, _T("Consolas"));

        TCHAR str[64];
        _stprintf_s(str, _T("Score: %d  HP: %d"), score, hp);
        outtextxy(10, 10, str);
    }

    void run()
    {
        while (true)
        {
            changeDirection(snake);
            moveSnake(snake);

            if (checkCollision(snake, food))
            {
                score++;

                delay = max(50, DELAY - score * 5);

                generateFood(food, snake);
                moveSnake(snake, true);
            }

            if (isCrash(snake))
            {
                hp--;

                if (hp <= 0) gameOver();
                else cutSnake(snake);
            }

            drawFood(food);
            drawUI();

            Sleep(delay);
        }
    }
};

int main()
{
    Game game;
    game.run();
    return 0;
}