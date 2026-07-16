/**
  ******************************************************************************
  * @file    ssd1306.c
  * @author  Equip Embedded
  * @brief   Hardware peripheral interface definitions and macros.
  * @note    This copyright applies only to this file.
  *
  *          This file may contain:
  *           - SSD1306 OLED display driver functions
  *           - I2C communication routines
  *
  ******************************************************************************
  * MIT License
  *
  * Copyright (c) 2026 Equip Embedded
  *
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  ******************************************************************************
  */


#include "device_drivers/ssd1306.h"
#include <stdlib.h>

uint8_t ssd1306_buffer[128*8];

static const uint8_t font5x7_letters[26][5] = {

    // A
    {0x7C, 0x12, 0x11, 0x12, 0x7C},

    // B
    {0x7F, 0x49, 0x49, 0x49, 0x36},

    // C
    {0x3E, 0x41, 0x41, 0x41, 0x22},

    // D
    {0x7F, 0x41, 0x41, 0x22, 0x1C},

    // E
    {0x7F, 0x49, 0x49, 0x49, 0x41},

    // F
    {0x7F, 0x09, 0x09, 0x09, 0x01},

    // G
    {0x3E, 0x41, 0x49, 0x49, 0x7A},

    // H
    {0x7F, 0x08, 0x08, 0x08, 0x7F},

    // I
    {0x00, 0x41, 0x7F, 0x41, 0x00},

    // J
    {0x20, 0x40, 0x41, 0x3F, 0x01},

    // K
    {0x7F, 0x08, 0x14, 0x22, 0x41},

    // L
    {0x7F, 0x40, 0x40, 0x40, 0x40},

    // M
    {0x7F, 0x02, 0x04, 0x02, 0x7F},

    // N
    {0x7F, 0x04, 0x08, 0x10, 0x7F},

    // O
    {0x3E, 0x41, 0x41, 0x41, 0x3E},

    // P
    {0x7F, 0x09, 0x09, 0x09, 0x06},

    // Q
    {0x3E, 0x41, 0x51, 0x21, 0x5E},

    // R
    {0x7F, 0x09, 0x19, 0x29, 0x46},

    // S
    {0x46, 0x49, 0x49, 0x49, 0x31},

    // T
    {0x01, 0x01, 0x7F, 0x01, 0x01},

    // U
    {0x3F, 0x40, 0x40, 0x40, 0x3F},

    // V
    {0x1F, 0x20, 0x40, 0x20, 0x1F},

    // W
    {0x7F, 0x20, 0x18, 0x20, 0x7F},

    // X
    {0x63, 0x14, 0x08, 0x14, 0x63},

    // Y
    {0x03, 0x04, 0x78, 0x04, 0x03},

    // Z
    {0x61, 0x51, 0x49, 0x45, 0x43}
};

static const uint8_t font5x7_numbers[10][5] = {

    // 0
    {0x3E, 0x51, 0x49, 0x45, 0x3E},

    // 1
    {0x00, 0x42, 0x7F, 0x40, 0x00},

    // 2
    {0x62, 0x51, 0x49, 0x49, 0x46},

    // 3
    {0x22, 0x41, 0x49, 0x49, 0x36},

    // 4
    {0x18, 0x14, 0x12, 0x7F, 0x10},

    // 5
    {0x2F, 0x49, 0x49, 0x49, 0x31},

    // 6
    {0x3E, 0x49, 0x49, 0x49, 0x32},

    // 7
    {0x01, 0x71, 0x09, 0x05, 0x03},

    // 8
    {0x36, 0x49, 0x49, 0x49, 0x36},

    // 9
    {0x26, 0x49, 0x49, 0x49, 0x3E}
};



void i2c_write(uint8_t addr, uint8_t control_byte, uint8_t data) {

    /* Clear STOP and NACK flags */
    I2C1->ICR |= I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    /* Reset CR2 configuration */
    I2C1->CR2 = 0;

    /* Set slave address */
    I2C1->CR2 |= (addr << 1);

    /* Configure transfer size for 2 bytes */
    I2C1->CR2 |= (2 << I2C_CR2_NBYTES_Pos);

    /* Automatically generate STOP condition */
    I2C1->CR2 |= I2C_CR2_AUTOEND;

    /* Start I2C transfer */
    I2C1->CR2 |= I2C_CR2_START;

    /* Wait until TX register empty and ready for the next byte */
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = control_byte;

    /* Wait until TX register empty before sending data */
    while (!(I2C1->ISR & I2C_ISR_TXIS));
    I2C1->TXDR = data;

    /* Wait until STOP condition detected */
    while (!(I2C1->ISR & I2C_ISR_STOPF));
}

void ssd1306_cmd(uint8_t cmd) {

    /* Send command byte to SSD1306 */
	i2c_write(SSD1306_ADDR, SSD1306_CMD, cmd);
}

