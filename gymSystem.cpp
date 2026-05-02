#include "gymSystem.h"
#include <iostream>
#include <string>
using namespace std;

AttendanceLog::AttendanceLog()
    : memberID(0), feePaid(false), visits(0) {
}

void AttendanceLog::input() {
    cout << "Enter Member ID: "; 
    cin >> memberID;
    cout << "Fee Paid? (1=Yes / 0=No): "; 
    cin >> feePaid;
    cin.ignore();
    cout << "Date (e.g. 2026-05-01): "; 
    getline(cin, date);
    cout << "Check-in time: ";           
    getline(cin, inTime);
    cout << "Check-out time: ";          
    getline(cin, outTime);
    if (feePaid) visits++;
}

bool AttendanceLog::access() {
    if (!feePaid) {
        cout << "Access Denied – payment required.\n";
        return false;
    }
    cout << "Access Granted.\n";
    return true;
}

void AttendanceLog::display() {
    cout << "---- Attendance ----\n";
    cout << "ID     : " << memberID << "\n";
    cout << "Date   : " << date << "\n";
    cout << "In     : " << inTime << "\n";
    cout << "Out    : " << outTime << "\n";
    cout << "Visits : " << visits << "\n";
}

int AttendanceLog::getDays() { return visits; }

AttendanceLog::~AttendanceLog() {}

ProgressAnalytics::ProgressAnalytics()
    : weight(0), target(0), height(0) {
    history = new float[3] {0.0f, 0.0f, 0.0f};
}

ProgressAnalytics::ProgressAnalytics(const ProgressAnalytics& other)
    : weight(other.weight), target(other.target), height(other.height) {
    history = new float[3];
    for (int i = 0; i < 3; i++) history[i] = other.history[i];
}

ProgressAnalytics& ProgressAnalytics::operator=(const ProgressAnalytics& other) {
    if (this != &other) {
        weight = other.weight;
        target = other.target;
        height = other.height;
        delete[] history;
        history = new float[3];
        for (int i = 0; i < 3; i++) history[i] = other.history[i];
    }
    return *this;
}

ProgressAnalytics::~ProgressAnalytics() {
    delete[] history;
    history = nullptr;
}

void ProgressAnalytics::input() {
    cout << "--- Progress Report Input ---\n";
    cout << "Current weight (kg): "; cin >> weight;
    cout << "Target  weight (kg): "; cin >> target;
    cout << "Height (cm or m)   : "; cin >> height;
    cout << "Last 3 months weight history:\n";
    for (int i = 0; i < 3; i++) {
        cout << "  Month " << (i + 1) << ": "; cin >> history[i];
    }
}

float ProgressAnalytics::bmi() {
    if (height <= 0) { cout << "[Error] Height must be > 0.\n"; return 0; }
    float hInMeters = (height > 3.0f) ? height / 100.0f : height;
    return weight / (hInMeters * hInMeters);
}

const char* ProgressAnalytics::category() {
    float b = bmi();
    if (b < 18.5f) return "Underweight";
    if (b < 25.0f) return "Normal";
    if (b < 30.0f) return "Overweight";
    return "Obese";
}

float ProgressAnalytics::change() { return history[2] - history[0]; }
float ProgressAnalytics::average() { return (history[0] + history[1] + history[2]) / 3.0f; }

void ProgressAnalytics::report() {
    cout << "\n---- Fitness Report ----\n";
    cout << "BMI      : " << bmi() << "\n";
    cout << "Category : " << category() << "\n";
    cout << "3-month change  : " << change() << " kg\n";
    cout << "3-month average : " << average() << " kg\n";
    cout << "Goal    : " << target << " kg  (current: " << weight << " kg)\n";
    float diff = weight - target;
    if (diff > 0)       cout << "Still " << diff << " kg to lose.\n";
    else if (diff < 0)  cout << "You are " << -diff << " kg below your target!\n";
    else                cout << "Target reached!\n";
}

float ProgressAnalytics::consistency(int d) {
    return (static_cast<float>(d) / 30.0f) * 100.0f;
}
