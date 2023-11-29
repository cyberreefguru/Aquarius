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
    ssd1306.setCursor(0,0);
    ssd1306.print("012345678901234567890123456789");
    ssd1306.display();
    delay(2000);
    ssd1306.clearDisplay();
    setState("Booting...");

    eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                 { display.eventHandler(arg, base, id, data); });
}

void Display::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    State state = (State)id;
    switch (state)
    {
    case State::ACTIVE:
    case State::DEACTIVE:
    case State::WIFI_DOWN:
        setState("WIFI ERROR");
        setNetworkStatus();
        break;
    case State::MQTT_DOWN:
        setState("MQTT ERROR");
        setNetworkStatus();
        setIpAddress();
        break;
    case State::WIFI_UP:
        setState("WIFI UP");
        setNetworkStatus();
        setIpAddress();
        break;
    case State::MQTT_UP:
        setState("MQTT UP");
        setNetworkStatus();
        setIpAddress();
        break;
    case State::RECEIVING:
        setState("Receiving");
        break;
    case State::PROCESSING:
        setState("Processing");
        break;
    case State::SENDING:
        setState("Sending");
        break;
    case State::INITIALIZING:
        setState("Initializing");
        setNetworkStatus();
        break;
    case State::WAITING:
        setState("Waiting");
        setNetworkStatus();
        break;
    case State::ERROR:
        setState("Error!");
        break;
    default:
        break;
    }
}

void Display::setState(const char *msg)
{
    clearRow(STATUS_ROW);
    setCursor(STATUS_ROW, STATUS_COL);
    ssd1306.print("Status: ");
    ssd1306.print(msg);
    ssd1306.display(); // actually display all of the above
}

void Display::setNetworkStatus()
{
    clearRow(WIFI_ROW);
    if( WIFI_ROW != MQTT_ROW)
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
    ssd1306.display(); // actually display all of the above
}

void Display::setIpAddress()
{
    clearRow(IP_ADDRESS_ROW);
    setCursor(IP_ADDRESS_ROW, IP_ADDRESS_COL);
    ssd1306.print("IP: ");
    ssd1306.print( WiFi.localIP() );
    ssd1306.display(); // actually display all of the above
}


void Display::clearRow(uint8_t row)
{
    uint8_t start = row * FONT_HEIGHT;
    uint8_t end = start + FONT_HEIGHT-1;

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

