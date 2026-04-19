#include <easyx.h>
#include <deque>
#include <windows.h>
using namespace std;

#define WIDTH 640
#define HEIGHT 480
#define SIZE 20
#define DELAY 200

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Snake
{
    int x, y;
    Direction dir;
};
//吃的
struct Food
{
    int x, y;
};
//畫蛇添足
void drawSnake(deque<Snake>&snake)
{
    setfillcolor(GREEN);
    for (const auto& body : snake)
    {
        fillrectangle(body.x*SIZE , body.y * SIZE , (body.x+1) * SIZE , (body.y + 1) * SIZE);
    }
    Sleep(DELAY);
}
//遊戲結束判斷
void isOver(deque<Snake>& snake)
{
    for (auto iter = snake.begin() + 1;iter != snake.end(); ++iter) 
    {
        if ( (snake.front().x == iter->x && snake.front().y == iter->y) //跟身體重疊gameover
            || (snake.front().x<0) || (snake.front().x>=WIDTH/SIZE) //越界gameover
            || (snake.front().y<0) || (snake.front().y>=HEIGHT/SIZE) //越界gameover
           )
        {
            settextcolor(RED);
            settextstyle(100, 0, _T("Consolas"));
                TCHAR endStr[16];
                _stprintf_s(endStr, _T("Game Over"));
                outtextxy(WIDTH / SIZE,HEIGHT / SIZE, endStr);
                Sleep(3000);//3s
                closegraph();
                exit(0);
        }
    }
}
//控制移動-蛇
void moveSnake(deque<Snake>& snake, bool grow = false) 
{
    Snake newHead = snake.front();

    switch (newHead.dir)
    {
    case UP:
        newHead.y--;
        break;
    case DOWN:
        newHead.y++;
        break;
    case LEFT:
        newHead.x--;
        break;
    case RIGHT:
        newHead.x++;
        break;
    }
    snake.push_front(newHead);
    isOver(snake);
    //grow=true吃到食物:grow=false普通移動
    if (!grow)
    {
        clearrectangle(snake.back().x * SIZE, snake.back().y * SIZE, (snake.back().x+1) * SIZE, (snake.back().y+1) * SIZE);

        snake.pop_back();
    }
    drawSnake(snake);
}
//控制移動-鍵盤
void changeDirection(deque<Snake>& snake)
{
    ExMessage msg = { 0 };
    peekmessage(&msg, EX_KEY);
    if(msg.message == WM_KEYDOWN)
    {
        switch (msg.vkcode)
        { 
        case'W':
        case'w':
        case VK_UP:
            if (snake.front().dir != DOWN)
            {
                snake.front().dir = UP;
            }
            break;
        case'S':
        case's':
        case VK_DOWN:
            if (snake.front().dir != UP)
            {
                snake.front().dir = DOWN;
            }
            break;
        case'A':
        case'a':
        case VK_LEFT:
            if (snake.front().dir != RIGHT)
            {
                snake.front().dir = LEFT;
            }
            break;
        case'D':
        case'd':
        case VK_RIGHT:
            if (snake.front().dir != LEFT)
            {
                snake.front().dir = RIGHT;
            } 
            break;
        }
    }
}
//生成食物
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

        if (!overlap)
        {
            break;
        }
    }
}

bool checkCollision(deque<Snake>& snake, Food& food)
{
    if (snake.front().x == food.x && snake.front().y == food.y)
    {
        return true;
    }
        return false;
}

int main() 
{
    initgraph(WIDTH,HEIGHT);

    //蛇
    deque<Snake> snake;
    //初始化
    snake.push_front({WIDTH/SIZE/2,HEIGHT/SIZE/2,RIGHT});

    Food food;
    generateFood(food,snake);
    //畫蘋果
    setfillcolor(RED);
    fillrectangle(food.x * SIZE, food.y * SIZE, (food.x + 1) * SIZE, (food.y + 1) * SIZE);
    //畫蛇添足
    drawSnake(snake);
    int score = 0;

    while (true)
    {
        moveSnake(snake);
        changeDirection(snake);

        if (checkCollision(snake, food))
        {
            score++;
            generateFood(food, snake);
            moveSnake(snake,true);
        }
        setfillcolor(RED);//畫蘋果
        fillrectangle(food.x * SIZE, food.y * SIZE, (food.x + 1) * SIZE, (food.y + 1) * SIZE);

        settextcolor(YELLOW);
        settextstyle(20, 0, _T("Consolas"));
        TCHAR strScore[16];
        _stprintf_s(strScore, _T("Score: %d"), score);
        outtextxy(10, 10, strScore);
    }
    system("pause");
    closegraph();
     
    return 0;
}