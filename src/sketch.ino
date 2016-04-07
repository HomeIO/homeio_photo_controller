// flash led for communication time
#define LED_PIN 13
#define COMM_TEST_VALUE 12345

#define AVG_NUM 8

#define ADC_SOLAR_VOLT_CHANELL 0
#define ADC_SOLAR_CURR_CHANELL 1

#define ADC_SOLAR_VOLT_OFFSET 0
// 100kO + 20kO
// 5V input ADC => (5 / 20) * 100 = 25V voltage
// 1023 => 25V = 25000mV
// 1 => (25000 / 1023)  =
#define ADC_SOLAR_VOLT_COEFF 24.4379

#define ADC_SOLAR_CURR_OFFSET -512
// (1023 - 512) => 5A = 5000mA
#define ADC_SOLAR_CURR_COEFF 9.7847


int photoVoltRaw = 0; // photo panel output voltage
int photoCurrRaw = 0; // photo panel output current

int photoVolt = 0; // photo panel output voltage in mV
int photoCurr = 0; // photo panel output current in mA
int photoPower = 0; // photo panel output power in mW

byte command; // command from HomeIO backend
byte buffer = 0; // used for sending reply

void setup()
{
  // initialize the serial communication:
  Serial.begin(38400);
  while (!Serial) ;
}

// author: Debasish Dutta/deba168, www.opengreenenergy.in
int avgAdcRead(int channel){
  int sum = 0;
  int temp;
  int i;

  for (i=0; i<AVG_NUM; i++) {          // loop through reading raw adc values AVG_NUM number of times
    temp = analogRead(channel);        // read the input pin
    sum += temp;                       // store sum for averaging
    delayMicroseconds(50);             // pauses for 50 microseconds
  }
  return(sum / AVG_NUM);               // divide sum by AVG_NUM to get average and return it
}

void readAllAdcs() {
  photoVoltRaw = avgAdcRead(ADC_SOLAR_VOLT_CHANELL);
  photoCurrRaw = avgAdcRead(ADC_SOLAR_CURR_CHANELL);

  photoCurr = (photoCurrRaw + ADC_SOLAR_CURR_OFFSET) * ADC_SOLAR_CURR_COEFF;
  photoVolt = (photoVoltRaw + ADC_SOLAR_VOLT_OFFSET) * ADC_SOLAR_VOLT_COEFF;
  photoPower = photoCurr * photoVolt / 1000;
}

void loop() {
  readAllAdcs();

  // check if data has been sent from the computer:
  if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):
    digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)

    command = Serial.read();
    if (command == '0') {
      buffer = photoVoltRaw / 256;
      Serial.write(buffer);

      buffer = photoVoltRaw % 256;
      Serial.write(buffer);
    }

    if (command == '1') {
      buffer = photoCurrRaw / 256;
      Serial.write(buffer);

      buffer = photoCurrRaw % 256;
      Serial.write(buffer);
    }

    if (command == 'a') {
      buffer = photoVolt / 256;
      Serial.write(buffer);

      buffer = photoVolt % 256;
      Serial.write(buffer);
    }

    if (command == 'b') {
      buffer = photoCurr / 256;
      Serial.write(buffer);

      buffer = photoCurr % 256;
      Serial.write(buffer);
    }

    if (command == 'p') {
      buffer = photoPower / 256;
      Serial.write(buffer);

      buffer = photoPower % 256;
      Serial.write(buffer);
    }

    if (command == 't') {
      buffer = COMM_TEST_VALUE / 256;
      Serial.write(buffer);

      buffer = COMM_TEST_VALUE % 256;
      Serial.write(buffer);
    }

    if (command == 's') {
      buffer = 0;
      Serial.write(buffer);
    }

    digitalWrite(LED_PIN, LOW);
  }


}
