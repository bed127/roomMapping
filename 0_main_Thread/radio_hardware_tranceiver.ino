#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 0;
const static uint8_t DESTINATION_RADIO_ID = 1;
const static uint8_t PIN_RADIO_CE = 48;
const static uint8_t PIN_RADIO_CSN = 49;

enum RadioPacketType
{
    AcknowledgementData, // Produced by the primary receiver and provided to the transmitter via an acknowledgement data packet.
    Heartbeat,    // Sent by the primary transmitter.
    BeginGetData, // Sent by the primary transmitter to tell the receiver it should load itself with an acknowledgement data packet.
    EndGetData    // Sent by the primary transmitter to receive the acknowledgement data packet from the receiver.
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

void setupRadio()  {
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Cannot communicate with radio");
    }
}

void loopRadio()  {
    if (millis() - _lastHeartbeatSendTime > 999)
    {
        _lastHeartbeatSendTime = millis();
        sendHeartbeat();        
    }
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
    } else  {
      Serial.println("...Failed");
    }
}

void checkRadio() {
  
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
       
