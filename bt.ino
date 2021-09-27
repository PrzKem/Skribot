#include "BluetoothSerial.h"
#include <Skribot.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

Skribot robot;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  robot.AddDCRotor("LEFT");          
  robot.AddDCRotor("RIGHT");
  robot.SetSpeed(100);
}

void loop() {
  char actualValue;
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    actualValue = SerialBT.read();
    Serial.write(actualValue);
    if(actualValue == 'w')
    {
      robot.MoveForward(1000);
    }
    else if (actualValue == 's')
    {
      robot.MoveBack(1000);
    }
    else if (actualValue == 'd')
    {
      robot.FaceRight(1000);
    }
    else if (actualValue == 'a')
    {
      robot.FaceLeft(1000);
    }
  }
  delay(20);
}
