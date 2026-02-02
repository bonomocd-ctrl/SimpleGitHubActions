// ==========================
// Header files
// ==========================
//Added doctest for debug tests.
#ifdef RUN_TESTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#endif
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h> // For Windows console colors

using namespace std;
//

// ==========================
// CONSTANTS
// ==========================
const int ADVANCED_HOURS = 160;
const int INTERMEDIATE_HOURS = 21;
const int FREQUENT_CLIMBER_DAYS = 80;

const int NEW_CLIMBER_DAYS = 10;
const double DEDICATED_SESSION_HOURS = 2.0;

// ==========================
// ENUM
// ==========================
enum ClimbDifficulty { EASY = 1, MODERATE, HARD, EXTREME };

// ==========================
// COLOR FUNCTION
// ==========================
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ==========================
// BANNER
// ==========================
void displayBanner() {
    setColor(11);
    cout << "=============================================\n";
    cout << "      Welcome to the Rock Climbing Tracker!  \n";
    cout << "  Track your progress and discover your level.\n";
    cout << "=============================================\n\n";
    setColor(15);
}

// ==========================
// INPUT VALIDATION
// ==========================
string getStringInput(string prompt) {
    string input;
    setColor(5);
    cout << prompt;
    getline(cin, input);

    while (input == "") {
        setColor(12);
        cout << "Invalid input. Please try again.\n";
        setColor(5);
        cout << prompt;
        getline(cin, input);
    }
    return input;
}

int getIntInput(string prompt) {
    int value;
    setColor(5);
    cout << prompt;
    cin >> value;
    while (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid. Enter a positive number: ";
        cin >> value;
    }
    cin.ignore();
    return value;
}

double getDoubleInput(string prompt) {
    double value;
    setColor(5);
    cout << prompt;
    cin >> value;
    while (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid. Enter a positive number: ";
        cin >> value;
    }
    cin.ignore();
    return value;
}

// ==========================
// ENUM FUNCTIONS
// ==========================
string difficultyToString(ClimbDifficulty d) {
    switch (d) {
    case EASY: return "Easy";
    case MODERATE: return "Moderate";
    case HARD: return "Hard";
    case EXTREME: return "Extreme";
    }
    return "Unknown";
}

void describeDifficulty(ClimbDifficulty difficulty) {
    setColor(10);
    cout << "\nDifficulty Rating: ";
    switch (difficulty) {
    case EASY:
        cout << "This is a beginner-friendly route. Great for warming up. Keep growing your skillset!\n";
        break;
    case MODERATE:
        cout << "A reasonable challenge. Using good technique is helpful. Climb higher than your fears!\n";
        break;
    case HARD:
        cout << "A tough climb! Keep going one move at a time!\n";
        break;
    case EXTREME:
        cout << "Top-tier difficulty. You are a great climber! Keep climbing on!\n";
        break;
    default:
        cout << "Unknown difficulty.\n";
    }
    setColor(15);
}

ClimbDifficulty getDifficultyFromUser() {
    int choice;
    cout << "\nHow difficult was the climb?\n";
    cout << " 1 = Easy\n 2 = Moderate\n 3 = Hard\n 4 = Extreme\n";
    cout << "Enter choice: ";
    cin >> choice;
    while (choice < 1 || choice > 4) {
        cout << "Invalid (1–4): ";
        cin >> choice;
    }
    cin.ignore();
    return static_cast<ClimbDifficulty>(choice);
}

// ==========================
// REPORT FUNCTIONS
// ==========================
void showReport(string name, string type, string location, int days,
    double hoursPerSession, double totalTime,
    const int grades[], int gradeCount, double avgDifficulty, int highest, int lowest)
{
    setColor(10);
    cout << fixed << setprecision(2);

    cout << "\n=============================================\n";
    cout << "         Rock Climbing Summary Report        \n";
    cout << "=============================================\n";
    cout << left << setw(25) << "Climber Name:" << right << setw(20) << name << endl;
    cout << left << setw(25) << "Climbing Style:" << right << setw(20) << type << endl;
    cout << left << setw(25) << "Location:" << right << setw(20) << location << endl;
    cout << left << setw(25) << "Days per Year:" << right << setw(20) << days << endl;
    cout << left << setw(25) << "Hours per Session:" << right << setw(20) << hoursPerSession << endl;
    cout << left << setw(25) << "Average Annual Hours:" << right << setw(20) << totalTime << endl;

    if (gradeCount > 0) {
        cout << "\n---- Monthly Difficulty Ratings ----\n";
        for (int i = 0; i < gradeCount; i++)
            cout << "Month " << (i + 1) << ": " << grades[i] << endl;

        cout << "Avg Difficulty: " << avgDifficulty
            << " | High: " << highest
            << " | Low: " << lowest << endl;
    }

    cout << "=============================================\n";
    setColor(15);
}

