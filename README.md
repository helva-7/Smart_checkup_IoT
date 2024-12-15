# Smart Attendance System

## Overview
The Smart Attendance System is an automated access and attendance tracking solution. It integrates hardware components with a robust algorithm to ensure secure and accurate management of user access and attendance records.

## Components

### Sensors:
- **RFID Reader**: Used to scan user cards.
- **Keyboard**: Allows users to input their PIN code.

### Actuators:
- **LCD Display**: Displays messages to the user, such as status updates or error notifications.
- **Servomotor**: Simulates a door lock mechanism.

## How It Works
1. **Database Setup**: A database stores a list of authorized IDs along with their corresponding PIN codes.
2. **User Authentication**:
   - The user scans their RFID card.
   - The system prompts the user to enter their PIN code.
   - The system checks the ID and PIN against the database.
3. **Access Control**:
   - If the user is authorized:
     - The door unlocks (via the servomotor).
     - The system logs the time of entry.
   - If the user is not authorized:
     - The LCD displays an error message.
4. **Manual Override**:
   - The dashboard allows manual control of the door, enabling it to be opened without RFID and PIN verification.

## Dashboard Features
- **User Entry Logs**: Displays a list of user entries with timestamps.
- **User Management**: Allows administrators to configure new IDs and PINs.
- **Manual Door Control**: Provides an option to open the door manually from the dashboard.

## System Workflow
1. User scans their RFID card.
2. User enters their PIN on the keypad.
3. The system verifies the credentials:
   - **Authorized**: Unlocks the door and logs the entry.
   - **Unauthorized**: Displays an error message on the LCD.
4. Administrator accesses the dashboard to review logs or configure new users.

## Benefits
- Enhanced security with dual-factor authentication (RFID + PIN).
- Accurate attendance tracking with timestamped logs.
- User-friendly dashboard for efficient management and monitoring.
- Flexibility with manual override functionality.
