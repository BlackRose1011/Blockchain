#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include "transactions.h"

using namespace std;

int from, to;
string check;
int sum;

#define RESET       "\033[0m"
#define CYAN        "\033[36m"     
#define RED         "\033[31m" 

// FUNCTION TO REWRITE THE LINE IN FILE
void rewrite_line(const string& filename, int target_line, const string& new_content) {
    ifstream fin(filename); // Відкриваємо файл для читання
    if (!fin.is_open()) {
        cerr << "Unable to open file!" << endl;
        return;
    }

    vector<string> lines;
    string line;
    int current_line = 1;

    // Зчитування вмісту файлу в пам'ять
    while (getline(fin, line)) {
        if (current_line == target_line) {
            lines.push_back(new_content); // Замінюємо потрібну строчку
        } else {
            lines.push_back(line); // Зберігаємо інші строчки без змін
        }
        current_line++;
    }

    fin.close(); // Закриваємо файл після читання

    ofstream fout(filename); // Відкриття файлу для запису
    if (!fout.is_open()) {
        cerr << "Unable to open file for writing!" << endl;
        return;
    }

    // Записуємо модифікований вміст назад у файл
    for (const string& l : lines) {
        fout << l << endl;
    }

    fout.close(); // Закриваємо файл після запису
}

// FUNCTION TO SEND CRYPTO FROM ONE TO ANOTHER WALLET
void send_crypto_func() {
    cout << "\nWrite wallet number from what you want to send:\n>> ";
    cin >> from; 

    cout << "Write what wallet will recieve:\n>> ";
    cin >> to;

    cout << "How much you would like to send?\n>> ";
    cin >> sum;

    cout << "\n\nAre you sure that all the entered information is correct? (YES / NO)\n"
    << CYAN << "\nFrom: " << RESET << from << CYAN << "\nTo: " << RESET 
    << to << CYAN << "\nSum: " << RESET << sum << "\n\n>> ";
    cin >> check;
    cout << "\n";

    // CHECK IF THE USER REALY WANT TO SEND THE CRYPTO TO ANOTHER WALLET
    if (check == "YES") {
        // PATH TO FILE
        string filename_from = "database/wallets/wallet_" + to_string(from) + ".md";
        ifstream fin_from(filename_from); // OPEN FILE

        string filename_to = "database/wallets/wallet_" + to_string(to) + ".md";
        ifstream fin_to(filename_to); 

        int digits_1 = 0; 
        int digits_2 = 0;

        if (fin_from.is_open()) {
            string line;
            int lineNumber = 1; // NUMBER OF THE LINE WHAT WE STARTED TO LOOKINK FOR LINE WHAT WE NEED
            
            while (getline(fin_from, line)) {
                if (lineNumber == 4) { // READ FOURTH LINE (AS EXAMPLE FOURTH LINE, OF COURSE YOU CAN CHANGE IT)
                    
                    // READ ALL LINE, CHAR BY CHAR
                    string digits_str; 
                    for (char c : line) {
                        if (isdigit(c)) {
                            digits_str += c;
                        }
                    }
                    digits_1 = stoi(digits_str);
                    break; // LEAVE CYCLE 
                }
                lineNumber++;
            }

            fin_from.close(); // CLOSE FILE AFTER READING
        } 
        else {
            cout << RED << "Error " << RESET << ": Unable to open file!" << endl;
        }

        if (fin_to.is_open()) {
            string line;
            int lineNumber = 1; 
            
            while (getline(fin_to, line)) {
                if (lineNumber == 4) { 
                    string digits_str;
                    for (char c : line) {
                        if (isdigit(c)) {
                            digits_str += c;
                        }
                    }
                    digits_2 = stoi(digits_str);
                    break; 
                }
                lineNumber++;
            }

            fin_to.close();
        } 
        else {
            // ERROR IF U CANT OPEN THE FILE
            cout << RED << "Error " << RESET << ": Unable to open file!" << endl;
        }
        
        if (digits_1 >= sum) {
            // HERE WE CALCULATE WHAT THE BALANCE WOULD BE IN SENDER AND RECIEVER
            int balance_1 = digits_1 - sum;
            int balance_2 = digits_2 + sum;

            string new_content_from = "# Balance: " + to_string(balance_1);
            string new_content_to = "# Balance: " + to_string(balance_2);

            rewrite_line(filename_from, 4, new_content_from); // UPDATE SENDER BALANCE
            rewrite_line(filename_to, 4, new_content_to); // UPDATE RECIEVER BALANCE
            cout << "Transaction completed " << CYAN << "successfully" << ".\n";
        }
        // ERROR IF SENDER HAD NO ENOUGHT MONEY TO SEND CRYPTO
        else {
            cout << RED << "Error " << RESET << ":Not enough balance to make the transaction." << endl;
        }

    // OTHER
    } else if (check == "NO") {
        cout << RED << "Error: " << RESET << "Operation cancelled." << endl;
    } else {
        cout << RED << "Error: " << RESET << "Invalid input." << endl;
    }
}
