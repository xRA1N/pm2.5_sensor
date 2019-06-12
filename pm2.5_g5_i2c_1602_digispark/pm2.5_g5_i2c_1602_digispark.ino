#include <SoftSerial.h>    //digispark softserial
//#include <TinyPinChange.h>
#include <LiquidCrystal_I2C.h>

//G5传感器的Tx接 digispark p1
SoftSerial g5Serial(1, 5); // RX, TX
// I2C 1602液晶屏
LiquidCrystal_I2C lcd(0x3f, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int c;
int state;
int count;
int hcf;
int lcf;
int hc;
int lc;
int pm1_0, pm2_5, pm10_0;        //PM1.0、PM2.5、PM10
int i;

void setup()
{
  //Serial.begin(115200);        //USB串口向PC发送数据
  g5Serial.begin(9600);        //软串口连接传感器
  lcd.init();
  lcd.backlight();
  lcd.print("G5 PM2.5 ");
  lcd.setCursor(0, 1);
  lcd.print("version#");
  lcd.clear();
}

void loop()
{
  if (g5Serial.available()) {
    c = g5Serial.read();
    if  (0x42 == c) {
      state = 1;
      count = 0;
      //Serial.println(c,HEX);
    }
    if ( 0x4d == c && state == 1 && count == 0) {
      state = 2 ;
      //Serial.println(c,HEX);
    }
    if ( state == 2) {
      count = count + 1;

    }

    if (count == 6) {
      hcf = c;
      // Serial.print("count6  ");
      // Serial.println(count);
      // Serial.print("pm2.5 high");
      // Serial.println(hcf);
    }
    if (count == 7) {
      lcf = c;
      // Serial.print("count7  ");
      // Serial.println(count);
      // Serial.print("pm2.5 low");
      // Serial.println(lcf);
    }
    if (count == 12) {
      hc = c;
      //Serial.print("count6  ");
      //Serial.println(count);
      //Serial.print("pm2.5 high");
      //Serial.println(hc);
    }
    if (count == 13) {
      lc = c;
      //Serial.print("count7  ");
      //Serial.println(count);
      //Serial.print("pm2.5 low");
      //Serial.println(lc);

    }
    lcd.setCursor(0, 0);
    lcd.print("PM2.5");
    lcd.setCursor(0, 1);
    lcd.print(hc * 256 + lc);
    lcd.print("CN/");
    lcd.print(hcf * 256 + lcf);
    lcd.print("US  ");
    lcd.setCursor(11, 1);
    lcd.print("ug/m3   ");
  }
}
