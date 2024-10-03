/*
 * effection.c
 *
 *  Created on  : 2024
 *  Authors      : Trung Tran
 *  Description : SnakeGame
 */

#include <stdio.h>

#include "SSD1306_OLED.h"
#include "effection.h"

void start_snake_game()
{
    setTextSize(2);
    setTextColor(WHITE);
    setCursor(1,0);
    println();
    print_strln("Snake Game");
    println();
    setTextSize(1);
    print_strln("by Trung Tran");
}

void end_snake_game()
{
    setTextSize(2);
    setTextColor(WHITE);
    setCursor(1,0);
    println();
    print_strln("Game Over!");
    println();
    setTextSize(1);
}