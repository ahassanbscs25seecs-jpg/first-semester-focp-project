//#include <iostream>
//
//long int gen_seed(const std::string &rand_str) {
//	std::srand(std::time(nullptr));
//	long int seed = std::rand();
//
//	for (int i = 0; i < rand_str.length(); i++) {
//		seed |= rand_str[i];
//		seed <<= 2;
//		seed *= 3;
//	}
//
//	return seed;
//}
//
//const char SPECIAL[] = "!@#$%^&*?";
//const char UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//const char LOWER[] = "abcdefghijklmnopqrstuvwxyz";
//const char DIGITS[] = "0123456789";
//
//enum class CharClasses : int {
//	SPECIAL = 0,
//	UPPER,
//	LOWER,
//	DIGITS,
//};
//
//int main() {
//	std::string password;
//	int password_len;
//
//	std::string rand_str;
//	unsigned long int seed = 0;
//
//	bool options[4] = {};
//	int n_options = 0;
//
//	std::cout << "Enter a random string of at least 50 characters long" << std::endl;
//
//	do {
//		std::cin >> rand_str;
//
//		if (rand_str.length() < 50) {
//			std::cout << "\nNot long enough\n" << std::endl;
//			rand_str.clear();
//		}
//	} while (rand_str.length() < 50);
//
//	seed = gen_seed(rand_str);
//
//	std::cout << "Enter the password length (8-20)" << std::endl;
//	do {
//		std::cout << "> ";
//		std::cin >> password_len;
//
//		if (password_len < 8 || password_len > 20) {
//			std::cout << "Out of range!" << std::endl;
//		}
//	} while (password_len < 8 || password_len > 20);
//	
//	std::cout << "Enter the number of character types you want to choose (2-4)" << std::endl;
//	do {
//		std::cout << "> ";
//		std::cin >> n_options;
//
//		if (n_options < 2 || n_options > 4) {
//			std::cout << "Out of range";
//		}
//	} while (n_options < 2 || n_options > 4);
//
//	if (n_options == 4) {
//		options[0] = options[1] = options[2] = options[3] = true;
//	} else {
//		int option = 0;
//		std::cout << "1) Digits\n2) Special\n3) Upper\n4) Lower" << std::endl;
//		std::cout << "Enter any " << n_options << " options" << std::endl;
//
//		for (int i = 0; i < n_options; i++) {
//			do {
//				std::cout << "> ";
//				std::cin >> option;
//
//				if (option < 1 || option > 4) {
//					std::cout << "Invalid option" << std::endl;
//				} else if (options[option-1]) {
//					std::cout << "Option already selected.";
//				}
//			} while (option < 1 || option > 4 || options[option-1]);
//			options[option-1] = true;
//		}
//	}
//
//	std::srand(seed);
//
//	for (int i = 0; i < password_len; i++) {
//		CharClasses category = static_cast<CharClasses>(std::rand() % 4);
//		char c = 0;
//
//		switch (category) {
//		case CharClasses::DIGITS:
//			if (options[0])
//				c = DIGITS[std::rand() % (sizeof(DIGITS) - 1)];
//			else
//				i--;
//			break;
//
//		case CharClasses::SPECIAL:
//			if (options[1])
//				c = SPECIAL[std::rand() % (sizeof(SPECIAL) - 1)];
//			else
//				i--;
//			break;
//
//		case CharClasses::UPPER:
//			if (options[2])
//				c = UPPER[std::rand() % 26];
//			else
//				i--;
//			break;
//		
//		case CharClasses::LOWER:
//			if (options[3])
//				c = LOWER[std::rand() % 26];
//			else
//				i--;
//			break;
//		}
//		password.push_back(c);
//	}
//
//	std::cout << "Password: " << password;
//	return 0;
//}
