#include "ArduinoHub.h"

ArduinoHub hub;

void setup() {
  Serial.begin(9600);
  hub.setup();
}

void loop() {
  String msg = hub.readBluetoothMessage();  
  if (msg.length() > 0) {
    Serial.println("==== Bluetooth 수신됨 ====");
    Serial.println("RAW: [" + msg + "]");

    for (char c : msg) hub.btIn(c);
    hub.btIn('\n');
  }

  hub.loopOnce();
}
