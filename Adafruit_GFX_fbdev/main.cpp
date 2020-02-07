#include "Arduino.h"
#include "fbdev/fbdev.h"

static fbdev screen(0xFF, 0xFF);

float p = 3.1415926;

void testlines(uint16_t color)
{
    screen.fillScreen(screen.Black);
    screen.display();
    for (int16_t x = 0; x < screen.width(); x += 6)
    {
        screen.drawLine(0, 0, x, screen.height() - 1, color);
        screen.display();
    }
    for (int16_t y = 0; y < screen.height(); y += 6)
    {
        screen.drawLine(0, 0, screen.width() - 1, y, color);
        screen.display();
    }

    screen.fillScreen(screen.Black);
    screen.display();
    for (int16_t x = 0; x < screen.width(); x += 6)
    {
        screen.drawLine(screen.width() - 1, 0, x, screen.height() - 1, color);
        screen.display();
    }
    for (int16_t y = 0; y < screen.height(); y += 6)
    {
        screen.drawLine(screen.width() - 1, 0, 0, y, color);
        screen.display();
    }

    screen.fillScreen(screen.Black);
    for (int16_t x = 0; x < screen.width(); x += 6)
    {
        screen.drawLine(0, screen.height() - 1, x, 0, color);
        screen.display();
    }
    for (int16_t y = 0; y < screen.height(); y += 6)
    {
        screen.drawLine(0, screen.height() - 1, screen.width() - 1, y, color);
        screen.display();
    }

    screen.fillScreen(screen.Black);
    screen.display();
    for (int16_t x = 0; x < screen.width(); x += 6)
    {
        screen.drawLine(screen.width() - 1, screen.height() - 1, x, 0, color);
        screen.display();
    }
    for (int16_t y = 0; y < screen.height(); y += 6)
    {
        screen.drawLine(screen.width() - 1, screen.height() - 1, 0, y, color);
        screen.display();
    }
}

void testdrawtext(const char *text, uint16_t color)
{
    screen.setCursor(0, 0);
    screen.setTextColor(color);
    screen.setTextWrap(true);
    screen.print(text);
    screen.display();
}

void testfastlines(uint16_t color1, uint16_t color2)
{
    screen.fillScreen(screen.Black);
    screen.display();
    for (int16_t y = 0; y < screen.height(); y += 5)
    {
        screen.drawFastHLine(0, y, screen.width(), color1);
        screen.display();
    }
    for (int16_t x = 0; x < screen.width(); x += 5)
    {
        screen.drawFastVLine(x, 0, screen.height(), color2);
        screen.display();
    }
}

void testdrawrects(uint16_t color)
{
    screen.fillScreen(screen.Black);
    screen.display();
    for (int16_t x = 0; x < screen.width(); x += 6)
    {
        screen.drawRect(screen.width() / 2 - x / 2, screen.height() / 2 - x / 2, x, x, color);
        screen.display();
    }
}

void testfillrects(uint16_t color1, uint16_t color2)
{
    screen.fillScreen(screen.Black);
    screen.display();
    for (int16_t x = screen.width() - 1; x > 6; x -= 6)
    {
        screen.fillRect(screen.width() / 2 - x / 2, screen.height() / 2 - x / 2, x, x, color1);
        screen.display();
        screen.drawRect(screen.width() / 2 - x / 2, screen.height() / 2 - x / 2, x, x, color2);
        screen.display();
    }
}

void testfillcircles(uint8_t radius, uint16_t color)
{
    for (int16_t x = radius; x < screen.width(); x += radius * 2)
    {
        for (int16_t y = radius; y < screen.height(); y += radius * 2)
        {
            screen.fillCircle(x, y, radius, color);
            screen.display();
        }
    }
}

void testdrawcircles(uint8_t radius, uint16_t color)
{
    for (int16_t x = 0; x < screen.width() + radius; x += radius * 2)
    {
        for (int16_t y = 0; y < screen.height() + radius; y += radius * 2)
        {
            screen.drawCircle(x, y, radius, color);
            screen.display();
        }
    }
}

void testtriangles()
{
    screen.fillScreen(screen.Black);
    screen.display();
    int color = 0xF800;
    int t;
    int w = screen.width() / 2;
    int x = screen.height() - 1;
    int y = 0;
    int z = screen.width();
    for(t = 0 ; t <= 15; t++)
    {
        screen.drawTriangle(w, y, y, x, z, x, color);
        screen.display();
        x -= 4;
        y += 4;
        z -= 4;
        color += 100;
    }
}

void testroundrects()
{
    screen.fillScreen(screen.Black);
    screen.display();
    int color = 100;
    int i;
    int t;
    for(t = 0 ; t <= 4; t += 1)
    {
        int x = 0;
        int y = 0;
        int w = screen.width() - 2;
        int h = screen.height() - 2;
        for(i = 0 ; i <= 16; i += 1)
        {
            screen.drawRoundRect(x, y, w, h, 5, color);
            screen.display();
            x += 2;
            y += 3;
            w -= 4;
            h -= 6;
            color += 1100;
        }
        color += 100;
    }
}