void saveReport(string name, string type, string location, int days,
    double hoursPerSession, double totalTime,
    const int grades[], int gradeCount, double avgDifficulty, int highest, int lowest)
{
    ofstream out("report.txt");
    out << fixed << setprecision(2);

    out << "Rock Climbing Report\n";
    out << "-----------------------\n";
    out << "Climber: " << name << endl;
    out << "Style: " << type << endl;
    out << "Location: " << location << endl;
    out << "Days/year: " << days << endl;
    out << "Hrs/session: " << hoursPerSession << endl;
    out << "Total Hours: " << totalTime << endl;

    if (gradeCount > 0) {
        out << "\nMonthly Difficulty Ratings:\n";
        for (int i = 0; i < gradeCount; i++)
            out << "Month " << (i + 1) << ": " << grades[i] << endl;

        out << "Average: " << avgDifficulty
            << " | High: " << highest
            << " | Low: " << lowest << endl;
    }

    out.close();
}

// ==========================
// LEVEL RECOMMENDATION
// ==========================
void recommendLevel(int days, double hrs, double totalTime, string name)
{
    setColor(11);

    if (days >= FREQUENT_CLIMBER_DAYS && hrs >= DEDICATED_SESSION_HOURS)
        cout << "\nWow, " << name << "! You're extremely dedicated!\n";
    else if (days >= FREQUENT_CLIMBER_DAYS)
        cout << "\nYou climb frequently — great job!\n";
    else if (days < NEW_CLIMBER_DAYS && hrs <= DEDICATED_SESSION_HOURS)
        cout << "\nYou're just starting out — keep going!\n";
    else if (days < NEW_CLIMBER_DAYS)
        cout << "\nNew climber but very dedicated — awesome!\n";
    else
        cout << "\nYou have a healthy, balanced climbing schedule.\n";

    if (totalTime >= ADVANCED_HOURS)
        cout << "You are an ADVANCED climber!\n";
    else if (totalTime >= INTERMEDIATE_HOURS)
        cout << "You are an INTERMEDIATE climber.\n";
    else
        cout << "You are a BEGINNER climber.\n";

    setColor(15);
}

// ==========================
// MONTHLY GRADES
// ==========================
int fillMonthlyGrades(int grades[], int max) {
    int count;
    cout << "\nHow many months (1–" << max << ")? ";
    cin >> count;

    while (count < 1 || count > max) {
        cout << "Invalid (1–" << max << "): ";
        cin >> count;
    }

    for (int i = 0; i < count; i++) {
        int value;
        cout << "Difficulty for month " << (i + 1) << " (1–10): ";
        cin >> value;
        while (value < 1 || value > 10) {
            cout << "Must be 1–10: ";
            cin >> value;
        }
        grades[i] = value;
    }
    cin.ignore();
    return count;
}

void analyzeGrades(const int grades[], int count, double& avg, int& high, int& low) {
    if (count == 0) { avg = 0; high = 0; low = 0; return; }

    int sum = 0;
    high = grades[0];
    low = grades[0];

    for (int i = 0; i < count; i++) {
        sum += grades[i];
        if (grades[i] > high) high = grades[i];
        if (grades[i] < low) low = grades[i];
    }
    avg = static_cast<double>(sum) / count;
}

// ==========================
// MENU
// ==========================
void displayMenu() {
    setColor(14);
    cout << "\n=============================================\n";
    cout << "  1 = View Climbing Report\n";
    cout << "  2 = Recommend Climbing Level\n";
    cout << "  3 = Log Single Climbing Session\n";
    cout << "  4 = Rate Difficulty Only\n";
    cout << "  5 = Enter Monthly Difficulty Grades\n";
    cout << "  6 = Exit Program\n";
    cout << "  7 = Add Session to Weekly Log\n";
    cout << "  8 = View Weekly Log\n";
    cout << "=============================================\n";
    setColor(5);
}

// ==========================
// STRUCT
// ==========================
struct ClimbSession {
    string date;
    double hours;
    ClimbDifficulty difficulty;
};

ClimbSession createClimbSession() {
    ClimbSession s;
    s.date = getStringInput("\nEnter session date (mm/dd/yyyy): ");
    s.hours = getDoubleInput("Enter hours climbed: ");
    s.difficulty = getDifficultyFromUser();
    return s;
}

