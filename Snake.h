#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <windows.h>
using namespace std;

#define WIDTH 640
#define HEIGHT 480
#define SIZE 20

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Snake {
    int x, y;
    Direction dir;
};

// 函式宣告（保留你原本名字）
void drawSnake(deque<Snake>& snake);
void moveSnake(deque<Snake>& snake, bool grow = false);
void changeDirection(deque<Snake>& snake);
bool isCrash(deque<Snake>& snake);

#endif#pragma once
