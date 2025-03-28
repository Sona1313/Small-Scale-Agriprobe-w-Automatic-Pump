int baselineTemp = 40;  
int celsius = 0;
int fahrenheit = 0;

#define TEMP_SENSOR A0  // TMP36 connected to Analog A0
#define SOIL_SENSOR A1  // Soil Moisture Sensor connected to Analog A1
#define MOTOR_IN1 7     // L293D Motor - Direction 1
#define MOTOR_IN2 8     // L293D Motor - Direction 2
#define MOTOR_PWM 9     // PWM speed control

const int soilMoistureThreshold = 400; 
void setup() {
  Serial.begin(9600);

  
  pinMode(TEMP_SENSOR, INPUT);
  pinMode(SOIL_SENSOR, INPUT);


  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
}

void loop() {
  
  int tempReading = analogRead(TEMP_SENSOR);
  celsius = map(((tempReading - 20) * 3.04), 0, 1023, -40, 125);
  
  fahrenheit = ((celsius * 9) / 5 + 32);

  int soilMoisture = analogRead(SOIL_SENSOR);

  // Print sensor data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print("°C | Soil Moisture: ");
  Serial.println(soilMoisture);

  // Condition to activate motor
  if (celsius >= baselineTemp || soilMoisture < soilMoistureThreshold) {
    Serial.println("Activating motor...");
    activateMotor();
  } else {
    stopMotor();
  }

  delay(2000);
}

void activateMotor() {
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_PWM, 150);  

  Serial.println("Motor is ON...");
}

void stopMotor() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_PWM, 0);  

  Serial.println("Motor is OFF...");
}
