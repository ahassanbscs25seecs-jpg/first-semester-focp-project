//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <ctime>
//#include <string>
//
//const long long IGNORE_SIZE = std::numeric_limits<std::streamsize>::max();
//
//const char SPECIAL[] = "!@#$%^&*?";
//const char UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//const char LOWER[] = "abcdefghijklmnopqrstuvwxyz";
//const char DIGITS[] = "0123456789";
//
//enum class CharClasses : int {
//    DIGITS = 0,
//    SPECIAL,
//    UPPER,
//    LOWER
//};
//
//long int genSeed(const std::string& rand_str) {
//    std::srand(std::time(nullptr));
//    long int seed = std::rand();
//
//    for (size_t i = 0; i < rand_str.length(); i++) {
//        seed |= rand_str[i];
//        seed <<= 2;
//        seed *= 3;
//    }
//    return seed;
//}
//
//int main() {
//    std::string password;
//    int password_len;
//
//    std::string rand_str;
//    unsigned long int seed = 0;
//
//    bool options[4] = {};
//    int n_options = 0;
//
//    // --- Random string input ---
//    std::cout << "Enter a random string of at least 50 characters long" << std::endl;
//    do {
//        std::getline(std::cin, rand_str);
//
//        if (rand_str.length() < 50) {
//            std::cout << "\nNot long enough\n" << std::endl;
//            rand_str.clear();
//        }
//    } while (rand_str.length() < 50);
//
//    seed = genSeed(rand_str);
//
//    // --- Password length input ---
//    std::cout << "Enter the password length (8-20)" << std::endl;
//    do {
//        std::cout << "> ";
//        std::cin >> password_len;
//        std::cin.ignore(IGNORE_SIZE, '\n');
//
//        if (password_len < 8 || password_len > 20) {
//            std::cout << "Out of range!" << std::endl;
//        }
//    } while (password_len < 8 || password_len > 20);
//
//    // --- Character options ---
//    std::cout << "Enter the number of character types you want to choose (2-4)" << std::endl;
//    do {
//        std::cout << "> ";
//        std::cin >> n_options;
//
//        if (n_options < 2 || n_options > 4) {
//            std::cout << "Out of range";
//        }
//    } while (n_options < 2 || n_options > 4);
//
//    if (n_options == 4) {
//        options[0] = options[1] = options[2] = options[3] = true;
//    }
//    else {
//        int option = 0;
//        std::cout << "1) Digits\n2) Special\n3) Upper\n4) Lower" << std::endl;
//        std::cout << "Enter any " << n_options << " options" << std::endl;
//
//        for (int i = 0; i < n_options; i++) {
//            do {
//                std::cout << "> ";
//                std::cin >> option;
//
//                if (option < 1 || option > 4) {
//                    std::cout << "Invalid option" << std::endl;
//                }
//                else if (options[option - 1]) {
//                    std::cout << "Option already selected.";
//                }
//            } while (option < 1 || option > 4 || options[option - 1]);
//
//            options[option - 1] = true;
//        }
//    }
//
//    //// --- Prepare random generator ---
//    //std::srand(seed);
//
//    //// ============================================================
//    ////    Build allowed character sets + guarantee each type
//    //// ============================================================
//    //std::vector<const char*> allowed_sets;
//    //std::vector<int> allowed_sizes;
//
//    //if (options[0]) {
//    //    allowed_sets.push_back(DIGITS);
//    //    allowed_sizes.push_back(sizeof(DIGITS) - 1);
//    //}
//    //
//    //if (options[1]) {
//    //    allowed_sets.push_back(SPECIAL);
//    //    allowed_sizes.push_back(sizeof(SPECIAL) - 1);
//    //}
//    //
//    //if (options[2]) {
//    //    allowed_sets.push_back(UPPER);
//    //    allowed_sizes.push_back(26);
//    //}
//    //
//    //if (options[3]) {
//    //    allowed_sets.push_back(LOWER);
//    //    allowed_sizes.push_back(26);
//    //}
//
//    //// First: ensure at least one from each selected type
//    //for (size_t i = 0; i < allowed_sets.size(); i++) {
//    //    const char* set = allowed_sets[i];
//    //    int size = allowed_sizes[i];
//    //    password.push_back(set[std::rand() % size]);
//    //}
//
//    //// Fill the rest randomly
//    //while ((int)password.length() < password_len) {
//    //    int index = std::rand() % allowed_sets.size();
//    //    const char* set = allowed_sets[index];
//    //    int size = allowed_sizes[index];
//
//    //    password.push_back(set[std::rand() % size]);
//    //}
//
//    //// Shuffle so required characters aren't all at the start
//    //std::random_shuffle(password.begin(), password.end());
//
//    //// Final output
//    //std::cout << "Password: " << password << std::endl;
//
//    return 0;
//}