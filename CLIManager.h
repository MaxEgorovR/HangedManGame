#pragma once
#include <iostream>
#include <sqlite_modern_cpp.h>
#include <thread>
#include <chrono>
#include "AccountManager.h"

class CLIManager {
public:
	void run() {
		start_form();
		int choise;
		while (true) {
			std::cout << "1 - New game\nElse - Exit\n";
			std::cin >> choise;
			if (choise == 1) {
				manager->user->score += hanged_game();
			}
			else {
				break;
			}
		}
	}
private:
	void start_form() {
		system("cls");
		std::cout << "Choose an action\n"
			"1. Registration\n"
			"2. Log in\n";

		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1:
			sign_up_form();
			break;
		case 2:
			sign_in_form();
			break;
		}
	}

	void sign_in_form() {
		system("cls");

		std::string login, password;

		std::cout << "Login: "; std::cin >> login;
		std::cout << "Password: "; std::cin >> password;
		if (this->manager->sign_in(login, password)) {
			std::cout << "Login completed successfully!\nYour name: "<<manager->user->name << "\nYour score: " << manager->user->score << std::endl;
			std::this_thread::sleep_for(std::chrono::nanoseconds(5000000000));
		}
		else {
			std::cout << "Invalid username or password!\n";
			std::this_thread::sleep_for(std::chrono::nanoseconds(5000000000));
			start_form();
		};
	}

	void sign_up_form() {
		system("cls");

		std::string name, login, password;

		std::cout << "Name: "; std::cin >> name;
		std::cout << "Login: "; std::cin >> login;
		std::cout << "Password: "; std::cin >> password;

		if (this->manager->sign_up(name, login, password)) {
			std::cout << "The user has been successfully created!\nYour name: " << manager->user->name << "\nYour score: " << manager->user->score << std::endl;
			std::this_thread::sleep_for(std::chrono::nanoseconds(5000000000));
			sign_in_form();
		}
		else {
			std::cout << "A user with this username already exists! Try again\n";
			std::this_thread::sleep_for(std::chrono::nanoseconds(5000000000));
			start_form();
		}
	}

    std::string after_choice(const std::string& word, const std::string& newword, char elem) {
        std::string result = "";
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == elem) {
                result += elem;
            }
            else if (newword[i] != '_') {
                result += newword[i];
            }
            else {
                result += '_';
            }
        }
        return result;
    }

    int hanged_game() {
        std::vector<std::string> words = { "SUN", "SKY", "STARS", "MOON", "HERT", "BRAIN" };
        int index = std::rand() % words.size();
        std::string word(words[index].length(), '_');

        std::cout << "You're in the hangman game!" << std::endl;
        std::cout << word << std::endl;

        int choice = 0;
        while (true) {
            std::cout << "Enter the number of attempts for which you want to guess a random word: ";
            std::cin >> choice;
            if (choice <= 0) {
                std::cout << "The number of attempts must be greater than 0!" << std::endl;
            }
            else if (choice > 26) {
                std::cout << "There are 26 letters in the English alphabet! Why do you need so many attempts?!" << std::endl;
            }
            else {
                break;
            }
        }

        int i = 1;
        char choice1;

        while (true) {
            if (i <= choice) {
                std::cout << word << std::endl;
                if (word.find('_') == std::string::npos) {
                    std::cout << "Hooray, you've won!" << std::endl;
                    return 1;
                }
                std::cout << "Attempt " << i << " of " << choice << ". Enter a letter of the English alphabet: ";
                while (true) {
                    std::cin >> choice1;
                    if ((choice1 >= 'A' && choice1 <= 'Z')|| (choice1 >= 'a' && choice1 <= 'z')) {
                        break;
                    }
                    else {
                        std::cout << "There is no such letter in the English alphabet." << std::endl;
                    }
                }

                if (words[index].find(toupper(choice1)) != std::string::npos && word.find(toupper(choice1)) == std::string::npos) {
                    word = after_choice(words[index], word, toupper(choice1));
                    --i;
                }
                else {
                    std::cout << "This letter is not in this word(" << std::endl;
                }
            }
            else {
                std::cout << word << std::endl;
                if (word.find('_') == std::string::npos) {
                    std::cout << "Hooray, you've won!" << std::endl;
                    break;
                }
                std::cout << "You've lost(" << std::endl;
                return -1;
            }
            ++i;
        }
    }
private:
	std::shared_ptr<AccountManager> manager = std::make_shared<AccountManager>();
};