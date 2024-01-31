/**
 * @brief Abstracts displaying items to the screen
 * @file DisplayManager.cpp
 * @date Nov 26, 2023
 * @author cyberreefguru
 */
#include "DisplayManager.h"

DisplayManager displayManager;

DisplayManager::DisplayManager()
{
}

void DisplayManager::initialize()
{
    // Log.traceln("DisplayManager::initialize - BEGIN");

    ssd1306 = Adafruit_SSD1306(128, 64, &Wire);
    ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
    uint8_t b = prefManager.getScreenBrightness();
    Log.traceln("DisplayManager::initialize - Setting screen brightness - %d", b);
    setBrightness( prefManager.getScreenBrightness() );

    ssd1306.setTextSize(1);
    ssd1306.setTextColor(SSD1306_WHITE);
    ssd1306.clearDisplay();
    ssd1306.drawBitmap(0, 0, aquarius_boot_bitmap, 128, 64, WHITE);    
    ssd1306.display();
    delay(1000);
    ssd1306.clearDisplay();
    ssd1306.display();

    Log.infoln("DisplayManager::initialize - creating display task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { displayManager.displayTask(pvParameters); },
        "display_task",
        1024,
        NULL,
        tskIDLE_PRIORITY + 1,
        &displayTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("DisplayManager::initialize - FAILED TO CREATE DISPLAY TASK");
    }

    // Log.traceln("DisplayManager::initialize - END");
}

/***
 * DisplayManager task updates the display when things change.
 */
