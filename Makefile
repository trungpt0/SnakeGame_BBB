SOURCES = SSD1306_OLED_Library/SSD1306_OLED.c Src/main.c Src/automation.c I2C_Library/I2C.c
OBJS := $(SOURCES:.c=.o)
CPPFLAGS := -I SSD1306_OLED_Library -I I2C_Library
CFLAGS := -g

main: $(OBJS)
	$(CC) $^ -o $@

clean:
	rm -rf main $(OBJS)
