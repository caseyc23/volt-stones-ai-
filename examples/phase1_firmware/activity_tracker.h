#ifndef ACTIVITY_TRACKER_H
#define ACTIVITY_TRACKER_H

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

class ActivityTracker {
private:
    MPU6050 accel;
    
    // Activity data
    int dailySteps;
    int dailyCalories;
    bool isMoving;
    unsigned long lastStepTime;
    unsigned long lastResetTime;
    
    // Step detection parameters
    const int STEP_THRESHOLD = 15000;
    const int STEP_MIN_INTERVAL = 300;  // ms between steps
    const int MOVEMENT_THRESHOLD = 5000;
    
    // Calibration
    int16_t accelOffsetX;
    int16_t accelOffsetY;
    int16_t accelOffsetZ;
    
public:
    ActivityTracker() : dailySteps(0), dailyCalories(0), isMoving(false),
                        lastStepTime(0), lastResetTime(0),
                        accelOffsetX(0), accelOffsetY(0), accelOffsetZ(0) {}
    
    bool begin(int sdaPin = 21, int sclPin = 22) {
        Wire.begin(sdaPin, sclPin);
        accel.initialize();
        
        if (!accel.testConnection()) {
            Serial.println("Activity: MPU6050 connection failed");
            return false;
        }
        
        Serial.println("Activity: MPU6050 connected");
        
        // Configure accelerometer
        accel.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
        accel.setDLPFMode(MPU6050_DLPF_BW_20);  // Low-pass filter
        
        // Calibrate
        calibrate();
        
        lastResetTime = millis();
        return true;
    }
    
    void calibrate() {
        Serial.println("Activity: Calibrating (keep still)...");
        
        int32_t sumX = 0, sumY = 0, sumZ = 0;
        const int samples = 100;
        
        for (int i = 0; i < samples; i++) {
            int16_t ax, ay, az;
            accel.getAcceleration(&ax, &ay, &az);
            sumX += ax;
            sumY += ay;
            sumZ += az;
            delay(10);
        }
        
        accelOffsetX = sumX / samples;
        accelOffsetY = sumY / samples;
        accelOffsetZ = sumZ / samples;
        
        Serial.printf("Activity: Calibration complete (X=%d, Y=%d, Z=%d)\n",
            accelOffsetX, accelOffsetY, accelOffsetZ);
    }
    
    void update() {
        int16_t ax, ay, az;
        accel.getAcceleration(&ax, &ay, &az);
        
        // Apply calibration offsets
        ax -= accelOffsetX;
        ay -= accelOffsetY;
        az -= accelOffsetZ;
        
        // Calculate magnitude
        long magnitude = sqrt((long)ax*ax + (long)ay*ay + (long)az*az);
        
        // Step detection
        if (magnitude > STEP_THRESHOLD) {
            unsigned long now = millis();
            if (now - lastStepTime > STEP_MIN_INTERVAL) {
                dailySteps++;
                lastStepTime = now;
                
                // Calculate calories (rough estimate: 0.04 cal per step)
                dailyCalories = dailySteps * 0.04;
                
                Serial.printf("Activity: Step detected! Total=%d, Cal=%d\n", 
                    dailySteps, dailyCalories);
            }
        }
        
        // Movement detection
        isMoving = (magnitude > MOVEMENT_THRESHOLD);
        
        // Auto-reset at midnight (check every hour)
        if (millis() - lastResetTime > 3600000) {  // 1 hour
            checkMidnightReset();
            lastResetTime = millis();
        }
    }
    
    void checkMidnightReset() {
        // This would need RTC or time sync for accurate midnight detection
        // For now, we'll reset after 24 hours of uptime
        if (millis() > 86400000) {  // 24 hours
            reset();
        }
    }
    
    void reset() {
        dailySteps = 0;
        dailyCalories = 0;
        Serial.println("Activity: Daily stats reset");
    }
    
    // Getters
    int getSteps() { return dailySteps; }
    int getCalories() { return dailyCalories; }
    bool isMoving() { return isMoving; }
    
    // Get distance in meters (assuming 0.75m per step)
    float getDistanceMeters() {
        return dailySteps * 0.75;
    }
    
    // Get distance in kilometers
    float getDistanceKm() {
        return getDistanceMeters() / 1000.0;
    }
    
    // Get JSON representation
    String toJSON() {
        String json = "{";
        json += "\"steps\":" + String(dailySteps) + ",";
        json += "\"calories\":" + String(dailyCalories) + ",";
        json += "\"distance_m\":" + String(getDistanceMeters(), 2) + ",";
        json += "\"distance_km\":" + String(getDistanceKm(), 2) + ",";
        json += "\"is_moving\":" + String(isMoving ? "true" : "false") + ",";
        json += "\"timestamp\":" + String(millis());
        json += "}";
        return json;
    }
    
    // Get current acceleration (for debugging)
    void getAcceleration(int16_t* ax, int16_t* ay, int16_t* az) {
        accel.getAcceleration(ax, ay, az);
        *ax -= accelOffsetX;
        *ay -= accelOffsetY;
        *az -= accelOffsetZ;
    }
    
    // Sleep mode for power saving
    void sleep() {
        accel.setSleepEnabled(true);
    }
    
    void wake() {
        accel.setSleepEnabled(false);
    }
};

#endif
