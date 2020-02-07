#ifndef __FBDEV_H
#define __FBDEV_H

#include "Adafruit_GFX_Library/Adafruit_GFX.h"

extern "C"
{
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
}

class fbdev : public GFXcanvas32
{
    typedef struct
    {
        int16_t x1;
        int16_t y1;
        int16_t x2;
        int16_t y2;
    } fb_area_t;

    typedef union {
        struct
        {
            uint16_t blue : 5;
            uint16_t green : 6;
            uint16_t red : 5;
        } ch;
        uint16_t full;
    } fb_color16_t;

    typedef union
    {
        struct
        {
            uint8_t blue;
            uint8_t green;
            uint8_t red;
            uint8_t alpha;
        } ch;
        uint32_t full;
    } fb_color32_t;

public:
    fbdev(uint16_t w, uint16_t h, const char *path = "/dev/fb0") : GFXcanvas32(w, h)
    {
        fbPath = path;
        fbp = 0;
        screensize = 0;
        fbfd = 0;
    }
    ~fbdev()
    {
        close(fbfd);
    }
    bool init(void);
    void flush(const fb_area_t *area, fb_color32_t *color_p);
    void display()
    {
        const fb_area_t area = {0, 0, (int16_t)(_width - 1), (int16_t)(_height - 1)};
        /*fb_color32_t buf_32bit[_width * _height];
        fb_color16_t *buf_16bit = (fb_color16_t*)getBuffer();
        for (int i = 0; i < _width * _height; i++)
        {
            buf_32bit[i].ch.red = buf_16bit[i].ch.red * 8;
            buf_32bit[i].ch.green = buf_16bit[i].ch.green * 4;
            buf_32bit[i].ch.blue = buf_16bit[i].ch.blue * 8;
            buf_32bit[i].ch.alpha = 0xFF;
        }*/

        flush(&area, (fb_color32_t *)getBuffer());
    }

    typedef enum
    {
        White = 0xFFFF,
        Black = 0x0000,
        Blue = 0x001F,
        Bred = 0XF81F,
        Gred = 0XFFE0,
        Gblue = 0X07FF,
        Red = 0xF800,
        Magenta = 0xF81F,
        Green = 0x07E0,
        Cyan = 0x7FFF,
        Yellow = 0xFFE0,
        Brown = 0XBC40,
        Brred = 0XFC07,
        Gray = 0X8430,

        DarkBlue = 0X01CF,
        LightBlue = 0X7D7C,
        GRAYBLUE = 0X5458,

        LightGreen = 0X841F,
        LightGray = 0XEF5B,
        Lgray = 0XC618,

        LgrayBlue = 0XA651,
        Lbblue = 0X2B12
    } Color_Type;

//private:
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

    const char *fbPath;
    uint8_t *fbp;
    uint64_t screensize;
    int fbfd;
};

#endif
