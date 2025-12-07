//#include<iostream>
//#include<cctype>
//#include<string>
//#include<set>
//#include<cmath>
//#include<vector>
//using namespace std;
//
//string getPasswordInput();
//int calculateStrengthScore(const string& password);
//string strengthLabel(int points);
//string giveFeedback(const string& password, int points);
//
//bool hasEasyPattern(const string& password);
//bool hasRepetition(const string& password);
//double calculateEntropy(const string& password);
//
//int main() {
//    cout << "=== PassGuard Strength Checker ===\n";
//    string password = getPasswordInput();
//    int score = calculateStrengthScore(password);
//    string label = strengthLabel(score);
//    string feedback = giveFeedback(password, score);
//    cout << "Strength : " << label << endl;
//    cout << feedback;
//    return 0;
//}
//
//
//string getPasswordInput() {
//    string password;
//    cout << "Enter your password(spaces allowed): ";
//    getline(cin, password);     // accept spaces
//    
//    // If empty password is entered
//    while (password.size() == 0) {
//        cout << "Password cannot be empty. Enter Again: ";
//        getline(cin, password);
//    }
//    return password;
//}
//
//int calculateStrengthScore(const string& password) {
//    int points = 0;
//    set<char> uniqueChars;
//    int len = password.length();
//    double entropy = calculateEntropy(password);
//    
//    // Entropy points 
//    if (entropy <= 20)
//        points += 5;
//    else if (entropy <= 40)
//        points += 15;
//    else if (entropy <= 60)
//        points += 25;
//    else if (entropy <= 75)
//        points += 40;
//    else
//        points += 50;
//
//    // Character and Length points 
//    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
//    for (char ch : password) {
//        unsigned char uch = static_cast<unsigned char>(ch);
//        uniqueChars.insert(uch);
//
//        if (isupper(uch))  hasUpper = true;
//        else if (islower(uch))  hasLower = true;
//        else if (isdigit(uch))  hasDigit = true;
//        else if (ispunct(uch))  hasSpecial = true;
//    }
//    if (hasUpper) points += 5;
//    if (hasLower) points += 5;
//    if (hasDigit) points += 5;
//    if (hasSpecial) points += 10;
//
//    if (len >= 12) points += 10;
//    else if (len >= 10) points += 8;
//
//
//    //UNique char bonus
//    int unique_count = uniqueChars.size();
//    if (unique_count <= 4)
//        points += 0;
//    else if (unique_count <= 7)
//        points += 5;
//    else if (unique_count <= 10)
//        points += 12;
//    else if (unique_count <= 15)
//        points += 15;
//    else
//        points += 30;
//
//    //pattern penalty
//    if (hasEasyPattern(password)) points -= 10;
//
//    //Repeated char penality
//    if (hasRepetition(password)) points -= 10;
//
//
//    if (points > 100) points = 100;
//    if (points < 0) points = 0;
//
//    return points;
//}
//
//string strengthLabel(int points) {
//    string label = "";
//    if (points < 30)
//        return "Weak";
//    else if (points < 60)
//        return "Medium";
//    else if (points < 80)
//        return "Strong";
//    else
//        return "Very Strong";
//    return label;
//}
//
//string giveFeedback(const string& password, int points) {
//    int len = password.length();
//    int uppercount = 0, lowercount = 0, digitcount = 0, specialcount = 0;
//    set<char>uniqueChars;
//    double entropy = calculateEntropy(password);
//
//    for (char ch : password) {
//        unsigned char uch = static_cast<unsigned char>(ch);
//        uniqueChars.insert(uch);
//
//        if (isupper(uch))
//            uppercount++;
//        else if (islower(uch))
//            lowercount++;
//        else if (isdigit(uch))
//            digitcount++;
//        else if (ispunct(uch))
//            specialcount++;
//    }
//
//    vector<string> suggestions;
//
//    if (len < 8)
//        suggestions.push_back("Use atleast 8 characters.");
//    
//    if (specialcount == 0)
//        suggestions.push_back("Add special characters(e.g. !@#$%^&*).");
//    
//    if (digitcount == 0)
//        suggestions.push_back("Add digits(0-9).");
//    
//    if (uppercount == 0)
//        suggestions.push_back("Add Uppercase letters(A-Z).");
//    
//    if (lowercount == 0)
//        suggestions.push_back("Add lowercase letters(a-z).");
//
//    if (uniqueChars.size() < 6)
//        suggestions.push_back("Increase variety of characters to avoid predictability.");
//    
//    if (hasRepetition(password))
//        suggestions.push_back("Avoid repeating the same characters 3 or more times.");
//    
//    if (hasEasyPattern(password))
//        suggestions.push_back("Avoid common patterns like '1234' or 'abcd' or 'qwerty'. ");
//    
//    if (points >= 80) {
//        if (suggestions.empty()) return "Excellent! Your password is highly secure.";
//        else {
//            string out = "Great password! Just a few minor improvements: \n";
//            for (string& s : suggestions) out += "- " + s + "\n";
//            return out;
//        }
//    }
//    if (!suggestions.empty()) {
//        string output = "";
//        for (string& s : suggestions) output += s + "\n";
//        return output;
//    }
//
//    if (entropy < 28)
//        return "Extremely predictable. Add length and variety of characters.";
//    else if (entropy < 36)
//        return "Increase randomness and avoid predictable sequences.";
//    else if (entropy < 45)
//        return "Add more unique characters or unrelated words.";
//    else if (entropy < 60)
//        return "Consider increasing length or adding symbols for extra security.";
//    else if (entropy < 75)
//        return "Good entropy, but more randomness improves security.";
//    else
//        return "Highly resistant to brute-force attacks.";
//}
//
//bool hasEasyPattern(const string& password) {
//    string lower = password;
//
//    for (char& c : lower)
//        c = tolower(c);
//    
//    return lower.find("1234") != string::npos ||
//           lower.find("abcd") != string::npos ||
//           lower.find("qwerty") != string::npos ||
//           lower.find("password") != string::npos ||
//           lower.find("admin") != string::npos ||
//           lower.find("1122") != string::npos ||
//           lower.find("asdf") != string::npos ||
//           lower.find("zxcv") != string::npos;
//
//    return false;
//}
//bool hasRepetition(const string& password) {
//    for (int i = 0; i < password.size() - 2; i++) {
//        if (password[i] == password[i + 1] && password[i] == password[i + 2]) {
//            return true;
//        }
//    }
//    return false;
//}
//
//double calculateEntropy(const string& password) {
//    double entropy = 0.00;
//    int characterSetSize = 0;
//    int len = password.length();
//    set<char>uniqueChars;
//    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
//    
//    for (char ch : password) {
//        unsigned char uch = static_cast<unsigned char>(ch);
//        uniqueChars.insert(uch);
//
//        if (isupper(uch))
//            hasUpper = true;
//        else if (islower(uch))
//            hasLower = true;
//        else if (isdigit(uch))
//            hasDigit = true;
//        else if (ispunct(uch))
//            hasSpecial = true;
//    }
//
//    if (hasUpper)
//        characterSetSize += 26;
//    
//    if (hasLower)
//        characterSetSize += 26;
//    
//    if (hasDigit)
//        characterSetSize += 10;
//    
//    if (hasSpecial)
//        characterSetSize += 32;
//
//
//    if (characterSetSize == 0)
//        entropy = 0;
//    else
//        entropy = len * log2(characterSetSize);
//
//    return entropy;
//}