void ssd1306_data(uint8_t data) {

    /* Send data byte to SSD1306 */
	i2c_write(SSD1306_ADDR, SSD1306_DATA, data);
}

void ssd1306_init() {

    /* Turn display off during configuration */
	ssd1306_cmd(0xAE);

    /* Set memory addressing mode */
    ssd1306_cmd(0x20);

    /* Use horizontal addressing mode */
    ssd1306_cmd(0x00);

    /* Remap display columns */
    ssd1306_cmd(0xA1);

    /* Set COM output scan direction */
    ssd1306_cmd(0xC8);

    /* Set display contrast */
    ssd1306_cmd(0x81);

    /* Set contrast value */
    ssd1306_cmd(0x7F);

    /* Set normal (non-inverted) display mode */
    ssd1306_cmd(0xA6);

    /* Set multiplex ratio */
    ssd1306_cmd(0xA8);

    /* Configure multiplex value for 64 rows */
    ssd1306_cmd(0x3F);

    /* Set display offset */
    ssd1306_cmd(0xD3);

    /* No display offset */
    ssd1306_cmd(0x00);

    /* Set display clock divide ratio */
    ssd1306_cmd(0xD5);

    /* Set recommended clock setting */
    ssd1306_cmd(0x80);

    /* Enable charge pump regulator */
    ssd1306_cmd(0x8D);

    /* Use internal charge pump */
    ssd1306_cmd(0x14);

    /* Turn display on */
    ssd1306_cmd(0xAF);
}

void ssd1306_clear() {
    // Set full column address range
    ssd1306_cmd(0x21);
    ssd1306_cmd(0);
    ssd1306_cmd(127);

    // Set full page address range
    ssd1306_cmd(0x22);
    ssd1306_cmd(0);
    ssd1306_cmd(7);

    // Clear entire display GDDRAM
    for (int i = 0; i < 1024; i++)
    {
        i2c_write(0x3C, 0x40, 0x00);
    }
}

// Clears the entire display buffer by setting all pixels to OFF.
void ssd1306_clear_buffer(void)
{
    for (int i = 0; i < 1024; i++)
        ssd1306_buffer[i] = 0;
}

// Sends the contents of the display buffer to the SSD1306.
void ssd1306_update(){
    for (int i = 0; i < 1024; i++)
        ssd1306_data(ssd1306_buffer[i]);
}

// Draws a single pixel at the specified (x, y) coordinate.
void ssd1306_draw_pixel(int x, int y) {
	 if (x < 0 || x > 127 || y < 0 || y > 63)
		 return;

	 uint16_t index = (uint16_t)(x + ((y / 8) * 128));
	 uint8_t bit = (uint8_t)(1U << (y % 8));

	 ssd1306_buffer[index] |= bit;
}

// Draws a line between two points using Bresenham's line algorithm.
void ssd1306_draw_line(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;

    while (1)
    {
        ssd1306_draw_pixel(x0, y0);

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

// Draws the outline of a rectangle.
void ssd1306_draw_rect(int x, int y, int w, int h)
{
	// Top + bottom
	for (int i = 0; i < w; i++) {
		ssd1306_draw_pixel(x + i, y);			// top
		ssd1306_draw_pixel(x + i, y + h - 1);	// bottom
	}

	// Left + right
	for (int i = 0; i < h; i++) {
		ssd1306_draw_pixel(x, y + i);			// left
		ssd1306_draw_pixel(x + w - 1, y + i);	// right
	}
}

// Draws the outline of a circle centered at (cx, cy).
void ssd1306_draw_circle(int cx, int cy, int r)
{
    for (int x = -r; x <= r; x++)
    {
        for (int y = -r; y <= r; y++)
        {
            int d = x*x + y*y;

            if (d >= (r*r - r) && d <= (r*r + r))
            {
                ssd1306_draw_pixel(cx + x, cy + y);
            }
        }
    }
}

// Draws a single 5x7 character.
void ssd1306_draw_char(int x, int y, char c)
{
    const uint8_t *font = 0;

    if (c >= 'A' && c <= 'Z')
    {
        font = font5x7_letters[c - 'A'];
    }
    else if (c >= '0' && c <= '9')
    {
        font = font5x7_numbers[c - '0'];
    }
    else
    {
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        uint8_t col = font[i];

        for (int j = 0; j < 7; j++)
        {
            if (col & (1 << j))
            {
                ssd1306_draw_pixel(x + i, y + j);
            }
        }
    }
}

// Prints a null-terminated string to the display.
void ssd1306_print(int x, int y, const char *str)
{
    int cursor = x;

    while (*str)
    {
        if ((*str >= 'A' && *str <= 'Z') ||
            (*str >= '0' && *str <= '9'))
        {
            ssd1306_draw_char(cursor, y, *str);
        }

        cursor += 6; // 5 pixels + spacing
        str++;
    }
}
