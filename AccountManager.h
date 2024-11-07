#pragma once
#include <iostream>
#include <sqlite_modern_cpp.h>
#include <thread>
#include <chrono>
#include "User.h"

class AccountManager {
public:
	std::shared_ptr<User> user = std::make_shared<User>();

	bool sign_in(std::string login, std::string password) {
		try {
			bool check = false;
			db << "select count(*) from users where login = ? and password = ?;"
				<< login
				<< password
				>> check;

			if (!check)
				return false;
			std::string name;
			int score;
			db << "SELECT name FROM users WHERE login = ? AND password = ?;"
				<< login
				<< password
				>> name;
			db << "SELECT score FROM users WHERE login = ? AND password = ?;"
				<< login
				<< password
				>> score;
			this->user->name = name;
			this->user->login = login;
			this->user->password = password;
			this->user->score = score;
			return true;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	bool sign_up(std::string name,
		std::string login,
		std::string password) {
		try {
			bool check = false;
			db << "select count(*) from users where login = ?;"
				<< login
				>> check;

			if (check)
				return false;
			int score = 0;
			db << "insert into users (name, login, password, score) "
				"values (?,?,?,?);"
				<< name
				<< login
				<< password
				<< score;
			this->user->name = name;
			this->user->login = login;
			this->user->password = password;
			this->user->score = score;
			return true;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	AccountManager()
	{
		db << "create table if not exists users ("
			"	id integer primary key autoincrement not null,"
			"	name text,"
			"	login text,"
			"	password text,"
			"	score integer"
			");";
	}
private:
	sqlite::database db{ "database.db" };
};
