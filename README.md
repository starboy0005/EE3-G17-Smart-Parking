# Group 17 Electrical 3
## Smart Parking System with Arduino using Ultrasonic Sensors

This project is an Arduino-based Parking Management System that detects vehicle occupancy using ultrasonic sensors, tracks parking fees, and displays available slots on an I2C LCD display. The system logs entry and exit events via the Serial Monitor, assigns ticket numbers, and charges fees at a simulated rate.

## Features
1. **Real-time Slot Detection:** Uses ultrasonic sensors to detect if a parking slot is occupied.
2. **LCD Display:** Shows available parking slots and updates dynamically.
3. **Fee Calculation:** Charges a fee every 5 seconds for occupied slots.
4. **Serial Monitoring:** Logs vehicle entry, exit, ticket numbers, and total fee upon exit.
5. **Random Ticket Assignment:** Assigns a unique simulated number plate to each parked vehicle.

## Components Used
- Arduino Uno Board  
- Ultrasonic Sensors (HC-SR04) - 4 units  
- I2C LCD Display (16x2)  
- Jumper Wires  
- Power Supply  

## Wiring
Each parking slot is assigned a respective ultrasonic sensor.  
The trigger and echo pins of the ultrasonic sensors are connected to digital pins.  
The LCD is connected via I2C to its corresponding Arduino Uno pins (using the `Adafruit_LiquidCrystal` library).  

| Slot  | Trigger Pin | Echo Pin |
|-------|------------|----------|
| P1    | 3          | 2        |
| P2    | 5          | 4        |
| P3    | 7          | 6        |
| P4    | 9          | 8        |

## Code Overview
1. **Initialize LCD & Sensors:** The system sets up I2C communication, serial monitoring, and configures ultrasonic sensor pins.
2. **Distance Measurement:** The `getDistance()` function calculates the distance to determine if a slot is occupied.
3. **Slot Detection & Fee Calculation:**  
   - If a slot is empty, it resets the fee and logs the exit.  
   - If a slot is occupied, it assigns a ticket and charges a fee every 5 seconds.  
4. **LCD Display Update:**  
   - Shows the count of available slots for 1 second.  
   - Displays free slot numbers for another 1 second.  
   - Loops continuously.  

## Simulation Circuit
![Simulation Circuit](Circuit_image_Tinkercad.jpg)

**Simulation link:** [Tinkercad Project](https://www.tinkercad.com/things/1AGQpEJ5IEI-bodacious-rottis)  

## Serial Monitor Output Example
```
Car Entered | Slot: P2  
Charging P2 | Ticket: NP4567 | Fee: $0.10  
Charging P2 | Ticket: NP4567 | Fee: $0.20  
Car Exited  | Ticket: NP4567 | Total Fee: $0.40  
```

## LCD Output Examples
*(Add images here once available.)*  

## Dependencies
Ensure you have the `Adafruit_LiquidCrystal` library installed for LCD I2C communication.

