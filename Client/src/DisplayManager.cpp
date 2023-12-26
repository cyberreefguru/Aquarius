#include "DisplayManager.h"

DisplayManager displayManager;

#define FONT_HEIGHT 8
#define FONT_WIDTH 6
#define STATUS_ROW 0
#define STATUS_COL 8
#define WIFI_ROW 2
#define WIFI_COL 0
#define MQTT_ROW 2
#define MQTT_COL 11
#define IP_ADDRESS_ROW 4
#define IP_ADDRESS_COL 0
#define MEMORY_ROW 6
#define MEMORY_COL 0
#define NODE_ROW 0
#define NODE_COL 0

DisplayManager::DisplayManager()
{
}

void DisplayManager::initialize()
{
    ssd1306 = Adafruit_SSD1306(128, 64, &Wire);
    ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

    ssd1306.clearDisplay();
    ssd1306.setTextSize(1);
    ssd1306.setTextColor(SSD1306_WHITE);

    setNode();
    setStatusMessage( Helper::toString(Event::INITIALIZING));
    setNetworkStatus();
    setMemory(true);

    eventManager.addEventHandler([](void *arg, esp_event_base_t base, int32_t id, void *data)
                                 { displayManager.eventHandler(arg, base, id, data); });

    Log.infoln("Creating display task.");
    BaseType_t xReturned = xTaskCreate(
        [](void *pvParameters)
        { displayManager.displayTask(pvParameters); },
        "display_task",
        2048,
        (void *)1,
        tskIDLE_PRIORITY,
        &displayTaskHandle);
    if (xReturned != pdPASS)
    {
        Log.errorln("FAILED TO CREATE DISPLAY TASK");
    }
}

void DisplayManager::setSize(DisplaySize size)
{
    this->size = size;
    prefManager.set(KEY_DISPLAY_SIZE, (uint8_t)(size));
}

void DisplayManager::eventHandler(void *arg, esp_event_base_t base, int32_t id, void *data)
{
    Event event = (Event)id;
    switch (event)
    {
    case Event::INITIALIZING:
        setStatusMessage("Initializing", true);
        break;
    case Event::WAITING:
        setStatusMessage("Waiting", true);
        break;
    case Event::MSG_RECEIVED:
        setStatusMessage("Msg Received", true);
        break;
    case Event::PROCESSING:
        setStatusMessage("Processing", true);
        break;
    case Event::ACTIVE:
        break;
    case Event::DEACTIVE:
        break;
    case Event::WIFI_DOWN:
        setStatusMessage("WIFI ERROR");
        setNetworkStatus(true);
        break;
    case Event::WIFI_UP:
        setStatusMessage("WIFI UP");
        setNetworkStatus(true);
        break;
    case Event::MQTT_DOWN:
        setStatusMessage("MQTT ERROR");
        setNetworkStatus(true);
        break;
    case Event::MQTT_UP:
        setStatusMessage("MQTT UP");
        setNetworkStatus(true);
        break;
    case Event::NODE_ID_CHANGE:
        setNode(true);
        break;
    case Event::ERROR:
        setStatusMessage("ERROR", true);
        break;
    default:
        break;
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
        vTaskDelay(pdMS_TO_TICKS(100));
        clicks++;
        if( clicks >= 10 )
        {
            setNetworkStatus();
            setMemory(true);
            clicks = 0;
        }
        if( refresh )
        {
            ssd1306.display();
            refresh = false;
        }
    }
}

void DisplayManager::setStatusMessage(const char *msg, bool refresh)
{
    clearRow(STATUS_ROW, STATUS_COL, STATUS_ROW, 21);
    // clearRow(STATUS_ROW);
    setCursor(STATUS_ROW, STATUS_COL);
    //ssd1306.print("-");
    ssd1306.print(msg);
    this->refresh = refresh;
}

void DisplayManager::setNetworkStatus(bool refresh)
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

    clearRow(IP_ADDRESS_ROW);
    setCursor(IP_ADDRESS_ROW, IP_ADDRESS_COL);
    ssd1306.print("IP: ");
    if( stateManager.wifi == false )
    {
        ssd1306.print("0.0.0.0");
    }
    else
    {
        ssd1306.print(WiFi.localIP());
    }
    this->refresh = refresh;
}

void DisplayManager::setMemory(bool refresh)
{
    clearRow(MEMORY_ROW, MEMORY_COL, MEMORY_ROW, 21);
    setCursor(MEMORY_ROW, MEMORY_COL);
    ssd1306.print("MEM: ");
    uint32_t m = ESP.getFreeHeap();
    if( m > 10000000)
    {
    ssd1306.print(m/1000);
    ssd1306.print("K");
    }
    else
    {
    ssd1306.print(m);
    }
    this->refresh = refresh;
}

void DisplayManager::setNode(bool refresh)
{
    clearRow(NODE_ROW, NODE_COL, NODE_ROW, 8);
    setCursor(NODE_ROW, NODE_COL);
    ssd1306.print("ID ");
    ssd1306.printf("%3.3d",prefManager.getId());
    ssd1306.print(": ");
    this->refresh = refresh;
}


void DisplayManager::clearRow(uint8_t row)
{
    ssd1306.fillRect(0, row * FONT_HEIGHT, 128, FONT_HEIGHT, BLACK);
}

void DisplayManager::clearRow(uint8_t srow, uint8_t scol, uint8_t erow, uint8_t ecol)
{

    uint8_t xstart = scol*FONT_WIDTH;
    uint8_t width = (ecol - scol + 1)*FONT_WIDTH;

    uint8_t ystart = srow * FONT_HEIGHT;
    uint8_t height = (erow - srow + 1)*FONT_HEIGHT;

    ssd1306.fillRect(xstart, ystart, width, height, BLACK);

}


void DisplayManager::setCursor(uint8_t row, uint8_t col)
{
    uint8_t r = row * FONT_HEIGHT;
    uint8_t c = col * FONT_WIDTH;
    ssd1306.setCursor(c, r);
}
