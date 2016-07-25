#include <DmxMaster.h>

void setup() {
  DmxMaster.usePin(3);
  DmxMaster.maxChannel(4);
}

void loop() {
  int brightness;
  for (brightness = 0; brightness <= 255; brightness++) {
    DmxMaster.write(1, brightness);
    DmxMaster.write(2, 0);
    DmxMaster.write(3, 0);
    DmxMaster.write(4, 255);
    delay(5);
  }
  for (brightness = 0; brightness <= 255; brightness++) {
    DmxMaster.write(2, brightness);
    DmxMaster.write(1, 0);
    DmxMaster.write(3, 0);
    DmxMaster.write(4, 255);
    delay(5);
  }
    for (brightness = 0; brightness <= 255; brightness++) {
    DmxMaster.write(3, brightness);
    DmxMaster.write(1, 0);
    DmxMaster.write(2, 0);
    DmxMaster.write(4, 255);
    delay(5);
  }
}