void screenPrintTest()
{
    screen.setTextWrap(false);
    screen.fillScreen(screen.Black);
    screen.setCursor(0, 30);
    screen.setTextColor(screen.Red);
    screen.setTextSize(1);
    screen.println("Hello World!");
    screen.display();

    screen.setTextColor(screen.Yellow);
    screen.setTextSize(2);
    screen.println("Hello World!");
    screen.display();

    screen.setTextColor(screen.Green);
    screen.setTextSize(3);
    screen.println("Hello World!");
    screen.display();

    screen.setTextColor(screen.Blue);
    screen.setTextSize(4);
    screen.print(1234.567);
    screen.display();

    delay(1500);
    screen.setCursor(0, 0);
    screen.fillScreen(screen.Black);
    screen.setTextColor(screen.White);
    screen.setTextSize(0);
    screen.println("Hello World!");
    screen.display();

    screen.setTextSize(1);
    screen.setTextColor(screen.Green);
    screen.print(p, 6);
    screen.println(" Want pi?");
    screen.println(" ");
    screen.print(8675309, HEX); // print 8,675,309 out in HEX!
    screen.println(" Print HEX!");
    screen.println(" ");
    screen.display();

    screen.setTextColor(screen.White);
    screen.println("Sketch has been");
    screen.println("running for: ");
    screen.setTextColor(screen.Magenta);
    screen.print(millis() / 1000);
    screen.setTextColor(screen.White);
    screen.print(" seconds.");
    screen.display();
}

void mediabuttons()
{
    // play
    screen.fillScreen(screen.Black);
    screen.fillRoundRect(25, 10, 78, 60, 8, screen.White);
    screen.fillTriangle(42, 20, 42, 60, 90, 40, screen.Red);
    screen.display();
    delay(500);
    // pause
    screen.fillRoundRect(25, 90, 78, 60, 8, screen.White);
    screen.fillRoundRect(39, 98, 20, 45, 5, screen.Green);
    screen.fillRoundRect(69, 98, 20, 45, 5, screen.Green);
    screen.display();
    delay(500);
    // play color
    screen.fillTriangle(42, 20, 42, 60, 90, 40, screen.Blue);
    screen.display();
    delay(50);
    // pause color
    screen.fillRoundRect(39, 98, 20, 45, 5, screen.Red);
    screen.fillRoundRect(69, 98, 20, 45, 5, screen.Red);
    screen.display();
    // play color
    screen.fillTriangle(42, 20, 42, 60, 90, 40, screen.Green);
    screen.display();
}

float time,fps;

void setup(void)
{
    printf("<%s>:%d x %d\r\n", screen.fbPath, screen.width(), screen.height());
    printf(screen.init() ? "init success\r\n" : "init faild\r\n");
    printf("%dx%d, %dbpp\n", screen.vinfo.xres, screen.vinfo.yres, screen.vinfo.bits_per_pixel);

    delay(2000);

    time = millis();
    for(int i = 0; i < 100; i++)
    {
        screen.fillScreen(screen.Red);
        screen.display();
        screen.fillScreen(screen.Green);
        screen.display();
        screen.fillScreen(screen.Blue);
        screen.display();
    }
    time = millis() - time;
    fps = 1000 / (time / 300);
    printf("fps:%0.2f\n",fps);

    uint16_t time = millis();
    screen.fillScreen(screen.Black);
    screen.display();
    time = millis() - time;

    // large block of text
    screen.fillScreen(screen.Black);
    screen.display();
    testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", screen.White);
    delay(1000);

    // screen print function!
    screenPrintTest();
    delay(4000);

    // a single pixel
    screen.drawPixel(screen.width() / 2, screen.height() / 2, screen.Green);
    screen.display();
    delay(500);

    // line draw test
    testlines(screen.Yellow);
    delay(500);

    // optimized lines
    testfastlines(screen.Red, screen.Blue);
    delay(500);

    testdrawrects(screen.Green);
    delay(500);

    testfillrects(screen.Yellow, screen.Magenta);
    delay(500);

    screen.fillScreen(screen.Black);
    screen.display();
    testfillcircles(10, screen.Blue);
    testdrawcircles(10, screen.White);
    delay(500);

    testroundrects();
    delay(500);

    testtriangles();
    delay(500);

    mediabuttons();
    delay(500);
}

void loop()
{
    screen.fillScreen(0);
    screen.display();
    delay(1000);
    screen.fillScreen(0xFFFF);
    screen.display();
    delay(1000);
}

int main()
{
    setup();
    for(;;)loop();
}
