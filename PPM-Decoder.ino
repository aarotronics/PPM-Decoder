/*
                                          ARDUINO PPM DECODER FOR RC
                                 ===============================================
   
   This decoder uses external interrupts so pins D2 or D3 must be used in case of the ATMEGA328P. Make sure to 
   adjust PPM_CHANNELS to the number of channels used by the system to decode.

   "THE BEERWARE LICENSE" (Revision 42):
   Aaron G. wrote this code in October 2020. As long as you retain this
   notice, you can do whatever you want with this stuff. If we meet someday,
   and you think this stuff is worth it, you can buy me a beer in return.
*/

#define PPM_PIN           2
#define PPM_CHANNELS      8


uint8_t channelCount;
uint16_t channelRaw[PPM_CHANNELS], channel[PPM_CHANNELS];
uint32_t thisPulseTime = 0, lastPulseTime = 0;


void setup() {
  Serial.begin(57600);
  pinMode(PPM_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PPM_PIN), readPulse, RISING);

}

void loop() {
  for (int i = 0; i < PPM_CHANNELS; i++) {
    Serial.print(channel[i]); Serial.print("\t");
  }
  Serial.println();
  delay(10);
}


void readPulse(void) {
  thisPulseTime = micros();
  if ((thisPulseTime - lastPulseTime) > 5000) {
    for (int i = 0; i < PPM_CHANNELS; i++) {
      channel[i] = channelRaw[i];
    }
    channelCount = 0;
  } else {
    channelRaw[channelCount] = thisPulseTime - lastPulseTime;
    channelCount++;
  }
  lastPulseTime = thisPulseTime;
}
