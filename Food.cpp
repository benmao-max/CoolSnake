#include "Food.h"
#include <graphics.h>

// 生成食物
void generateFood(Food& food, deque<Snake>& snake)
{
    while (true)
    {
        food.x = rand() % (WIDTH / SIZE);
        food.y = rand() % (HEIGHT / SIZE);

        bool overlap = false;

        for (const auto& body : snake)
        {
            if (food.x == body.x && food.y == body.y)
            {
                overlap = true;
                break;
            }
        }

        if (!overlap) break;
    }
}

// 碰撞
bool checkCollision(deque<Snake>& snake, Food& food)
{
    return (snake.front().x == food.x && snake.front().y == food.y);
}

// 畫食物（修正顏色）
void drawFood(Food& food)
{
    setfillcolor(RED);
    fillrectangle(food.x * SIZE, food.y * SIZE,
        (food.x + 1) * SIZE, (food.y + 1) * SIZE);
}