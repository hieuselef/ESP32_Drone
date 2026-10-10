#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Mặc định ESP32 dùng chân 21 (SDA) và 22 (SCL)
  
  byte status = mpu.begin();
  Serial.print(F("Trang thai ket noi MPU6050: "));
  Serial.println(status);
  
  // Trạng thái = 0 là kết nối thành công. Khác 0 là lỗi dây.
  while(status != 0){ } 
  
  Serial.println(F("Dang tinh toan sai so (Calibration)... Vui long GIU YEN mach!"));
  delay(1000);
  mpu.calcOffsets(); // Hàm tự động tính toán sai số ban đầu
  Serial.println(F("Da hieu chuan xong!\n"));
}

void loop() {
  mpu.update(); // Bắt buộc phải gọi hàm này liên tục để cập nhật dữ liệu
  
  // Cứ mỗi 50ms (0.05 giây) sẽ in dữ liệu ra màn hình 1 lần để chống giật lag
  if((millis() - timer) > 50){ 
    Serial.print("X (Roll): ");
    Serial.print(mpu.getAngleX());
    
    Serial.print("\tY (Pitch): ");
    Serial.print(mpu.getAngleY());
    
    Serial.print("\tZ (Yaw): ");
    Serial.println(mpu.getAngleZ());
    
    timer = millis();
  }
}