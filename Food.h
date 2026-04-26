#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"

struct Food {
    int x, y;
};

void generateFood(Food& food, deque<Snake>& snake);
bool checkCollision(deque<Snake>& snake, Food& food);
void drawFood(Food& food);

#endif#pragma once
