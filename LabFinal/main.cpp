#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits>
#include <set>
#include <algorithm>

const int MAX_PASSWORD_LEN = 20;
const long long IGNORE_SIZE = std::numeric_limits<std::streamsize>::max();

struct TableEntry {
	int id = 0;
	std::string username;
	std::string siteURL;
	std::string password;
};

enum class CharClasses : int {
	SPECIAL = 0,
	UPPER,
	LOWER,
	DIGITS,
};

const char SPECIAL[] = "!@#$%^&*?";
const char UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char LOWER[] = "abcdefghijklmnopqrstuvwxyz";
const char DIGITS[] = "0123456789";

/**
 * clearScreen:
 *   Clears the screen.
 * 
 * '\033[H' moves the terminal cursor to (0, 0)
 * '\033[2H' clears the entire entire terminal, regardless of cursor position.
 */
void clearScreen();

/**
 * printTitle:
 *   prints the title of the program
 */
void printTitle();


/**
 * genSeed:
 *   Generate a random number from randStr
 * 
 * Arguments:
 *   -> randStr: a string of random characters.
 * 
 * Return value:
 *   A random number which will be used as the seed for srand.
 */
long int genSeed(const std::string& randStr);

/**
 * readCSVFile:
 *   Reads a CSV file and processes it into a computer-friendly format
 *
 * Arguments:
 *   -> filename: Name of the CSV file we want to read from
 *
 * Return value:
 *   Returns the CSV file as a list of table entries
 */
std::vector<TableEntry> readCSVFile(const std::string& filename);

/**
 * writeCSVFile:
 *   Writes the contents of `table` into `filename` in CSV format
 *
 * Arguments:
 *   -> filename: The name of the CSV file we want to write to.
 *   -> table: The table that we want to store in CSV format.
 *
 * Return value:
 *   Returns nothing.
 */
void writeCSVFile(const std::string& filename, const std::vector<TableEntry>& table);

/**
 *
 */
std::vector<TableEntry> searchByUsername(const std::vector<TableEntry>& table, const std::string& username);

/**
 *
 */
std::vector<TableEntry> searchBySiteURL(const std::vector<TableEntry>& table, const std::string& siteURL);

/**
 * printTable:
 *   Print the password table to the terminal in an easy to read manner.
 *
 * Arguements:
 *   -> table: The table we want to print to the terminal.
 *
 * Return value:
 *   Returns nothing.
 */
void printTable(const std::vector<TableEntry>& table);

bool isSiteURLValid(const std::string& siteURL);

int calculateStrengthScore(const std::string& password);

std::string strengthLabel(int points);

std::string getPasswordInput();

void searchForPasswords(const std::string& filename);

void addNewPassword(std::string filename);

int main() {
	printTitle();

	int option = 0;
	bool done = false;

	std::string passFilename;

	std::cout << "Enter the password filename: ";
	std::cin >> passFilename;
	passFilename += ".csv";

	while (true) {
		clearScreen();
		printTitle();

		std::cout << "Enter an action\n"
				  << "1) Enter a new password\n"
				  << "2) Search for passwords\n"
				  << "3) Quit" << std::endl;

		do {
			std::cout << "> ";
			std::cin >> option;
			std::cin.ignore(IGNORE_SIZE, '\n');

			switch (option) {
			case 1:
				done = true;
				addNewPassword(passFilename);
				break;

			case 2:
				done = true;
				searchForPasswords(passFilename);
				break;
			
			case 3:
				return 0;

			default:
				std::cout << "Invalid option!" << std::endl;
				break;
			}
		} while (!done);
	}

	return 0;
}

void clearScreen() {
	std::cout << "\033[H\033[2J";
}

void printTitle() {
	std::cout << "PassGen\n"
		<< "-------\n" << std::endl;
}

long int genSeed(const std::string& randStr) {
	std::srand(std::time(nullptr));
	long int seed = std::rand();

	for (int i = 0; i < randStr.length(); i++) {
		seed |= randStr[i];
		seed <<= 2;
		seed *= 3;
	}

	return seed;
}

std::vector<TableEntry> readCSVFile(const std::string& filename) {
	std::fstream f(filename);
	std::string line;
	std::string temp;
	std::vector<TableEntry> table;

	/* Read the file line by line. Each line will be a record. */
	while (std::getline(f, line)) {
		/* Take the line and further divide it at the commas
		 * which will let us extract each individual entry.
		 */

		size_t a = line.find(',');
		size_t b = line.find(',', a + 1);
		size_t c = line.find(',', b + 1);

		table.push_back(TableEntry{
			std::stoi(line.substr(0, a)),  /* ID */
			line.substr(a + 1, b - a - 1), /* Username */
			line.substr(b + 1, c - b - 1), /* Site URL */
			line.substr(c + 1)             /* Password */
		});
	}

	return table;
}

void writeCSVFile(const std::string& filename, const std::vector<TableEntry>& table) {
	std::ofstream f(filename);

	for (auto& e : table) {
		f << e.id << ','
			<< e.username << ','
			<< e.siteURL << ','
			<< e.password << std::endl;
	}
}

