#pragma once
#include <chrono>
#include <ctime>
using namespace std;
namespace Lib {
	std::chrono::nanoseconds getTimeStamp(){
		std::chrono::nanoseconds ns = duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
		return ns.count()/1000000000.0;
	}
};