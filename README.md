<img src="https://github.com/user-attachments/assets/cbf35cc3-dd44-4659-91e4-407ee6c62ea6" width="300">

An Arduino code for a Weather station with DS3231 module and I²C 20x4 LCD!

### Libraries needed:
- Wire  
- RTClib  
- LiquidCrystal_I2C  
- BigFont01_I2C  

### Connections:
- DS3231 GND → Arduino GND  
- DS3231 VCC → Arduino 5V  
- DS3231 SDA → Arduino SDA  
- DS3231 SCL → Arduino SCL  
- LCD GND → Arduino GND  
- LCD VCC → Arduino 5V  
- LCD SDA → A4 if Arduino UNO/NANO, 20 if Arduino MEGA  
- LCD SCL → A5 if Arduino UNO/NANO, 21 if Arduino MEGA  
