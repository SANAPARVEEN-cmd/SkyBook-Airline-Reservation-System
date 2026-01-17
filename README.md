✈️ SkyBook – Airline Reservation Platform (C++)

A production-inspired airline reservation system built using C++, Object-Oriented Programming, Data Structures, and File Persistence.

🚀 Project Overview

SkyBook is a console-based airline reservation platform that simulates the core functionality of a real-world airline booking system.
It is designed with clean OOP architecture, efficient data structures, and persistent storage, making it highly relevant for MAANG/FAANG interviews and resumes.

The system supports flight management, ticket booking, cancellations, and waiting list handling, all while ensuring data consistency across program executions.

🎯 Key Objectives

Demonstrate strong fundamentals of C++

Apply Object-Oriented Design to a real-world problem

Use Data Structures to manage flights, bookings, and waiting lists

Implement file handling for persistent data storage

Build an interview-discussable, resume-worthy project

🧠 Core Concepts Used
✅ Object-Oriented Programming

Classes and objects

Inheritance (User → Admin / Passenger)

Encapsulation and abstraction

Modular and scalable design

✅ Data Structures & Algorithms

vector → store flights and bookings

queue → manage waiting list

Searching and updating algorithms

Seat availability tracking logic

✅ File Handling

Persistent storage using .txt files

Automatic data load on program start

Automatic data save on program exit

✨ Features
👨‍✈️ Admin Features

Add new flights

Remove existing flights

Update flight details

View all available flights

🧍 Passenger Features

View available flights

Book airline tickets

Cancel booked tickets

View booking history

⚙️ System Features

Automatic seat allocation

Waiting list for fully booked flights

Unique booking ID generation

Persistent storage across runs

🗂️ File Structure
SkyBook/
│
├── main.cpp          # Complete application source code
├── flights.txt       # Stores flight data (auto-generated)
├── bookings.txt      # Stores booking records (auto-generated)
└── README.md         # Project documentation
📄 Data Storage Format
flights.txt
FlightNumber Source Destination Date Time TotalSeats AvailableSeats
AI101 NYC LA 2026-01-20 10:00 150 150

bookings.txt
BookingID PassengerName FlightNumber SeatNumber
AI1011 John AI101 1
🧪 Example Use Cases

Admin creates multiple flights for different routes

Passengers browse flights and book tickets

Seat availability updates automatically

Cancellations free seats for new bookings

Waiting list handles full-capacity flights
