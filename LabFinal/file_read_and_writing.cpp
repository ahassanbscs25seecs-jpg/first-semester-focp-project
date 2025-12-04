#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

/*
 * Represents each record of the CSV file
 */
struct TableEntry {
    int id;
    std::string username;
    std::string siteURL;
    std::string password;
};

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
std::vector<TableEntry> readCSVFile(const std::string& filename) {
    std::fstream f(filename);
    std::string line;
    std::vector<TableEntry> table;

    /* Read the file line by line. Each line will be a record. */
    while (std::getline(f, line)) {
        /* Take the line and further divide it at the commas
         * which will let us extract each individual entry.
         */

        size_t a = line.find(',');
        size_t b = line.find(',', a + 1);
        size_t c = line.find(',', b + 1);

        table.push_back(TableEntry {
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
    
    for (const TableEntry& e : table) {
        f << e.id << ','
          << e.username << ','
          << e.siteURL << ','
          << e.password << std::endl;
    }
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
    std::string filename = "C:\\Users\\agha waleed agha\\Documents\\bruh.csv";
    std::vector<TableEntry> table = readCSVFile(filename);
}

