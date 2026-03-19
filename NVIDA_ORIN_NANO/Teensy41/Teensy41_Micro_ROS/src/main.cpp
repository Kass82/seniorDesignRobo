#include <Servo.h>
#include <Arduino.h>

//#include <micro_ros_arduino.h>

// Pin definitions
const int pwmPin = 25;          // PWM output to ESC
const int ledPin = 13;          // Onboard LED

// ESC pulse width limits
const int pulseMin = 1100;      // full reverse
const int pulseNeutral = 1500;  // stop
const int pulseMax = 1900;      // full forward
/*
//================================================================================
// runAngle Range
// 0 - Full Reverse, 90 - Stop, 180 - Full Forward
//
// Pulse Width Range 
// 1100 - Full Reverse, 1500 - Stop, 1900 - Full Forward
// 
//================================================================================
*/
// Thruster run parameters
const int runAngle = 180;
const unsigned long runDuration = 5000; // 5 seconds

// Test parameters for different write rates
struct RateTest {
  const char* name;
  int frequencyHz;        // Update frequency in Hz
  int delayMicroseconds;  // Delay between writes in microseconds
};

// Define different rates to test (Hz)
RateTest rateTests[] = {
  {"Low rate",     1,   1000000}, // 1 Hz (once per second)
  {"Medium rate",  10,  100000},  // 10 Hz
  {"Standard",     50,  20000},   // 50 Hz (typical servo rate)
  {"Fast",         100, 10000},   // 100 Hz
  {"Very Fast",    200, 5000},    // 200 Hz
  {"Extreme",      500, 2000}     // 500 Hz
};

const int numTests = sizeof(rateTests) / sizeof(rateTests[0]);

Servo thruster;
/*
//================================================================================
// map Function
// 
// map(angle, 0, 180, pulseMin, pulseMax)
// pulseMin = 1100
// pulseMax = 1900
// angle - range = 0 - 180
//         Where: 0 - Full Reverse, 90 - Stop, 180 - Full Forward
//================================================================================
*/
// Helper to convert angle back to pulse width (for display)
int angleToPulse(int angle) {
  return map(angle, 0, 180, pulseMin, pulseMax);
}

void runTest(const RateTest& test, int pulseWidth) {
  
  digitalWrite(ledPin, HIGH);  // LED on during test
  
  // Calculate number of iterations for 5 seconds
  int iterations = test.frequencyHz * 5;
  
  // Variables for timing and monitoring
  unsigned long startTime = micros();
  unsigned long lastPrintTime = 0;
  int actualIterations = 0;
  
  // Run at specified rate for 5 seconds
  for (int i = 0; i < iterations; i++) {
    unsigned long loopStart = micros();
    
    // Write to ESC
    thruster.writeMicroseconds(pulseWidth);
    actualIterations++;
    
    // Print status every second
    if (millis() - lastPrintTime >= 1000) {
      lastPrintTime = millis();
      float elapsedSec = (micros() - startTime) / 1000000.0;
    }
    
    // Precise timing delay
    unsigned long elapsed = micros() - loopStart;
    if (elapsed < test.delayMicroseconds) {
      delayMicroseconds(test.delayMicroseconds - elapsed);
    }
  }
  
  unsigned long totalTime = micros() - startTime;
  float actualRate = (actualIterations * 1000000.0) / totalTime;
  
  digitalWrite(ledPin, LOW);
  delay(2000);  // Pause between tests
}

void setup() {
  //Serial.begin(115200);
  //while (!Serial); // Wait for serial port (optional, for native USB)
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);   // LED on = system powered

  // Attach ESC with min and max pulse widths
  thruster.attach(pwmPin, pulseMin, pulseMax);

  // Set neutral (1500 µs) to arm the ESC
  thruster.writeMicroseconds(pulseNeutral);
  delay(5000);                  // arming delay

  int testPulse = angleToPulse(runAngle);
  
  // Run through all rate tests
  for (int i = 0; i < numTests; i++) {
    // Return to neutral between tests
    thruster.writeMicroseconds(pulseNeutral);
    delay(2000);
    
    // Run the test
    runTest(rateTests[i], testPulse);
  }
  
  // Stop thruster
  thruster.writeMicroseconds(pulseNeutral);

  digitalWrite(ledPin, LOW);
  
}

void loop() {
  // Nothing here – sequence runs once
}