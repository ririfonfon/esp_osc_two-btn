
// which can use both WiFi and Ethernet
#include <ArduinoOSCWiFi.h>

#include <ezButton.h>

ezButton button1(13); // create ezButton object that attach to pin 7;
ezButton button2(12); // create ezButton object that attach to pin 7;

// WiFi stuff
const char *ssid = "riri_new";
const char *pwd = "B2az41opbn6397";
const IPAddress ip(192, 168, 0, 121);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);

// for ArduinoOSC
const char *host = "192.168.0.22";
const int recv_port = 8081;
const int bind_port = 8081;
const int send_port = 8081;
const int publish_port = 8081;
// send / receive varibales
int i;
float f;
String s;

void setup()
{
    Serial.begin(115200);
    button1.setDebounceTime(100);
    button2.setDebounceTime(100);
    delay(2000);

    // WiFi stuff (no timeout setting for WiFi)
#if defined(ESP_PLATFORM) || defined(ARDUINO_ARCH_RP2040)
#ifdef ESP_PLATFORM
    WiFi.disconnect(true, true); // disable wifi, erase ap info
#else
    WiFi.disconnect(true); // disable wifi
#endif
    delay(1000);
    WiFi.mode(WIFI_STA);
#endif

    WiFi.begin(ssid, pwd);

    WiFi.config(ip, gateway, subnet);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.print("WiFi connected, IP = ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    button1.loop();
    button2.loop();

    if (button1.isPressed())
    {
        Serial.println("The button1 is pressed");
        OscWiFi.send(host, publish_port, "/button1/on", 1);
    }

    if (button1.isReleased())
    {
        Serial.println("The button1 is released");
        OscWiFi.send(host, publish_port, "/button1/off", 1);
    }
    if (button2.isPressed())
    {
        Serial.println("The button2 is pressed");
        OscWiFi.send(host, publish_port, "/button2/on", 1);
    }

    if (button2.isReleased())
    {
        Serial.println("The button2 is released");
        OscWiFi.send(host, publish_port, "/button2/off", 1);
    }
}
