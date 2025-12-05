#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

#define MAX_PASSWORD_LEN 20

struct TableEntry {
	int id;
	std::string username;
	std::string siteURL;
	std::string password;
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

int main() {
	printTitle();

	int option = 0;
	bool done = false;

	std::string passFilename = "C:\\Users\\agha waleed agha\\Documents\\bruh.csv";

	/* Read user options. */
	/* Take the appropriate action. */

	/*std::cout << "Enter the password filename: ";
	std::cin >> passFilename;*/

	std::vector<TableEntry> table = readCSVFile(passFilename);

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
					      << "2) Site URL" << std::endl;

				do {
					std::cout << "> ";
					std::cin >> option;

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
						std::cin.ignore(1);
						std::getline(std::cin, username);

						std::cout << "'" << username << "'" << std::endl;

						if (username.length() == 0) {
							std::cout << "Username can't be empty!" << std::endl;
						}
					} while (username.length() == 0);

					searchResults = searchByUsername(table, username);

					break;
				}

				case 2: {
					std::string siteURL;

					std::cout << "Enter the site url" << std::endl;
					do {
						std::cout << "> ";
						std::cin.ignore(1);
						std::getline(std::cin, siteURL);

						if (siteURL.length() == 0) {
							std::cout << "Site URL can't be empty!" << std::endl;
						}
					} while (siteURL.length() == 0);

					searchResults = searchBySiteURL(table, siteURL);

					break;
				}
				}

				printTable(searchResults);

				std::cout << "\nPress any key to continue..." << std::endl;
				(void)std::getchar();

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
	}

	return 0;
}
