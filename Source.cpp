#include <iostream>
#include <sqlite_modern_cpp.h>
#include <thread>
#include <chrono>
#include "AccountManager.h"
#include "CLIManager.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>



int main() {
	CLIManager cli;
	cli.run();
}