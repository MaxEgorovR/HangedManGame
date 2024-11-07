#pragma once
#include <iostream>
#include <sqlite_modern_cpp.h>
#include <thread>
#include <chrono>

struct User
{
public:
	std::string name;

	std::string login;

	std::string password;

	int score = 0;
};