void DisplayManager::displayTask(void *pvParameters)
{
    Log.traceln("DisplayManager::displayTask - starting display task.");
    uint8_t clicks = 0;

    for (;;)
    {
        if (refresh)
        {
            ssd1306.display();
            refresh = false;
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // update every 100ms
    }
}

/**
 * Sets the size of the font
 *
 * @param size display size enumeration
 *
 * @note currently unused
 */
void DisplayManager::setSize(DisplaySize size)
{
    this->size = size;
    prefManager.set(KEY_DISPLAY_SIZE, (uint8_t)(size));
}

/**
 * Tells the display thread to update the display
 *
 * @param r true = update; false = do not update
 */
void DisplayManager::setRefresh(bool r)
{
    refresh = r;
}

/**
 * Clears the display buffer
 *
 * @note does not call display
 *
 */
void DisplayManager::clear()
{
    ssd1306.clearDisplay();
}

/**
 * Sets the foreground color
 *
 * @param fg the foreground color
 */
void DisplayManager::setTextColor(uint16_t fg)
{
    ssd1306.setTextColor(fg);
}

/**
 * Sets the foreground and background colors
 *
 * @param fg the foreground color
 * @param bg the background color
 */
void DisplayManager::setTextColor(uint16_t fg, uint16_t bg)
{
    ssd1306.setTextColor(fg, bg);
}

/**
 * Prints the provided value to the screen
 *
 * @note does not set the cursor first
 *
 * @param m pointer to string
 */
void DisplayManager::print(const char *m)
{
    ssd1306.print(m);
}

/**
 * Prints the provided value to the screen
 *
 * @note does not set the cursor first
 *
 * @param d the byte
 */
void DisplayManager::print(uint8_t d)
{
    ssd1306.print(d);
}

/**
 * Prints the provided value to the screen
 *
 * @note does not set the cursor first
 *
 * @param d the short integer
 */
void DisplayManager::print(uint16_t d)
{
    ssd1306.print(d);
}

/**
 * Prints the provided value to the screen
 *
 * @note does not set the cursor first
 *
 * @param d the long integer
 */
void DisplayManager::print(uint32_t d)
{
    ssd1306.print(d);
}

/**
 * Prints the provided value to the screen
 *
 * @note does not set the cursor first
 *
 * @param f the floating point number
 */
void DisplayManager::print(float f)
{
    ssd1306.print(f);
}

/**
 * Prints the provided value to the screen
 *
 * @note does not set the cursor first
 *
 * @param d the double
 */
void DisplayManager::print(double d)
{
    ssd1306.print(d);
}

/**
 * Prints the provided value to the screen
 *
 * @note does not set the cursor first
 *
 * @param m String object
 */
void DisplayManager::print(String s)
{
    ssd1306.print(s);
}

/**
 * Prints the provided value to the screen with a newline
 *
 * @note does not set the cursor first
 *
 * @param m pointer to string
 */
void DisplayManager::println(const char *m)
{
    if( m ==  nullptr )
    {
        Log.errorln("DisplayManager::println - string pointer is null!");
        return;
    }
    ssd1306.println(m);
}

/**
 * Prints a newline to the screen
 * Effectively sets row = row+1; col=0
 *
 */
void DisplayManager::println()
{
    ssd1306.println();
}

void DisplayManager::printf(const char *f, ...)
{
    char dest[23];
    va_list argptr;
    va_start(argptr, f);
    vsprintf(dest, f, argptr);
    va_end(argptr);
    ssd1306.printf(dest);
}

void DisplayManager::dim(bool b)
{
    ssd1306.dim(b);
}

void DisplayManager::setBrightness(uint8_t v)
{
    ssd1306.ssd1306_command(SSD1306_SETCONTRAST);
    ssd1306.ssd1306_command(v);
}

/**
 * Sets the location of the cursor using rows/columns.
 * This is dependent on the font being used.
 *
 * @param row expressed in FONT_HEIGHT increments
 * @param col expressed in FONT_WIDTH increments
 */
void DisplayManager::setCursor(uint8_t row, uint8_t col)
{
    uint8_t r = row * FONT_HEIGHT;
    uint8_t c = col * FONT_WIDTH;
    ssd1306.setCursor(c, r);
}

/**
 * Sets the location of the cursor using pixels.
 *
 * @param row expressed in pixel increments
 * @param col expressed in pixel increments
 */
void DisplayManager::setCursorXY(uint16_t x, uint16_t y)
{
    ssd1306.setCursor(x, y);
}

/**
 * Sets the X location of the cursor using pixels.
 *
 * @param x expressed in pixel increments
 */
void DisplayManager::setCursorX(uint16_t x)
{
    ssd1306.setCursor(x, ssd1306.getCursorY());
}

/**
 * Sets the Y location of the cursor using pixels.
 *
 * @param y expressed in pixel increments
 */
void DisplayManager::setCursorY(uint16_t y)
{
    ssd1306.setCursor(ssd1306.getCursorX(), y);
}

/**
 * Returns the X location of the cursor in pixels.
 *
 * @return cursor X position expressed in pixel increments
 */
uint16_t DisplayManager::getCursorX()
{
    return ssd1306.getCursorX();
}

/**
 * Returns the Y location of the cursor in pixels.
 *
 * @return cursor Y position expressed in pixel increments
 */
uint16_t DisplayManager::getCursorY()
{
    return ssd1306.getCursorY();
}

/**
 * Adds specified amount to current cursor X position
 * 
 * @param dx integer number of pixels to adjust
*/
void DisplayManager::addCursorX(int16_t dx)
{
    uint16_t x, y;
    x = ssd1306.getCursorX();
    y = ssd1306.getCursorY();
    ssd1306.setCursor( (x+dx), y );
}

/**
 * Adds specified amount to current cursor Y position
 * 
 * @param dy integer number of pixels to adjust
*/
void DisplayManager::addCursorY(int16_t dy)
{
    uint16_t x, y;
    x = ssd1306.getCursorX();
    y = ssd1306.getCursorY();
    ssd1306.setCursor( x, (y+dy) );
}

/**
 * Adds specified amount to current cursor position
 * 
 * @param dx integer number of pixels to adjust
 * @param dy integer number of pixels to adjust
*/
void DisplayManager::addCursor(int16_t dx, int16_t dy)
{
    uint16_t x, y;
    x = ssd1306.getCursorX();
    y = ssd1306.getCursorY();
    ssd1306.setCursor( (x+dx), (y+dy) );
}

/**
 * Clears the entire row in the buffer.
 *
 * @note does NOT call display
 *
 * @param row expressed in FONT_HEIGHT increments
 */
void DisplayManager::clearRow(uint8_t row)
{
    ssd1306.fillRect(0, row * FONT_HEIGHT, 128, FONT_HEIGHT, BLACK);
}

/**
 * Clears a block of buffer space
 *
 * @note does NOT call display
 *
 * @param srow the starting row expressed in FONT_HEIGHT increments
 * @param scol the starting column expressed in FONT_WIDTH increments
 * @param erow the ending row expressed in FONT_HEIGHT increments
 * @param ecol the ending column expressed in FONT_WIDTH increments
 */
void DisplayManager::clearRow(uint8_t srow, uint8_t scol, uint8_t erow, uint8_t ecol)
{
    uint8_t xstart = scol * FONT_WIDTH;
    uint8_t width = (ecol - scol + 1) * FONT_WIDTH;

    uint8_t ystart = srow * FONT_HEIGHT;
    uint8_t height = (erow - srow + 1) * FONT_HEIGHT;

    ssd1306.fillRect(xstart, ystart, width, height, BLACK);
}

/**
 * @brief Draws a button with the specified text
 * @note button is 6 pixels taller and wider than text provided
 * @param text text for button
 * @param active if true, button is highlighted
 */
void DisplayManager::drawButton(const char *text, bool active)
{
    uint16_t x = ssd1306.getCursorX();
    uint16_t y = ssd1306.getCursorY();
    uint16_t h = FONT_HEIGHT + 6;
    uint16_t w = FONT_WIDTH * strlen(text) + 6;

    // Log.traceln("DisplayManager::drawButton - cursor (%d, %d), size (%d, %d)", x, y, h, w);

    if( active )
    {
        ssd1306.fillRoundRect(x, y, w, h, 4, WHITE);
        ssd1306.setCursor(x+3, y+3);
        ssd1306.setTextColor(BLACK);
        ssd1306.print(text);
    }
    else
    {
        ssd1306.drawRoundRect(x, y, w, h, 4, WHITE);
        ssd1306.setCursor(x+3, y+3);
        ssd1306.setTextColor(WHITE);
        ssd1306.print(text);
    }
    ssd1306.setTextColor(WHITE);

    // Log.traceln("DisplayManager::drawButton - cursor (%d, %d), size (%d, %d)", x, y, h, w);
    ssd1306.setCursor(ssd1306.getCursorX()+3, y); // reset cursor
    // Log.traceln("DisplayManager::drawButton - cursor (%d, %d), size (%d, %d)", x, y, h, w);

}