void printClimbSession(const ClimbSession& s) {
    setColor(11);
    cout << "\n===== Climbing Session =====\n";
    cout << "Date: " << s.date << endl;
    cout << "Hours: " << s.hours << endl;
    cout << "Difficulty: " << difficultyToString(s.difficulty) << endl;
    cout << "============================\n";
    setColor(15);
}

void saveSessionToFile(const ClimbSession& s) {
    ofstream out("session.txt");
    out << "Climbing Session\n";
    out << "Date: " << s.date << endl;
    out << "Hours: " << s.hours << endl;
    out << "Difficulty: " << difficultyToString(s.difficulty) << endl;
    out.close();
}

// ==========================
// CLIMBING TRACKER CLASS
// ==========================
class ClimbingTracker {
private:
    string name;
    string type;
    string location;

    ClimbSession sessions[50];
    int sessionCount;

    int monthlyGrades[12];
    int gradeCount;
    int daysPerYear;
    double hoursPerSession;

public:
    ClimbingTracker() {
        name = type = location = "";
        daysPerYear = 0;
        hoursPerSession = 0.0;
        sessionCount = 0;
        gradeCount = 0;
    }

    // ======= GETTERS =======
    int getDaysPerYear() const { return daysPerYear; }
    double getHoursPerSession() const { return hoursPerSession; }
    int getSessionCount() const { return sessionCount; }
    double getTotalHours() const { return daysPerYear * hoursPerSession; }
    const int* getMonthlyGrades() const { return monthlyGrades; }
    int getGradeCount() const { return gradeCount; }

    // ======= SETTERS =======
    void setDaysPerYear(int days) { daysPerYear = (days >= 0) ? days : 0; }
    void setHoursPerSession(double hours) { hoursPerSession = (hours >= 0.0) ? hours : 0.0; }
    bool addSession(const ClimbSession& s) {
        if (sessionCount >= 50) return false;
        sessions[sessionCount++] = s;
        return true;
    }
    void setMonthlyGrades(const int grades[], int count) {
        gradeCount = count > 12 ? 12 : count;
        for (int i = 0; i < gradeCount; i++)
            monthlyGrades[i] = grades[i];
    }

    // ======= INTERACTIVE METHODS =======
    void initializeProfile() {
        name = getStringInput("What is your full name? ");
        type = getStringInput("\nFavorite style of climbing? ");
        location = getStringInput("\nDo you climb indoors or outdoors? ");
        daysPerYear = getIntInput("\nHow many days do you climb per year? ");
        hoursPerSession = getDoubleInput("\nAverage hours per session? ");
    }

    void addSessionInteractive() {
        if (sessionCount >= 50) {
            cout << "\nSession log full.\n";
            return;
        }
        sessions[sessionCount] = createClimbSession();
        sessionCount++;
        cout << "\nSession added!\n";
    }

    void showSessions() const {
        if (sessionCount == 0) {
            cout << "\nNo sessions logged.\n";
            return;
        }
        cout << "\n====== Weekly Sessions ======\n";
        for (int i = 0; i < sessionCount; i++) {
            cout << "Session " << i + 1 << endl;
            cout << "Date: " << sessions[i].date << endl;
            cout << "Hours: " << sessions[i].hours << endl;
            cout << "Difficulty: " << difficultyToString(sessions[i].difficulty) << endl;
            cout << "-----------------------------\n";
        }
    }

    void enterMonthlyGrades() {
        gradeCount = fillMonthlyGrades(monthlyGrades, 12);
        cout << "\nGrades saved.\n";
    }

    void showReport() const {
        double avg;
        int high, low;
        analyzeGrades(monthlyGrades, gradeCount, avg, high, low);
        ::showReport(name, type, location, daysPerYear, hoursPerSession, getTotalHours(),
            monthlyGrades, gradeCount, avg, high, low);
    }

    void saveReportToFile() const {
        double avg;
        int high, low;
        analyzeGrades(monthlyGrades, gradeCount, avg, high, low);
        ::saveReport(name, type, location, daysPerYear, hoursPerSession, getTotalHours(),
            monthlyGrades, gradeCount, avg, high, low);
    }

    void recommend() const {
        recommendLevel(daysPerYear, hoursPerSession, getTotalHours(), name);
    }

