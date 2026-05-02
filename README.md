# Gym-Management-System

Gym Management System (C++ - OOP)
Overview
This is a console-based Gym Management System developed in C++ using Object-Oriented Programming (OOP) concepts.
It provides a simple and secure login system with role-based access for Admin and Member users.

---
🎯 Features

🔐 Authentication System

- User Login with email & password
- Forgot Password functionality
- Email validation (only "@gmail.com" allowed)
- Strong password validation:
  - Minimum 6 characters
  - At least 1 uppercase letter
  - At least 1 digit

---
👤 User Roles
🧑 Member
- Login to system
- View personal information
👨‍💼 Admin
- Login to system
- Access Admin Panel:
  - ➕ Add new members
  - ❌ Remove existing members
  - 📋 View all registered members
---
🧠 OOP Concepts Used
- Encapsulation → Private data with getters/setters
- Inheritance → "Member" and "Admin" inherit from "User"
- Polymorphism → Virtual functions ("login", "displayInfo")
- Abstraction → Base class "User" with pure virtual function "getRole()"
- Dynamic Binding → "dynamic_cast" for Admin panel access
---
🗂️ Project Structure
📁 Gym-Management-System
│
├── Gym loginsystem main.cpp  → Program entry point (menu system)
├── usersystem.h        → Class declarations
├── usersystem.cpp      → Class definitions & logic

📋 How It Works

1. System starts with user registration
2. Users are stored in an array ("User* users[50]")
3. Main menu options:
   - Login
   - Forgot Password
   - Exit
4. After login:
   - Admin → Admin Panel opens
   - Member → Personal info displayed

---
🔒 Security Design

- Admin functionalities are only accessible after login
- Prevents unauthorized access to system controls
- Email duplication is not allowed

---
⚠️ Limitations
- Data is stored in memory only (no file handling)
- Fixed array size (max 50 users)
- Console-based UI
---
👩‍💻 Author
Developed as part of an OOP (C++) academic project.

---
📜 License
This project is for educational purposes only.