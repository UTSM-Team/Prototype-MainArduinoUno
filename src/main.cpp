#include <Arduino.h>
#include <ArduinoBLE.h>



void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
  }

  //search for the UUID of the signal sent from the ESP32
  BLE.scanForUuid("c947c9a0-4c67-4122-942e-4f58db73695e");
  
  //check if a peripheral device has been found
  BLEDevice peripheral = BLE.available();
  //show details of found peripheral
  if (peripheral) {
    Serial.print("Found ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();
    //Stop scanning
    BLE.stopScan();

    Serial.println("Connecting...");

    //connect to the peripheral
    if (peripheral.connect()){
      Serial.println("Connected");
    } else {
      Serial.println("Failed to connect!");
    }
    //show attributes of discovered peripheral
    Serial.println("Discovering Attributes...");
    if (peripheral.discoverAttributes()) {
      Serial.println("Attributes discovered");
    } else {
      Serial.println("Attribute discovery failed!");
    }

    //Analyze the Powermeter Characteristic (UUID from ESP32)
    BLECharacteristic powerCharacteristic = peripheral.characteristic("0cf1a111-9e55-4fe5-9f08-0c326f089553");

    if (!powerCharacteristic) {
      Serial.println("Peripheral does not have the specified characteristic");
    } else {
      Serial.println("Characteristic found. We are good to go!");
    }


  }




}

void loop() {
  // put your main code here, to run repeatedly:



  delay(2000);
}