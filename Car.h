#pragma once
#include <string>
#include <iostream>

using std::string;
using namespace std;

class Car {
	string nrInmatriculare;
	string producator;
	string model;
	string tip;

public:
	//constructor
	Car(const string nr, const string pr, const string mod, const string t) :nrInmatriculare{ nr }, producator{ pr }, model{ mod }, tip{ t }{}

	//constructor de copiere
	//Car(const Car& ot) :nrInmatriculare{ ot.nrInmatriculare }, producator{ ot.producator }, model{ ot.model }, tip{ ot.tip }{
	//	cout << "Copy constructor used" << endl;
	//}

	//returneaza nr de inmatriculare
	string getnrInmatriculare() const {
		return nrInmatriculare;
	}
	//returneaza producator
	string getProducator() const {
		return producator;
	}
	//returneaza model
	string getModel() const {
		return model;
	}
	//returneaza tipul
	string getTip() const {
		return tip;
	}

	//verifica daca 2 masini au acelasi nr 
	bool operator==(const Car& ot1) noexcept {
		return nrInmatriculare == ot1.nrInmatriculare;
	}

	//operator!= pt 2 masini
	bool operator!=(const Car& ot)noexcept {
		return nrInmatriculare != ot.nrInmatriculare;
	}

	void setProd(string ot) {
		producator = ot;

	}

	void setModel(string ot) {
		model = ot;
	}
	void setTip(string ot) {
		tip = ot;
	}
};

bool cmpNumar(const Car& c1, const Car& c2);

bool cmpTip(const Car& c1, const Car& c2);


void testCar();


class CarDTO {
private:
	string type;
	//MyList<string>lista;
	string nr;
	int count;

public:
	CarDTO() noexcept : nr{ "" }, type{ "" }, count{ 0 }{}

	void setNr(string new_nr) {
		nr = new_nr;
	}

	void setTip(string new_type) {
		type = new_type;
	}

	void setCount(int new_count)noexcept {
		count = new_count;
	}

	string getNr() {
		return nr;
	}

	string getType() {
		return type;
	}

	int getCount() noexcept {
		return count;
	}

};