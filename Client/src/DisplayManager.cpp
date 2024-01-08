#include "DisplayManager.h"

DisplayManager displayManager;

DisplayManager::DisplayManager()
{
}

void DisplayManager::initialize()
{
    ssd1306 = Adafruit_SSD1306(128, 64, &Wire);
    ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
    setBrightness(brightness);
    
    ssd1306.clearDisplay();
    ssd1306.setTextSize(1);
    ssd1306.setTextColor(SSD1306_WHITE);
    ssd1306.clearDisplay();
    refresh = true;

    // actionEventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
    //                                    { displayManager.eventHandler(arg, base, id, data); });

    Log.infoln("Creating display task.");
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
        Log.errorln("FAILED TO CREATE DISPLAY TASK");
    }
}

/***
 * DisplayManager task updates the display when things change.
 */
void DisplayManager::displayTask(void *pvParameters)
{
    Log.infoln("Starting display task.");
    uint8_t clicks = 0;

    for (;;)
    {
        if (refresh)
        {
            ssd1306.display();
            refresh = false;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void DisplayManager::setSize(DisplaySize size)
{
    this->size = size;
    prefManager.set(KEY_DISPLAY_SIZE, (uint8_t)(size));
}

void DisplayManager::setRefresh(bool r)
{
    refresh = r;
}

void DisplayManager::clear()
{
    ssd1306.clearDisplay();
}

void DisplayManager::setTextColor(uint16_t fg)
{
    ssd1306.setTextColor(fg);
}
void DisplayManager::setTextColor(uint16_t fg, uint16_t bg)
{
    ssd1306.setTextColor(fg, bg);
}

void DisplayManager::print(const char *m)
{
    ssd1306.print(m);
}

void DisplayManager::print(uint8_t d)
{
    ssd1306.print(d);
}

void DisplayManager::print(String s)
{
    ssd1306.print(s);
}

void DisplayManager::println(const char *m)
{
    ssd1306.println(m);
}

void DisplayManager::println()
{
    ssd1306.println();
}

void DisplayManager::setBrightness(uint8_t v)
{
    ssd1306.ssd1306_command(SSD1306_SETCONTRAST);
    ssd1306.ssd1306_command(v);
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

void DisplayManager::setCursor(uint8_t row, uint8_t col)
{
    uint8_t r = row * FONT_HEIGHT;
    uint8_t c = col * FONT_WIDTH;
    ssd1306.setCursor(c, r);
}

void DisplayManager::clearRow(uint8_t row)
{
    ssd1306.fillRect(0, row * FONT_HEIGHT, 128, FONT_HEIGHT, BLACK);
}

void DisplayManager::clearRow(uint8_t srow, uint8_t scol, uint8_t erow, uint8_t ecol)
{
    uint8_t xstart = scol * FONT_WIDTH;
    uint8_t width = (ecol - scol + 1) * FONT_WIDTH;

    uint8_t ystart = srow * FONT_HEIGHT;
    uint8_t height = (erow - srow + 1) * FONT_HEIGHT;

    ssd1306.fillRect(xstart, ystart, width, height, BLACK);
}
