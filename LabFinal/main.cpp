#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

#define MAX_PASSWORD_LEN 20

struct TableEntry {
	int id;
	std::string password;
	std::string username;
	std::string siteURL;
};

/**
 * clearScreen:
 *   Clears the screen.
 * 
 * '\033[H' moves the terminal cursor to (0, 0)
 * '\033[2H' clears the entire entire terminal, regardless of cursor position.
 */
void clearScreen() {
	std::cout << "\033[H\033[2J";
}

/**
 */
void printTitle() {
	std::cout << "PassGen\n"
		      << "-------\n" << std::endl;
}
//
//void add_new_password(std::string filename) {
//	clear_screen();
//
//	std::cout << "Do you want to generate a password (y/n)";
//
//	TableEntry new_entry;
//	char option;
//
//	do {
//		std::cin.seekg(SEEK_END, 0);
//		std::cout << "> ";
//		std::cin >> option;
//
//		if (option != 'y' && option != 'n') {
//			std::cout << "Invalid option!" << std::endl;
//		}
//	} while (option != 'y' && option != 'n');
//	
//	std::string password;
//
//	switch (option) {
//	case 'y':
//	case 'n':
//	}
//
//	std::cout << "Enter a username: ";
//	std::cin >> new_entry.username;
//
//	std::cout << "Enter a site url: ";
//	std::cin >> new_entry.site_url;
//
//	/* Put the url into our password file. */
//	std::fstream f(filename);
//	f.seekg(std::ios::end);
//
//	f.close();
//}
//

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
void writeCSVFile(const std::string& filename, const std::vector<TableEntry>& table) {
	std::ofstream f(filename);

	for (auto& e : table) {
		f << e.id << ','
			<< e.username << ','
			<< e.siteURL << ','
			<< e.password << std::endl;
	}
}

/**
 *
 */
std::vector<TableEntry> searchByUsername(const std::vector<TableEntry>& table, const std::string& username) {
	std::vector<TableEntry> result;

	for (auto& e : table) {
		if (username == e.username) {
			result.push_back(e);
		}
	}

	return result;
}

/**
 *
 */
std::vector<TableEntry> searchBySiteURL(const std::vector<TableEntry>& table, const std::string& siteURL) {
	std::vector<TableEntry> result;

	for (auto& e : table) {
		if (siteURL == e.siteURL) {
			result.push_back(e);
		}
	}

	return result;
}

int main() {
	printTitle();

	int option = 0;
	bool done = false;

	std::string passFilename;

	/* Read user options. */
	/* Take the appropriate action. */

	std::cout << "Enter the password filename: ";
	std::cin >> passFilename;

	std::vector<TableEntry> table = readCSVFile(passFilename);

	clearScreen();
	printTitle();

	std::cout << "Enter an action\n"
			  << "1) Enter a new password\n"
			  << "2) Search for passwords\n"
			  << "3) Quit" << std::endl;

	do {
		std::cout << "> ";
		std::cin >> option;
		
		switch (option) {
		case 1:
			done = true;

			break;

		case 2: {
			done = true;
			clearScreen();
			printTitle();

			std::vector<TableEntry> searchResults;
			int option = 0;

			std::cout << "What do you want to search with?\n"
				<< "1) Username\n"
				<< "2) Site URL\n" << std::endl;

			do {
				std::cout << "> ";
				std::cin >> option;
				
				if (option != 1 && option != 2) {
					std::cout << "Wrong option!" << std::endl;
				}
			} while (option != 1 && option != 2);

			switch (option) {
			case 1:
				searchResults = searchByUsername(table, );
				break;
				
			case 2:

			}

			break;
		}

		case 3:
			done = true;
			return 0;

		default:
			std::cout << "Invalid option!" << std::endl;
			break;
		}
	} while (!done);

	return 0;
}
