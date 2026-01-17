# ✈️ SkyBook – Airline Reservation Platform (C++)

## 📌 Overview

**SkyBook** is a console-based **Airline Reservation System** developed in **C++**, designed to model a real-world airline booking workflow.  
The project emphasizes **Object-Oriented Programming (OOP)**, **Data Structures**, and **File Persistence**, making it suitable for **software engineering interviews and resumes**.

---

## 🎯 Project Goals

- Apply **object-oriented design** to a real-world system
- Use **data structures** for efficient data management
- Implement **persistent storage** using file handling
- Build a project that is **interview-discussable and resume-ready**

---

## 🧠 Technologies & Concepts

### Language
- **C++**

### Core Concepts
- Object-Oriented Programming (OOP)
- Data Structures & Algorithms (DSA)
- File Handling using `fstream`
- Modular and scalable design

---

## 🧩 System Design

### User Roles
- **Admin**
- **Passenger**

### Core Components
- Flight Management
- Booking Management
- Seat Availability Tracking
- Waiting List Handling
- Persistent Data Storage

---

## ✨ Features

### Admin Features
- Add new flights
- Update existing flight details
- Remove flights
- View all available flights

### Passenger Features
- View available flights
- Book airline tickets
- Cancel bookings
- View booking history

### System Features
- Automatic seat allocation
- Waiting list for full flights
- Unique booking ID generation
- Persistent storage across program runs

---

## 🗂️ Project Structure
SkyBook Airline Reservation Platform/
│
├── project.cpp # Application source code
├── flights.txt # Stores flight data (auto-generated)
├── bookings.txt # Stores booking records (auto-generated)

---

## 📄 Data Persistence

### flights.txt
FlightNumber Source Destination Date Time TotalSeats AvailableSeats
AI101 NYC LA 2026-01-20 10:00 150 150


### bookings.txt
BookingID PassengerName FlightNumber SeatNumber
AI1011 John AI101 1

### 🧪 Example Workflow
Admin adds multiple flights
Passenger searches and books tickets
Seat availability updates automatically
Ticket cancellation restores seats
Waiting list manages overflow bookings
