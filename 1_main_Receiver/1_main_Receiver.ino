#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 1;
const static uint8_t DESTINATION_RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;

int xInput = A0;
int yInput = A1;
int zInput = A2;



int inByte = 0;         // incoming serial byte

enum RadioPacketType
{
    Heartbeat
};

struct RadioPacket
{
    RadioPacketType PacketType;
    uint8_t FromRadioId;
    uint32_t OnTimeMillis;
    byte temperature;
    byte xData;
    byte yData;
    byte zData;
};

NRFLite _radio;
uint32_t _lastHeartbeatSendTime;

void setup()
{
    Serial.begin(115200);

    establishContact();
    
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Cannot communicate with radio");
        while (1); // Wait here forever.
    }
}

void loop()
{
    // Send a heartbeat once every second.
    if (millis() - _lastHeartbeatSendTime > 999)
    {
        _lastHeartbeatSendTime = millis();
        sendHeartbeat();        
    }

    loopSerial();
    
    // Show any received data.
    checkRadio();
    
}

void sendHeartbeat()
{
    Serial.print("Sending heartbeat");

    RadioPacket radioData;
    radioData.PacketType = Heartbeat;
    radioData.FromRadioId = RADIO_ID;
    radioData.OnTimeMillis = millis();

    if (_radio.send(DESTINATION_RADIO_ID, &radioData, sizeof(radioData))) // 'send' puts the radio into Tx mode.
    {
        Serial.println("...Success");
    }
    else
    {
        Serial.println("...Failed");
    }
}

void checkRadio()
{
    while (_radio.hasData()) // 'hasData' puts the radio into Rx mode.
    {
        RadioPacket radioData;
        _radio.readData(&radioData);

        if (radioData.PacketType == Heartbeat)
        {
            Serial.print( "Heartbeat from ");
            Serial.print( radioData.FromRadioId);
            Serial.print( ", ");
            Serial.print( radioData.OnTimeMillis);
            Serial.println(" ms");
            Serial.print(" Temperature: ");
            Serial.print(radioData.temperature);
            
        }
    }
}
