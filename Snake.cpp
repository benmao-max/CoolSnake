#include "Snake.h"
#include <graphics.h>

// 畫蛇
void drawSnake(deque<Snake>& snake)
{
    setfillcolor(GREEN);
    for (const auto& body : snake)
    {
        fillrectangle(body.x * SIZE, body.y * SIZE,
            (body.x + 1) * SIZE, (body.y + 1) * SIZE);
    }
}

// 撞擊判斷（改成回傳）
bool isCrash(deque<Snake>& snake)
{
    for (auto iter = snake.begin() + 1; iter != snake.end(); ++iter)
    {
        if (snake.front().x == iter->x && snake.front().y == iter->y)
            return true;
    }

    if (snake.front().x < 0 || snake.front().x >= WIDTH / SIZE ||
        snake.front().y < 0 || snake.front().y >= HEIGHT / SIZE)
        return true;

    return false;
}

// 移動
void moveSnake(deque<Snake>& snake, bool grow)
{
    Snake newHead = snake.front();

    switch (newHead.dir)
    {
    case UP: newHead.y--; break;
    case DOWN: newHead.y++; break;
    case LEFT: newHead.x--; break;
    case RIGHT: newHead.x++; break;
    }

    snake.push_front(newHead);

    if (!grow)
    {
        clearrectangle(snake.back().x * SIZE, snake.back().y * SIZE,
            (snake.back().x + 1) * SIZE, (snake.back().y + 1) * SIZE);
        snake.pop_back();
    }

    drawSnake(snake);
}

// 方向控制
void changeDirection(deque<Snake>& snake)
{
    ExMessage msg = { 0 };
    peekmessage(&msg, EX_KEY);

    if (msg.message == WM_KEYDOWN)
    {
        switch (msg.vkcode)
        {
        case 'W': case VK_UP: case 'w':
            if (snake.front().dir != DOWN) snake.front().dir = UP; break;
        case 'S': case VK_DOWN: case 's':
            if (snake.front().dir != UP) snake.front().dir = DOWN; break;
        case 'A': case VK_LEFT: case 'a':
            if (snake.front().dir != RIGHT) snake.front().dir = LEFT; break;
        case 'D': case VK_RIGHT: case 'd':
            if (snake.front().dir != LEFT) snake.front().dir = RIGHT; break;
        }
    }
}