#pragma once

#include <string>
#include "Car.h"
#include <vector>

using namespace std;

class ValidateException {
	vector<string>msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {

	}
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};


class CarValidator {
public:
	void validate(const Car& c);
};
