#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

char ssid[] = "shhh";
char pass[] = "definitely didn't keep these in here";
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
const char broker[] = "like yeah go ahead ddos a college";
const int port = 1883;
const char publishTopic[] = "charlieleemburg/test";
const char subscribeTopic[] = "charlieleemburg/test";
long count = 0;
const long interval = 1000;
unsigned long previousMillis = 0;


DHT11 dht11(8);
int trial[3000] = {};

LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t Go[8] = {
  0b00000,
  0b11000,
  0b10100,
  0b10010,
  0b10001,
  0b10010,
  0b10100,
  0b11000
};
uint8_t Left[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b01000,
  0b11111,
  0b01000,
  0b00100,
  0b00000
};
uint8_t Right[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b00010,
  0b11111,
  0b00010,
  0b00100,
  0b00000
};
uint8_t El[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10101,
  0b00000,
  0b00000,
  0b00000
};


uint8_t R[8] = {
  0b00000,
  0b01110,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};


void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(7, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);

  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  Serial.begin(9600);
  lcd.createChar(3, Go);
  lcd.createChar(4, Left);
  lcd.createChar(5, Right);
  lcd.createChar(6, El);
  lcd.createChar(1, R);
}


void loop() {
  int choise = 0;
  bool chosen = true;
  while (choise != 100) {
    while (chosen) {

      // awful no good code
      lcd.setCursor(0, 1);
      lcd.print("\x04       \x05      \x03");
      while (chosen) {
        if (digitalRead(4) == HIGH) {
          choise = (choise + 1) % 3;
          lcd.setCursor(0, 0);
          if (choise == 0) lcd.print("Sensor ");
          if (choise == 1) lcd.print("Server ");
          if (choise == 2) lcd.print("Console");
          delay(250);
        }
        if (digitalRead(7) == HIGH) {
          choise = (((choise - 1) % 3) + 3) % 3;
          lcd.setCursor(0, 0);
          if (choise == 0) lcd.print("Sensor ");
          if (choise == 1) lcd.print("Server ");
          if (choise == 2) lcd.print("Console");
          delay(250);
        }
        lcd.setCursor(0, 0);
        if (choise == 0) lcd.print("Sensor ");
        if (choise == 1) lcd.print("Server ");
        if (choise == 2) lcd.print("Console");

        if (digitalRead(2) == HIGH) {
          chosen = false;
          delay(250);
        }
      }

      if (choise == 0) {
        chosen = true;
        bool opts = true;
        choise = 0;
        while (chosen) {
          if (opts) {
            lcd.setCursor(0, 1);
            lcd.print("\x04       \x05      \x06");

          } else {
            lcd.setCursor(0, 1);
            lcd.print("\x03       x      \x06");
          }
          if (digitalRead(2) == HIGH) {
            opts = !opts;
            delay(250);
          }

          if (digitalRead(4) == HIGH && opts) {
            choise = (choise + 1) % 5;
            lcd.setCursor(0, 0);
            if (choise == 0) lcd.print("Temperature");
            if (choise == 1) lcd.print("Humidity   ");
            if (choise == 2) lcd.print("Light      ");
            if (choise == 3) lcd.print("Flame      ");
            if (choise == 4) lcd.print("Distance      ");
            delay(250);
          }
          if (digitalRead(4) == HIGH && !opts) {
            choise = 100;
            chosen = false;
            delay(250);
          }
          if (digitalRead(7) == HIGH && !opts) {
            chosen = false;
            delay(250);
          }
          if (digitalRead(7) == HIGH && opts) {
            choise = (((choise - 1) % 5) + 5) % 5;
            lcd.setCursor(0, 0);
            if (choise == 0) lcd.print("Temperature");
            if (choise == 1) lcd.print("Humidity   ");
            if (choise == 2) lcd.print("Light      ");
            if (choise == 3) lcd.print("Flame      ");
            if (choise == 4) lcd.print("Distance      ");
            delay(250);
          }
          lcd.setCursor(0, 0);
          if (choise == 0) lcd.print("Temperature");
          if (choise == 1) lcd.print("Humidity   ");
          if (choise == 2) lcd.print("Light      ");
          if (choise == 4) lcd.print("Distance     ");
          if (choise == 3) lcd.print("Flame      ");
        }
      } else if (choise == 2) {
        chosen = true;
        bool opts = true;
        choise = 0;
        while (chosen) {
          if (opts) {
            lcd.setCursor(0, 1);
            lcd.print("\x04       \x05      \x06");

          } else {
            lcd.setCursor(0, 1);
            lcd.print("\x03       x      \x06");
          }
          if (digitalRead(2) == HIGH) {
            opts = !opts;
            delay(250);
          }

          if (digitalRead(4) == HIGH && opts) {
            choise = (choise + 1) % 4;
            lcd.setCursor(0, 0);
            if (choise == 0) lcd.print("Newline");
            if (choise == 1) lcd.print("Space   ");
            if (choise == 2) lcd.print("Tab      ");
            if (choise == 3) lcd.print("Comma      ");
            delay(250);
          }
          if (digitalRead(4) == HIGH && !opts) {
            choise = 100;
            chosen = false;
            delay(250);
          }
          if (digitalRead(7) == HIGH && !opts) {
            chosen = false;
            choise += 10;
            delay(250);
          }
          if (digitalRead(7) == HIGH && opts) {
            choise = (((choise - 1) % 4) + 4) % 4;
            lcd.setCursor(0, 0);
            if (choise == 0) lcd.print("Newline");
            if (choise == 1) lcd.print("Space   ");
            if (choise == 2) lcd.print("Tab      ");
            if (choise == 3) lcd.print("Comma      ");
            delay(250);
          }
          lcd.setCursor(0, 0);
          if (choise == 0) lcd.print("Newline");
          if (choise == 1) lcd.print("Space   ");
          if (choise == 2) lcd.print("Tab      ");
          if (choise == 3) lcd.print("Comma      ");
        }
      } else if (choise == 1) {
        lcd.setCursor(0, 0);
        lcd.print("Connecting");
        lcd.setCursor(0, 1);
        lcd.print("                             ");
        bool bbb = false;
        lcd.setCursor(0, 0);
        while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
          delay(2500);
          bbb = !bbb;
          if (bbb) {
            lcd.setCursor(0, 0);
            lcd.print("Connecting.");
          } else {
            lcd.setCursor(0, 0);
            lcd.print("Connecting ");
          }
        }
        bool MQTTconnected = false;
        while (!MQTTconnected) {
          if (!mqttClient.connect(broker, port)) delay(1000);
          else MQTTconnected = true;
        }
        mqttClient.onMessage(onMqttMessage);
        mqttClient.subscribe(subscribeTopic);
        lcd.print("finally");
      }
    }

    int val = 0;
    bool flash = true;
    int index = 0;
    if (choise == 10) {
      while (trial[index] != NULL) {
        Serial.println(trial[index]);
        index++;
      }
      choise = 100;
    }
    if (choise == 11) {
      while (trial[index] != NULL) {
        Serial.print(trial[index]);
        Serial.print(" ");
        index++;
      }

      Serial.print("\n");
      choise = 100;
    }
    if (choise == 13) {
      while (trial[index] != NULL) {
        Serial.print(trial[index]);
        Serial.print(",");
        index++;
      }

      Serial.print("\n");
      choise = 100;
    }
    if (choise == 12) {
      while (trial[index] != NULL) {
        Serial.print(trial[index]);
        Serial.print("\t");
        index++;
      }

      Serial.print("\n");
      choise = 100;
    }

    if (choise != 100) {

      lcd.setCursor(0, 0);
      lcd.print("                                                                ");
      lcd.setCursor(0, 1);
      lcd.print("\x03      REC     x");


      chosen = true;
      bool recording = false;

      while (chosen) {
        if (digitalRead(2) == HIGH) {
          chosen = false;
          choise = 100;
          delay(250);
        }
        if (digitalRead(4) == HIGH) {
          recording = !recording;

          if (recording) {
            lcd.setCursor(0, 1);
            flash = true;
            lcd.print("\x03     \x01REC     x");
          } else {
            lcd.setCursor(0, 1);
            lcd.print("\x03      REC     x");
          }


          delay(250);
        }

        if (recording) {
          if (index < 3000) {
            trial[index] = val;
            index += 1;


            lcd.setCursor(0, 1);
            if (flash) {
              lcd.print("\x03     \x01REC     x");
            } else {

              lcd.print("\x03      REC     x");
            }
            flash = !flash;
          } else {
            lcd.setCursor(0, 1);
            lcd.print("\x03     !REC     x");
          }
        }
        int temperature = dht11.readTemperature();
        int humidity = dht11.readHumidity();
        if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT && humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
          if (choise == 0) {
            lcd.setCursor(0, 0);
            lcd.print("T = ");
            lcd.print(temperature);
            lcd.print((char)223);
            lcd.print("C");
            val = temperature;
          }
          if (choise == 1) {
            lcd.setCursor(0, 0);
            lcd.print("q = ");
            lcd.print(humidity);
            lcd.print("%");
            val = humidity;
          }
          if (choise == 2) {
            int value = analogRead(A0);
            lcd.setCursor(0, 0);
            lcd.print("E = ");
            lcd.print(value);
            lcd.print("lx");
            val = value;
          }
          if (choise == 3) {
            int value = analogRead(A1);
            lcd.setCursor(0, 0);
            lcd.print("x = ");
            lcd.print(value);
            lcd.print("");
            val = value;
          }
          if (choise == 4) {
            digitalWrite(9, LOW);
            delayMicroseconds(2);
            digitalWrite(9, HIGH);
            delayMicroseconds(10);
            digitalWrite(9, LOW);

            double sss = pulseIn(10, HIGH);
            int value = (sss * .0343) / 2;
            lcd.setCursor(0, 0);
            lcd.print("d = ");
            lcd.print(value);
            lcd.print("cm   ");
            val = value;
          }
          delay(20);
        }
      }
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("                                                                ");
}
void onMqttMessage(int messageSize) {
  //...
}