    void runMenu() {
        int choice;
        do {
            displayMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                showReport();
                saveReportToFile();
                break;
            case 2:
                recommend();
                break;
            case 3: {
                ClimbSession s = createClimbSession();
                printClimbSession(s);
                saveSessionToFile(s);
                break;
            }
            case 4:
                describeDifficulty(getDifficultyFromUser());
                break;
            case 5:
                enterMonthlyGrades();
                break;
            case 6:
                cout << "\nGoodbye!\n";
                break;
            case 7:
                addSessionInteractive();
                break;
            case 8:
                showSessions();
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 6);
    }
};


// ==========================
// DOCTEST UNIT TESTS
// ==========================
#ifdef RUN_TESTS

// ==========================
// CALCULATIONS — total hours
// ==========================
TEST_CASE("Calculations: total hours using getters/setters") {
    ClimbingTracker tracker;

    // Normal case
    tracker.setDaysPerYear(50);
    tracker.setHoursPerSession(2.5);
    CHECK(tracker.getTotalHours() == doctest::Approx(125.0));
    CHECK(tracker.getDaysPerYear() == 50);
    CHECK(tracker.getHoursPerSession() == doctest::Approx(2.5));

    // Edge case: 0 days
    tracker.setDaysPerYear(0);
    tracker.setHoursPerSession(5.0);
    CHECK(tracker.getTotalHours() == doctest::Approx(0.0));

    // Edge case: 0 hours per session
    tracker.setDaysPerYear(10);
    tracker.setHoursPerSession(0.0);
    CHECK(tracker.getTotalHours() == doctest::Approx(0.0));

    // Small value
    tracker.setDaysPerYear(1);
    tracker.setHoursPerSession(1.5);
    CHECK(tracker.getTotalHours() == doctest::Approx(1.5));
}

// ==========================
// ENUM DECISION LOGIC
// ==========================
TEST_CASE("Enum decision logic: difficultyToString") {
    CHECK(difficultyToString(EASY) == "Easy");
    CHECK(difficultyToString(MODERATE) == "Moderate");
    CHECK(difficultyToString(HARD) == "Hard");
    CHECK(difficultyToString(EXTREME) == "Extreme");

    // Guard case: invalid enum
    CHECK(difficultyToString(static_cast<ClimbDifficulty>(5)) == "Unknown");
}

// ==========================
// STRUCT / ARRAY PROCESSING
// ==========================
TEST_CASE("Struct/array processing: sessions & grades") {
    ClimbingTracker tracker;

    // Add sessions
    ClimbSession s1 = { "01/01/2026", 2.0, EASY };
    ClimbSession s2 = { "01/02/2026", 3.0, MODERATE };
    CHECK(tracker.addSession(s1) == true);
    CHECK(tracker.addSession(s2) == true);
    CHECK(tracker.getSessionCount() == 2);

    // Edge case: no grades
    double avg;
    int high, low;
    analyzeGrades(tracker.getMonthlyGrades(), tracker.getGradeCount(), avg, high, low);
    CHECK(avg == doctest::Approx(0.0));
    CHECK(high == 0);
    CHECK(low == 0);

    // Normal case: set grades
    int grades[5] = { 3, 5, 7, 2, 10 };
    tracker.setMonthlyGrades(grades, 5);
    analyzeGrades(tracker.getMonthlyGrades(), tracker.getGradeCount(), avg, high, low);
    CHECK(avg == doctest::Approx(5.4));
    CHECK(high == 10);
    CHECK(low == 2);

    // Edge case: exactly 12 grades
    int fullGrades[12] = { 1,2,3,4,5,6,7,8,9,10,1,2 };
    tracker.setMonthlyGrades(fullGrades, 12);
    CHECK(tracker.getGradeCount() == 12);
}

// ==========================
// CLASS METHODS
// ==========================
TEST_CASE("Class methods: addSession & total hours") {
    ClimbingTracker tracker;

    tracker.setDaysPerYear(20);
    tracker.setHoursPerSession(2.0);
    CHECK(tracker.getTotalHours() == doctest::Approx(40.0));

    ClimbSession s = { "01/10/2026", 1.5, HARD };
    CHECK(tracker.addSession(s) == true);
    CHECK(tracker.getSessionCount() == 1);

    // Guard case: exceed session limit
    for (int i = 0; i < 49; i++) tracker.addSession(s);
    CHECK(tracker.getSessionCount() == 50);
    CHECK(tracker.addSession(s) == false); // Should fail when full
}
#else
int main() {
    ClimbingTracker tracker;
    displayBanner();
    tracker.initializeProfile();
    tracker.runMenu();
    return 0;
}
#endif