std::vector<TableEntry> searchByUsername(const std::vector<TableEntry>& table, const std::string& username) {
	std::vector<TableEntry> result;

	for (auto& e : table) {
		if (username == e.username) {
			result.push_back(e);
		}
	}

	return result;
}

std::vector<TableEntry> searchBySiteURL(const std::vector<TableEntry>& table, const std::string& siteURL) {
	std::vector<TableEntry> result;

	for (auto& e : table) {
		if (siteURL == e.siteURL) {
			result.push_back(e);
		}
	}

	return result;
}

void printTable(const std::vector<TableEntry>& table) {
	std::cout << std::left
		<< std::setw(8) << "ID"
		<< std::setw(15) << "Username"
		<< std::setw(25) << "Site URL"
		<< std::setw(20) << "Password"
		<< "\n-------------------------------------------------------------" << std::endl;

	for (const auto& e : table) {
		std::cout << std::left
			<< std::setw(8) << e.id
			<< std::setw(15) << e.username
			<< std::setw(25) << e.siteURL
			<< std::setw(20) << e.password
			<< std::endl;
	}
}

bool isSiteURLValid(const std::string& siteURL) {
	for (auto& c : siteURL) {
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
			return false;
		}
	}
	return true;
}

int calculateStrengthScore(const std::string& password) {
	int points = 0;
	std::set<char> uniqueChars;
	int repeatPenalty = 0;
	int len = password.length();

	// Length points
	if (len >= 8 && len <= 11) {
		points += 10;
	}
	else if (len >= 12 && len <= 15) {
		points += 20;
	}
	else if (len >= 16 && len <= 20) {
		points += 30;
	}

	int uppercount = 0, lowercount = 0, digitcount = 0, specialcount = 0;
	for (char ch : password) {
		unsigned char uch = static_cast<unsigned char>(ch);
		uniqueChars.insert(uch);

		if (isupper(uch)) {
			uppercount++;
		}
		else if (islower(uch)) {
			lowercount++;
		}
		else if (isdigit(uch)) {
			digitcount++;
		}
		else if (ispunct(uch)) {
			specialcount++;
		}
	}

	// +2 per extra upper, lower, digit and +3 per extra character
	points += (uppercount - 1) * 2 +
		(lowercount - 1) * 2 +
		(digitcount - 1) * 2 +
		(specialcount - 1) * 3;

	// Unique char bonus
	points += std::min((int)uniqueChars.size(), 20); // Max 20

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

std::string strengthLabel(int points) {
	std::string label = "";

	if (points < 30) {
		label = "Weak";
	}
	else if (points < 60) {
		label = "Medium";
	}
	else if (points < 80) {
		label = "Strong";
	}
	else {
		label = "Very Strong";
	}

	return label;
}

std::string getPasswordInput() {
	std::string password;

	std::cout << "Enter your password (spaces allowed): ";

	do {
		std::cout << "> ";
		std::getline(std::cin, password); // Accept spaces

		if (password.length() == 0) {
			std::cout << "Password cannot be empty!" << std::endl;
		}
	} while (password.length() == 0);

	return password;
}

void searchForPasswords(const std::string& filename) {
	clearScreen();
	printTitle();

	std::vector<TableEntry> table = readCSVFile(filename);
	std::vector<TableEntry> searchResults;
	int option = 0;

	std::cout << "What do you want to search with?\n"
		<< "1) Username\n"
		<< "2) Site URL" << std::endl;

	do {
		std::cout << "> ";
		std::cin >> option;
		std::cin.ignore(IGNORE_SIZE, '\n');

		if (option != 1 && option != 2) {
			std::cout << "Wrong option!" << std::endl;
		}
	} while (option != 1 && option != 2);

	switch (option) {
	case 1: {
		std::string username;

		std::cout << "\nEnter the username" << std::endl;
		do {
			std::cout << "> ";
			std::getline(std::cin, username);

			if (username.length() == 0) {
				std::cout << "Username can't be empty!" << std::endl;
			}
		} while (username.length() == 0);

		searchResults = searchByUsername(table, username);
		break;
	}

	case 2: {
		std::string siteURL;

		std::cout << "Enter the site URL" << std::endl;
		do {
			std::cout << "> ";
			std::getline(std::cin, siteURL);

			if (siteURL.length() == 0) {
				std::cout << "Site URL can't be empty!" << std::endl;
			}
			else if (!isSiteURLValid(siteURL)) {
				std::cout << "Site URL can't contain whitespace!" << std::endl;
			}
		} while (siteURL.length() == 0 || !isSiteURLValid(siteURL));

		searchResults = searchBySiteURL(table, siteURL);

		break;
	}
	}

	std::cout << std::endl;
	printTable(searchResults);

	std::cout << "\nPress any key to continue..." << std::endl;
	(void)std::getchar();
}

void addNewPassword(std::string filename) {
	clearScreen();
	printTitle();

	TableEntry entry;

	std::cout << "Enter your username" << std::endl;
	do {
		std::cout << "> ";
		std::getline(std::cin, entry.username);

		if (entry.username.size() == 0) {
			std::cout << "Username can't be empty" << std::endl;
		}
	} while (entry.username.size() == 0);

	std::cout << "Enter the site URL" << std::endl;
	do {
		std::cout << "> ";
		std::getline(std::cin, entry.siteURL);

		if (entry.siteURL.length() == 0) {
			std::cout << "Site URL can't be empty!" << std::endl;
		}
		else if (!isSiteURLValid(entry.siteURL)) {
			std::cout << "Site URL can't contain whitespace!" << std::endl;
		}
	} while (entry.siteURL.length() == 0 || !isSiteURLValid(entry.siteURL));

	char option;
	std::cout << "Do you want to generate a password (y/n)" << std::endl;
	do {
		std::cout << "> ";
		std::cin >> option;
		std::cin.ignore(IGNORE_SIZE, '\n');
		option = std::tolower(option);

		if (option != 'y' && option != 'n') {
			std::cout << "Incorrect option!" << std::endl;
		}
	} while (option != 'y' && option != 'n');

	switch (option) {
	case 'n': {
		//std::string strength_label;
		//int score;

		entry.password = getPasswordInput();
		break;
	}

	case 'y': {
		int password_len;

		std::string rand_str;
		unsigned long int seed = 0;

		bool options[4] = {};
		int n_options = 0;

		std::cout << "Enter a random string of at least 50 characters long" << std::endl;

		do {
			std::cout << "> ";
			std::getline(std::cin, rand_str);

			if (rand_str.length() < 50) {
				std::cout << "\nNot long enough\n" << std::endl;
				rand_str.clear();
			}
		} while (rand_str.length() < 50);

		seed = genSeed(rand_str);

		std::cout << "Enter the password length (8-20)" << std::endl;
		do {
			std::cout << "> ";
			std::cin >> password_len;

			if (password_len < 8 || password_len > 20) {
				std::cout << "Out of range!" << std::endl;
			}
		} while (password_len < 8 || password_len > 20);

		std::cout << "Enter the number of character types you want to choose (2-4)" << std::endl;
		do {
			std::cout << "> ";
			std::cin >> n_options;

			if (n_options < 2 || n_options > 4) {
				std::cout << "Out of range";
			}
		} while (n_options < 2 || n_options > 4);

		if (n_options == 4) {
			options[0] = options[1] = options[2] = options[3] = true;
		}
		else {
			int option = 0;
			std::cout << "1) Digits\n2) Special\n3) Upper\n4) Lower" << std::endl;
			std::cout << "Enter any " << n_options << " options" << std::endl;

			for (int i = 0; i < n_options; i++) {
				do {
					std::cout << "> ";
					std::cin >> option;

					if (option < 1 || option > 4) {
						std::cout << "Invalid option" << std::endl;
					}
					else if (options[option - 1]) {
						std::cout << "Option already selected.";
					}
				} while (option < 1 || option > 4 || options[option - 1]);
				options[option - 1] = true;
			}
		}

		std::srand(seed);
		
		do {
			entry.password.clear();

			// ============================================================
			//    Build allowed character sets + guarantee each type
			// ============================================================
			std::vector<const char*> allowed_sets;
			std::vector<int> allowed_sizes;

			if (options[0]) {
				allowed_sets.push_back(DIGITS);
				allowed_sizes.push_back(sizeof(DIGITS) - 1);
			}

			if (options[1]) {
				allowed_sets.push_back(SPECIAL);
				allowed_sizes.push_back(sizeof(SPECIAL) - 1);
			}

			if (options[2]) {
				allowed_sets.push_back(UPPER);
				allowed_sizes.push_back(26);
			}

			if (options[3]) {
				allowed_sets.push_back(LOWER);
				allowed_sizes.push_back(26);
			}

			// First: ensure at least one from each selected type
			for (size_t i = 0; i < allowed_sets.size(); i++) {
				const char* set = allowed_sets[i];
				int size = allowed_sizes[i];
				entry.password.push_back(set[std::rand() % size]);
			}

			// Fill the rest randomly
			while ((int)entry.password.length() < password_len) {
				int index = std::rand() % allowed_sets.size();
				const char* set = allowed_sets[index];
				int size = allowed_sizes[index];

				entry.password.push_back(set[std::rand() % size]);
			}

			// Shuffle so required characters aren't all at the start
			std::random_shuffle(entry.password.begin(), entry.password.end());

			// Final output
			std::cout << "Password: " << entry.password << std::endl;
			std::cout << "Do you want to regenerate the password (y/n)?" << std::endl;

			char option;
			do {
				std::cout << "> ";
				std::cin >> option;
				option = std::tolower(option);
				std::cin.ignore(IGNORE_SIZE, '\n');

				if (option != 'y' && option != 'n') {
					std::cout << "Wrong option!" << std::endl;
				}
			} while (option != 'y' && option != 'n');
		
			if (option == 'n') {
				break;
			}
		} while (true);
		break;
	}
	}

	std::vector<TableEntry> table = readCSVFile(filename);

	if (table.size() == 0) {
		entry.id = 1;
	}
	else {
		TableEntry& lastEntry = table.back();
		entry.id = lastEntry.id + 1;
	}

	table.push_back(entry);

	writeCSVFile(filename, table);
}
