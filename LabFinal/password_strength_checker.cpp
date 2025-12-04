#include <iostream>
#include <cctype>
#include <string>
#include <set>

using namespace std;

string getPasswordInput();
int calculateStrengthScore(const string& password);
string strengthLabel(int points);
string giveFeedback(const string& password, int points);

bool hasEasyPattern(const string& password);
bool hasRepetition(const string& password);

int main() {
    string password;
    bool is_valid;
    int score;
    string strength_label;
    string feedback;

    cout << "=== PassGuard Strength Checker ===" << endl;
    
    password = getPasswordInput();

    score = calculateStrengthScore(password);
    strength_label = strengthLabel(score);
    feedback = giveFeedback(password, score);

    cout << "Strength: " << strength_label << endl;
    cout << feedback;

    return 0;
}

string getPasswordInput() {
    string password;

    do {
        cout << "Enter your password (spaces allowed): ";
        getline(cin, password); // Accept spaces
    
        if (password.length() == 0) {
            cout << "Password cannot be empty. Enter Again: ";
        }
    } while (password.length() == 0);
    
    return password;
}

int calculateStrengthScore(const string& password) {
    int points = 0;
    set<char> uniqueChars;
    int repeatPenalty = 0;
    int len=password.length();

    //Length points
    if (len >= 8 && len <= 11) {
        points += 10;
    } else if (len >= 12 && len <= 15) {
        points += 20;
    } else if (len >= 16 && len <= 20) {
        points += 30;
    }

    int uppercount = 0, lowercount = 0, digitcount = 0, specialcount = 0;
    for (char ch : password) {
        unsigned char uch = static_cast<unsigned char>(ch);
        uniqueChars.insert(uch);

        if (isupper(uch)) {
            uppercount++;
        } else if (islower(uch)) {
            lowercount++;
        } else if (isdigit(uch)) {
            digitcount++;
        } else if (ispunct(uch)) {
            specialcount++;
        }
    }

    // +2 per extra upper, lower, digit and +3 per extra character
    points += (uppercount - 1) * 2 +
              (lowercount - 1) * 2 +
              (digitcount - 1) * 2 +
              (specialcount - 1) * 3;

    // Unique char bonus
    points += min((int)uniqueChars.size(), 20); // Max 20

    // Repeated char penality
    for (int i = 0; i < password.size(); ++i) {
        for (int j = i + 1; j < password.size(); ++j) {
            if (password[i] == password[j]) {
                repeatPenalty++;
            }
        }
    }
    points -= repeatPenalty;

    if (points > 100) {
        points = 100;
    }
    
    if (points < 0) {
        points = 0;
    }

    return points;
}

string strengthLabel(int points) {
    string label = "";
    
    if (points < 30) {
        label = "Weak";
    } else if (points < 60) {
        label = "Medium";
    } else if (points < 80) {
        label = "Strong";
    } else {
        label = "Very Strong";
    }

    return label;
}

string giveFeedback(const string& password, int points) {
    int len = password.length();
    int uppercount = 0, lowercount = 0, digitcount = 0, specialcount = 0;
    set<char> uniqueChars;
    
    for (char ch : password) {
        unsigned char uch = static_cast<unsigned char>(ch);
        uniqueChars.insert(uch);

        if (isupper(uch))
            uppercount++;
        else if (islower(uch))
            lowercount++;
        else if (isdigit(uch))
            digitcount++;
        else if (ispunct(uch))
            specialcount++;
    }

    string result = "";
    int suggestions = 0;

    if (points >= 80) {
        return "Excellent! Your password is highly secure and meets all recommended standards.";
    }

    if (len < 12 && suggestions < 2) {
        result += "Increasing password length can improve strength.\n";
        suggestions++;
    }
    
    if (hasRepetition(password) && suggestions < 2) {
        result += "Your password contains repeated characters. Reducing repetition can improve it's strength.\n";
        suggestions++;
    }
    
    if (hasEasyPattern(password) && suggestions < 2) {
        result += "Your password includes common patterns. Removing predictable sequences can help strengthen it.\n";
        suggestions++;
    }
    
    if (specialcount <= 1 && suggestions < 2) {
        result += "Consider adding more special characters.\n";
        suggestions++;
    }
    
    if (digitcount <= 1 && suggestions < 2) {
        result += "Consider adding more digits.\n";
        suggestions++;
    }

    if (result.size() == 0) return result;

    return result;
}

bool hasEasyPattern(const string& password) {
    string lower = password;

    for (char& c : lower)
        c = tolower(c);

    return lower.find("1234") != string::npos || 
           lower.find("abcd") != string::npos || 
           lower.find("qwerty") != string::npos || 
           lower.find("password") != string::npos || 
           lower.find("admin") != string::npos || 
           lower.find("1122") != string::npos || 
           lower.find("asdf") != string::npos || 
           lower.find("zxcv") != string::npos;
}

bool hasRepetition(const string& password) {
    for (int i = 0; i < password.size() - 2; i++) {
        if (password[i] == password[i + 1] && password[i] == password[i + 2]) {
            return true;
        }
    }

    return false;
}
