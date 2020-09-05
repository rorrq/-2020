#pragma once

#include "KeeperCar.h"
#include "func.h"

class handlerInterface {
public:
	handlerInterface(KeeperCar* kCar) : kCar(kCar), next(nullptr) {}
	void add(handlerInterface* b) {
		if (next)
			next->add(b);
		else
			next = b;
	}
	virtual int handle(const car& ObjCar, int count) {
		return next->handle(ObjCar, count);
	}
protected:
	KeeperCar* kCar;
private:
	handlerInterface* next;
};

class handlerSalon : public handlerInterface {
public:
	handlerSalon(KeeperCar* kCar) : handlerInterface(kCar) {};
	int handle(const car& ObjCar, int count) override {
		KeeperCar tmpCar(kCar->sim_car(ObjCar));
		if (tmpCar.get_size()) {
			int num, tmpCount;
			std::cout << "Currently we have this in salon : " << std::endl;
			std::cout << tmpCar;

			num = get_dec("Enter the number(0 - if nothing fits): ") - 1;

			if (num < 0) {
				std::cout << "Redirecting to warehouse database..." << std::endl;
				return handlerInterface::handle(ObjCar, count);
			}

			try {
				tmpCount = kCar->get_amount(num);
			}
			catch (exceptions& e) {
				print_exp(e);
				return 0;
			}

			int ret = 0;

			if (count > tmpCount) {
				std::cout << "Order too large, redirecting to warehouse database..." << std::endl;
				ret = handlerInterface::handle(tmpCar[num], count - tmpCount);
				count = tmpCount;
			}

			kCar->sub_car(tmpCar[num], count);

			std::cout << "Sold " << count << " car from salon." << std::endl;

			return ret;
		}
		else {
			std::cout << "There are no similar copies in the salon, forwarding to the warehouse database..." << std::endl;
			return handlerInterface::handle(ObjCar, count);
		}
		return 0;
	}
};

class handlerBase : public handlerInterface {
public:
	handlerBase(KeeperCar* kCar) : handlerInterface(kCar) {};
	int handle(const car& ObjCar, int count) override {
		int tmpCount;

		if (ObjCar.is_pattern()) {
			KeeperCar tmpCar(kCar->sim_car(ObjCar));
			if (tmpCar.get_size()) {
				std::cout << "At the moment the following set is in stock: " << std::endl;
				std::cout << tmpCar;

				int num = get_dec("Enter number(0 - if no car fits): ") - 1;

				if (num < 0) {
					std::cout << "Redirection to production..." << std::endl;
					return handlerInterface::handle(ObjCar, count);;
				}

				try {
					tmpCount = kCar->get_amount(num);
				}
				catch (exceptions& e) {
					print_exp(e);
					return 0;
				}

				int ret = 0;

				if (count > tmpCount) {
					std::cout << "The order is too large, diversion to production..." << std::endl;
					ret = handlerInterface::handle(tmpCar[num], count - tmpCount);
					count = tmpCount;
				}

				kCar->sub_car(tmpCar[num], count);

				std::cout << "Sold " << count << " autos from warehouse." << std::endl;

				if (ret) return ret;

			}
			else {
				std::cout << "There are no similar instances in the warehouse database, redirecting to production... " << std::endl;
				return handlerInterface::handle(ObjCar, count);
			}
		}
		else {
			int num = kCar->find_car(ObjCar);
			if (num == kCar->get_size()) {
				std::cout << "The warehouse database does not have these instances, readdressing to production... " << std::endl;
				return handlerInterface::handle(ObjCar, count);
			}
			else {
				tmpCount = kCar->get_amount(num);

				int ret = 0;

				if (count > tmpCount) {
					std::cout << "The order is too large, diversion to production..." << std::endl;
					ret = handlerInterface::handle((*kCar)[num], count - tmpCount);
					count = tmpCount;
				}

				kCar->sub_car((*kCar)[num], count);

				std::cout << "Sold " << count << " autos from warehouse." << std::endl;

				if (ret) return ret;

			}
		}
		return 0;
	}
};

class handlerProduction : public handlerInterface {
public:
	handlerProduction(KeeperCar* kCar) : handlerInterface(kCar) {};
	int handle(const car& ObjCar, int count) override {
		int tmpCount;

		if (ObjCar.is_pattern()) {
			KeeperCar tmpCar(kCar->sim_car(ObjCar));
			if (tmpCar.get_size()) {
				std::cout << "At the moment, the plant can create the following set: " << std::endl;

				std::cout << tmpCar;

				int num = get_dec("Enter number(0 - if noauto fits): ") - 1;

				if (num < 0) return -1;

				try {
					tmpCount = kCar->get_amount(num);
				}
				catch (exceptions& e) {
					print_exp(e);
					return 1;
				}

				if (count > tmpCount) {
					std::cout << "The order is too big." << std::endl;
					count = tmpCount;
				}

				kCar->sub_car(tmpCar[num], count);

				std::cout << "Sold " << count << " autos from production." << std::endl;

			}
			else {
				std::cout << "The factory cannot make a car of this model and color." << std::endl;
				return -1;
			}
		}
		else {
			int num = kCar->find_car(ObjCar);
			if (num == kCar->get_size()) {
				std::cout << "The plant cannot make these copies." << std::endl;
				return -2;
			}
			else {
				tmpCount = kCar->get_amount(num);

				bool flag = 0;

				if (count > tmpCount) {
					std::cout << "The order is too big." << std::endl;
					count = tmpCount;
					flag = true;
				}
				kCar->sub_car((*kCar)[num], count);

				std::cout << "Sold " << tmpCount << " autos from production." << std::endl;

				if (flag) return -2;
			}
		}
		return 0;
	}
};