#include "Chain_of_Responsibility.h"

using std::cout;
using std::cin;
using std::endl;


void handler_db(KeeperCar& Obj);


int main() {
	int ch;
	bool FLAG = true;
	KeeperCar salonCar, dbCar, prdCar;

	system("color f0");

	handlerSalon salon(&salonCar);
	handlerBase dataBase(&dbCar);
	handlerProduction prdctn(&prdCar);

	salon.add(&dataBase);
	dataBase.add(&prdctn);

	try {
		salonCar.load("C:/Users/Public/TP/salon.txt");
		dbCar.load("C:/Users/Public/TP/dealer.txt");
		prdCar.load("C:/Users/Public/TP/manufacture.txt");
	}
	catch (exceptions& e) {
		print_exp(e);
		return 0;
	}


	std::string mode[]  = {
		"Interaction with DB",
		"Interaction with user",
		"Exit"
	};

	std::string db[] = {
		"Interaction with salon",
		"Interaction with dealers DB",
		"Interaction with Manufacturing",
		"Return"
	};

	std::string model;

	while (FLAG) {

		try {
			ch = menu("Choose mode: ", 3, mode);
		}
		catch (exceptions& e) {
			print_exp(e);
			continue;
		}

		switch (ch) {
		case 1:
			while (FLAG) {

				try {
					ch = menu("Enter what the work will be done with: ", 4, db);
				}
				catch (exceptions& e) {
					print_exp(e);
					continue;
				}

				switch (ch) {
				case 1:
					handler_db(salonCar);
					break;
				case 2:
					handler_db(dbCar);
					break;
				case 3:
					handler_db(prdCar);
					break;
				case 4:
					FLAG = false;
					break;
				default:
					cout << "Wrong choice." << endl;
				}
			}
			FLAG = true;
			break;
		case 2: {
			car tmpObj;
			int count;

			cout << "Enter car model: ";
			cin >> model;
			cout << "Enter the required quantity: ";
			cin >> count;


			tmpObj.set_model(model);

			switch (salon.handle(tmpObj, count)) {
			case -2:
				cout << "We are sorry that we could not find the right number of cars for you." << endl;
				break;
			case -1:
				cout << "We are sorry that we could not find the car you need." << endl;
				break;
			case 0:
				cout << "Congratulations on your successful purchase!" << endl;
				break;
			case 1:
				cout << "Interruption of a sales transaction..." << endl;
				break;
			}

			model.clear();
		}
			  break;
		case 3:
			FLAG = false;
			try {
				salonCar.save("C:/Users/Public/TP/salon.txt");
				dbCar.save("C:/Users/Public/TP/dealer.txt");
				prdCar.save("C:/Users/Public/TP/manufacture.txt");
			}
			catch (exceptions& e) {
				print_exp(e);
				FLAG = true;
			}

			break;
		default:
			cout << "Wrong choice" << endl;
		}
	}





	int xxccvv;
	cin >> xxccvv;

	return 0;
}

void handler_db(KeeperCar& Obj) {
	int ch;
	bool FLAG = true;
	car carObj;
	std::string list[] = {
		"Display content",
		"Add car",
		"Delete auto",
		"Return"
	};

	while (FLAG) {

		try {
			ch = menu("Select menu item: ", 4, list);
		}
		catch (exceptions& e) {
			print_exp(e);
			continue;
		}

		switch (ch) {
		case 1:
			cout << Obj;

			break;
		case 2:
			try {
				cin >> carObj;
			}
			catch (exceptions& e) {
				print_exp(e);
				break;
			}

			ch = get_dec("Enter the required quantity: ");

			Obj.add_car(carObj, ch);

			break;
		case 3:
			try {
				cin >> carObj;
			}
			catch (exceptions& e) {
				print_exp(e);
				break;
			}

			ch = get_dec("Enter the number to be deleted (delete all: -1): ");
			if (ch < 0) {
				ch = Obj.find_car(carObj);
				if (ch < Obj.get_size()) ch = Obj.get_amount(ch);
				else ch = 0;
			}
			try {
				Obj.sub_car(carObj, ch);
			}
			catch (exceptions& e) {
				print_exp(e);
			}
			break;
		case 4:
			FLAG = false;
			break;
		default:
			cout << "Wrong choice." << endl;
		}
	}
}