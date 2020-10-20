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
  Serial.print(channel[0]); Serial.print("\t");
  Serial.print(channel[1]); Serial.print("\t");
  Serial.print(channel[2]); Serial.print("\t");
  Serial.print(channel[3]); Serial.print("\t");
  Serial.print(channel[4]); Serial.print("\t");
  Serial.print(channel[5]); Serial.print("\t");
  Serial.print(channel[6]); Serial.print("\t");
  Serial.print(channel[7]); Serial.print("\t");
  Serial.println();
  delay(10);
}


void readPulse() {
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
