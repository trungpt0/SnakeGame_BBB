/*
 * main.c
 *
 *  Created on  : 2024
 *  Authors      : Trung Tran
 *  Description : SnakeGame
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#include "I2C.h"
#include "SSD1306_OLED.h"
#include "effection.h"

#define SNAKE_MAX_LENGTH 100
#define SNAKE_PIXEL_SIZE 4

#define BUTTON_1 "30"
#define BUTTON_2 "31"
#define BUTTON_3 "48"
#define BUTTON_4 "60"

typedef struct
{
    int x;
    int y;
} xy;

xy snake[SNAKE_MAX_LENGTH];
int snake_length;
xy food;
int direction;
int score = 0;


void gpio_export(const char *gpio)
{
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return;
    }
    write(fd, gpio, 2);
    close(fd);
}

void gpio_direction(const char *gpio, const char *direction)
{
    char path[35];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%s/direction", gpio);
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        perror("gpio/direction");
        return;
    }
    write(fd, direction, 3);
    close(fd);
}

int gpio_read(const char *gpio)
{
    char path[30];
    char value;
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%s/value", gpio);
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("gpio/read");
        return -1;
    }
    read(fd, &value, 1);
    close(fd);
    return (value == '0') ? 0 : 1;
}

void generate_food()
{
    srand(time(NULL));
    food.x = (rand() % (SSD1306_LCDWIDTH/SNAKE_PIXEL_SIZE)) * SNAKE_PIXEL_SIZE;
    food.y = (rand() % (SSD1306_LCDHEIGHT/SNAKE_PIXEL_SIZE)) * SNAKE_PIXEL_SIZE;
}

void snake_init()
{
    snake_length = 3;
    snake[0].x = SSD1306_LCDWIDTH/2;
    snake[0].y = SSD1306_LCDHEIGHT/2;
    snake[1].x = snake[0].x - SNAKE_PIXEL_SIZE;
    snake[1].y = snake[0].y;
    snake[2].x = snake[1].x - SNAKE_PIXEL_SIZE;
    snake[2].y = snake[1].y;
    direction = 1;
    generate_food();
}

void move_snake()
{
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    if (gpio_read(BUTTON_1) == 0) direction = 0;
    if (gpio_read(BUTTON_2) == 0) direction = 1;
    if (gpio_read(BUTTON_3) == 0) direction = 2;
    if (gpio_read(BUTTON_4) == 0) direction = 3;

    if (direction == 0) snake[0].y -= SNAKE_PIXEL_SIZE; // Move up
    if (direction == 1) snake[0].x += SNAKE_PIXEL_SIZE; // Move right
    if (direction == 2) snake[0].y += SNAKE_PIXEL_SIZE; // Move down
    if (direction == 3) snake[0].x -= SNAKE_PIXEL_SIZE; // Move left

    if (snake[0].x == food.x && snake[0].y == food.y) {
        snake_length++;
        score++;
        generate_food();
    }
}

int check_collision()
{
    if (snake[0].x < 0 || snake[0].x >= SSD1306_LCDWIDTH || snake[0].y < 0 || snake[0].y >= SSD1306_LCDHEIGHT) {
        return 1;
    }
    for (int i = 1; i < snake_length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 1;
        }
    }
    return 0;
}

void drawSnake()
{
    for (int i = 0; i < snake_length; i++) {
        fillRect(snake[i].x, snake[i].y, SNAKE_PIXEL_SIZE, SNAKE_PIXEL_SIZE, WHITE);
    }
}

void drawFood()
{
    fillRect(food.x, food.y, SNAKE_PIXEL_SIZE, SNAKE_PIXEL_SIZE, WHITE);
}

void update_game()
{
    clearDisplay();
    move_snake();
    if (check_collision()) {
        end_snake_game();
        print_str("score: ");
        printNumber_I(score, DEC);
        Display();
        usleep(3000000);
        clearDisplay();
        printf("Game Over!\n");
        exit(0);
    }
    drawSnake();
    drawFood();
    Display();
}

int main()
{
    // gpio_export(BUTTON_1);
    // gpio_export(BUTTON_2);
    // gpio_export(BUTTON_3);
    // gpio_export(BUTTON_4);

    gpio_direction(BUTTON_1, "in");
    gpio_direction(BUTTON_2, "in");
    gpio_direction(BUTTON_3, "in");
    gpio_direction(BUTTON_4, "in");

    if (init_i2c_dev(I2C_DEV2_PATH, SSD1306_OLED_ADDR) == 0) {
        printf("connected to ssd1306\r\n");
    } else {
        printf("connect to ssd1306 failed\r\n");
    }

    display_Init_seq();
    clearDisplay();

    start_snake_game();
    Display();
    usleep(3000000);
    clearDisplay();

    snake_init();

    while (1) {
        update_game();
        usleep(200000);
    }
    return 0;
}