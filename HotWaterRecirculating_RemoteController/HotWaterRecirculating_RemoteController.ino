const byte inputPinA = 2;
const byte inputPinB = 3;
const byte outputPin = 12;

const unsigned long periodA = 120000;
const unsigned long periodB = 240000;

struct RelayInfo
{
  unsigned long lastHight = 0;
  unsigned long period;
  bool isOn = false;
  byte pin;
} relayA, relayB;

void readState(RelayInfo* relayInfo, unsigned long now)
{
  if (digitalRead(relayInfo->pin) == LOW)
  {
    relayInfo->lastHight = now;
    relayInfo->isOn = true;
  }
}

void checkPeriod(RelayInfo* relayInfo, unsigned long now)
{
  if (relayInfo->isOn)
  {
    unsigned long diff = now - relayInfo->lastHight;
    if (diff > relayInfo->period)
    {
      relayInfo->isOn = false;
    }
  }
}

void setup() {
  relayA.period = periodA;
  relayA.pin = inputPinA;
  relayB.period = periodB;
  relayB.pin = inputPinB;
  
  pinMode(inputPinA, INPUT_PULLUP);
  pinMode(inputPinB, INPUT_PULLUP);
  pinMode(outputPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  
  readState(&relayA, now);
  readState(&relayB, now);

  checkPeriod(&relayA, now);
  checkPeriod(&relayB, now);
  
  digitalWrite(outputPin, relayA.isOn || relayB.isOn ? HIGH : LOW);
}
