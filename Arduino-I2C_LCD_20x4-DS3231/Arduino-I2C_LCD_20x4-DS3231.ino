#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <BigFont01_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
BigFont01_I2C bigFont(&lcd);
RTC_DS3231 rtc;

const char* dayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int prevMinuteTens = -1;

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  bigFont.begin();
  if (!rtc.begin()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RTC not found!");
    while (1);
  }
  lcd.setCursor(0, 3);
  lcd.print("Temp: ");
}

void loop() {
  DateTime now = rtc.now();
  float temperature = rtc.getTemperature();
  int row = 0;

  int hourTens = now.hour() / 10;
  int hourTensCol = (hourTens == 1) ? 3 : 2;
  bigFont.writeint(row, hourTensCol, hourTens, 1, true);

  bigFont.writeint(row, 5, now.hour() % 10, 1, true);

  int minuteTens = now.minute() / 10;
  int minuteTensCol = (minuteTens == 1) ? 11 : 10;

  if (prevMinuteTens == 0 && minuteTens == 1) {
    lcd.clear();
    lcd.setCursor(0, 3);
    lcd.print("Temp: ");
  }

  if (minuteTens != prevMinuteTens && prevMinuteTens != -1) {
    int prevMinuteTensCol = (prevMinuteTens == 1) ? 11 : 10;
    bigFont.writeint(row, prevMinuteTensCol, ' ', 1, true);
  }

  bigFont.writeint(row, minuteTensCol, minuteTens, 1, true);
  prevMinuteTens = minuteTens;

  bigFont.writeint(row, 13, now.minute() % 10, 1, true);

  lcd.setCursor(17, 1);
  if (now.second() < 10) lcd.print('0');
  lcd.print(now.second());

  lcd.setCursor(0, 2);
  lcd.print("Date: ");
  if (now.day() < 10) lcd.print('0');
  lcd.print(now.day());
  lcd.print(' ');
  lcd.print(monthNames[now.month() - 1]);
  lcd.print(' ');
  lcd.print(dayNames[now.dayOfTheWeek()]);
  lcd.print("     ");

  lcd.setCursor(6, 3);
  lcd.print("        ");

  lcd.setCursor(6, 3);
  lcd.print(temperature, 2);
  lcd.print((char)223);
  lcd.print("C");

  delay(1000);
}
