#include "Display.h"

Display display;

#define FONT_HEIGHT 8
#define FONT_WIDTH 6
#define STATUS_ROW 0
#define STATUS_COL 0
#define WIFI_ROW 2
#define WIFI_COL 0
#define MQTT_ROW 2
#define MQTT_COL 11
#define IP_ADDRESS_ROW 4
#define IP_ADDRESS_COL 0
#define MEMORY_ROW 6
#define MEMORY_COL 0

Display::Display()
{
}

void Display::initialize()
{
    ssd1306 = Adafruit_SSD1306(128, 64, &Wire);
    ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

    ssd1306.clearDisplay();
    ssd1306.setTextSize(1);
    ssd1306.setTextColor(SSD1306_WHITE);

    eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                 { display.eventHandler(arg, base, id, data); });

    Log.infoln("Creating display task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { display.displayTask(pvParameters); },
        "display_task",
        1024,
        (void *)1,
        tskIDLE_PRIORITY,
        &displayTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("FAILED TO CREATE DISPLAY TASK");
    }
}

void Display::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    Event event = (Event)id;
    switch (event)
    {
    case Event::INITIALIZING:
        setStatusMessage("Initializing");
        break;
    case Event::WAITING:
        setStatusMessage("Waiting");
        setNetworkStatus();
        break;
    case Event::MSG_RECEIVED:
        setStatusMessage("Msg Received");
        break;
    case Event::PROCESSING:
        setStatusMessage("Processing");
        break;
    case Event::ACTIVE:
        break;
    case Event::DEACTIVE:
        break;
    case Event::WIFI_DOWN:
        setStatusMessage("WIFI ERROR");
        setNetworkStatus();
        break;
    case Event::MQTT_DOWN:
        setStatusMessage("MQTT ERROR");
        setNetworkStatus();
        setIpAddress();
        break;
    case Event::WIFI_UP:
        setStatusMessage("WIFI UP");
        setNetworkStatus();
        setIpAddress();
        break;
    case Event::MQTT_UP:
        setStatusMessage("MQTT UP");
        setNetworkStatus();
        setIpAddress();
        break;
    case Event::ERROR:
        setStatusMessage("Error!");
        break;
    default:
        break;
    }
    ssd1306.display();
}

void Display::displayTask(void *pvParameters)
{
    Log.infoln("Starting display task.");

    setStatusMessage(Helper::toString(Event::INITIALIZING));
    setNetworkStatus();
    setIpAddress();

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        setNetworkStatus();
        setMemory();
        ssd1306.display();
    }
}
void Display::setStatusMessage(const char *msg)
{
    // statusMessage = msg;
    clearRow(STATUS_ROW);
    setCursor(STATUS_ROW, STATUS_COL);
    ssd1306.print("Status: ");
    ssd1306.print(msg);
    // ssd1306.display(); // actually display all of the above
}

void Display::setNetworkStatus()
{
    clearRow(WIFI_ROW);
    if (WIFI_ROW != MQTT_ROW)
    {
        clearRow(MQTT_ROW);
    }
    setCursor(WIFI_ROW, WIFI_COL);
    ssd1306.print("WIFI: ");
    if (stateManager.wifi == false)
    {
        ssd1306.print("Down");
    }
    else
    {
        ssd1306.print(stateManager.rssi);
    }
    setCursor(MQTT_ROW, MQTT_COL);
    ssd1306.print("MQTT: ");
    if (stateManager.mqtt == false)
    {
        ssd1306.print("Down");
    }
    else
    {
        ssd1306.print("Up");
    }
    // ssd1306.display(); // actually display all of the above
}

void Display::setIpAddress()
{
    clearRow(IP_ADDRESS_ROW);
    setCursor(IP_ADDRESS_ROW, IP_ADDRESS_COL);
    ssd1306.print("IP: ");
    ssd1306.print(WiFi.localIP());
    // ssd1306.display(); // actually display all of the above
}

void Display::setMemory()
{
    clearRow(MEMORY_ROW);
    setCursor(MEMORY_ROW, MEMORY_COL);
    ssd1306.print("MEMORY: ");
    ssd1306.print(ESP.getFreeHeap());
    ssd1306.print("KB");
}
void Display::clearRow(uint8_t row)
{
    uint8_t start = row * FONT_HEIGHT;
    uint8_t end = start + FONT_HEIGHT - 1;

    for (uint8_t y = start; y <= end; y++)
    {
        for (uint8_t x = 0; x < 127; x++)
        {
            ssd1306.drawPixel(x, y, BLACK);
        }
    }
}
void Display::setCursor(uint8_t row, uint8_t col)
{
    uint8_t r = row * FONT_HEIGHT;
    uint8_t c = col * FONT_WIDTH;
    ssd1306.setCursor(c, r);
}
