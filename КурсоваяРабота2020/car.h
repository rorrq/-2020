#pragma once

#include <iostream>
#include <fstream>
#include "exceptions.h"

class car {
public:
	car();
	car& operator=(const car& Obj);
	friend std::ostream& operator<<(std::ostream& os, const car& Obj);
	friend std::istream& operator>>(std::istream& is, car& Obj);
	friend std::ofstream& operator<<(std::ofstream& ofs, const car& Obj);
	friend std::ifstream& operator>>(std::ifstream& ifs, car& Obj);
	friend bool operator==(const car& Obj1, const car& Obj2);
	bool check(const std::string& model) const;
	friend void move(car& Obj1, car& Obj2);

	const std::string& get_model() const;
	const std::string& get_color() const;

	void set_model(const std::string model);

	bool is_pattern() const;

private:

	std::string model;
	std::string color;
	int year;
	int airbags;
	double capacity;
	double power;
	double fuelTank;
	double fuelCons;
	bool rdrHeat;
	bool gearBox;
	bool ABS;
	bool EDS;
	bool sysNav;
	bool computer;
	bool seatHead;
	bool roofRack;
	double x;
	double y;
	double z;
};
