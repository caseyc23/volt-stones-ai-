#ifndef GPS_TRACKER_H
#define GPS_TRACKER_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>

class GPSTracker {
private:
    HardwareSerial gpsSerial;
    TinyGPSPlus gps;
    
    // GPS data
    double latitude;
    double longitude;
    double altitude;
    float speed;
    int satellites;
    bool valid;
    unsigned long lastUpdate;
    
    // Configuration
    int rxPin;
    int txPin;
    int baudRate;
    
public:
    GPSTracker() : gpsSerial(2), latitude(0), longitude(0), altitude(0), 
                   speed(0), satellites(0), valid(false), lastUpdate(0),
                   rxPin(16), txPin(17), baudRate(9600) {}
    
    bool begin(int rx, int tx, int baud = 9600) {
        rxPin = rx;
        txPin = tx;
        baudRate = baud;
        
        gpsSerial.begin(baudRate, SERIAL_8N1, rxPin, txPin);
        Serial.println("GPS: Initializing...");
        
        // Wait for GPS to start
        delay(1000);
        
        // Check if GPS is responding
        unsigned long start = millis();
        while (millis() - start < 5000) {
            while (gpsSerial.available() > 0) {
                if (gps.encode(gpsSerial.read())) {
                    Serial.println("GPS: Module detected");
                    return true;
                }
            }
            delay(10);
        }
        
        Serial.println("GPS: No response from module");
        return false;
    }
    
    void update() {
        while (gpsSerial.available() > 0) {
            if (gps.encode(gpsSerial.read())) {
                if (gps.location.isUpdated()) {
                    latitude = gps.location.lat();
                    longitude = gps.location.lng();
                    altitude = gps.altitude.meters();
                    speed = gps.speed.kmph();
                    satellites = gps.satellites.value();
                    valid = gps.location.isValid();
                    lastUpdate = millis();
                    
                    if (valid) {
                        Serial.printf("GPS: Lat=%.6f, Lng=%.6f, Sats=%d\n", 
                            latitude, longitude, satellites);
                    }
                }
            }
        }
        
        // Check if data is stale (no update in 60 seconds)
        if (millis() - lastUpdate > 60000) {
            valid = false;
        }
    }
    
    // Getters
    double getLatitude() { return latitude; }
    double getLongitude() { return longitude; }
    double getAltitude() { return altitude; }
    float getSpeed() { return speed; }
    int getSatellites() { return satellites; }
    bool isValid() { return valid; }
    unsigned long getLastUpdate() { return lastUpdate; }
    
    // Power management
    void sleep() {
        // Send GPS to standby mode
        gpsSerial.println("$PMTK161,0*28");
        delay(100);
    }
    
    void wake() {
        // Wake GPS from standby
        gpsSerial.println("$PMTK225,0*2B");
        delay(100);
    }
    
    // Get JSON representation
    String toJSON() {
        String json = "{";
        json += "\"latitude\":" + String(latitude, 6) + ",";
        json += "\"longitude\":" + String(longitude, 6) + ",";
        json += "\"altitude\":" + String(altitude, 2) + ",";
        json += "\"speed\":" + String(speed, 2) + ",";
        json += "\"satellites\":" + String(satellites) + ",";
        json += "\"valid\":" + String(valid ? "true" : "false") + ",";
        json += "\"timestamp\":" + String(lastUpdate);
        json += "}";
        return json;
    }
    
    // Distance calculation (Haversine formula)
    float distanceTo(double lat2, double lon2) {
        const float R = 6371000; // Earth radius in meters
        
        float lat1Rad = latitude * PI / 180.0;
        float lat2Rad = lat2 * PI / 180.0;
        float deltaLat = (lat2 - latitude) * PI / 180.0;
        float deltaLon = (lon2 - longitude) * PI / 180.0;
        
        float a = sin(deltaLat/2) * sin(deltaLat/2) +
                  cos(lat1Rad) * cos(lat2Rad) *
                  sin(deltaLon/2) * sin(deltaLon/2);
        float c = 2 * atan2(sqrt(a), sqrt(1-a));
        
        return R * c;
    }
    
    // Check if within geofence
    bool isWithinGeofence(double centerLat, double centerLon, float radiusMeters) {
        if (!valid) return false;
        return distanceTo(centerLat, centerLon) <= radiusMeters;
    }
};

#endif
