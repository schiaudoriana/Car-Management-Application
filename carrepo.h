#pragma once
#include "Car.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>



using std::string;
using std::vector;
using std::map;

class RepoException {
	string msg;
public:
	RepoException(string m) :msg{ m } {
		//exceptie dac exista deja masina
	}
	string getMessage() {
		return msg;
	}

};

//clasa RepoVirtual, toate Repo-urile mostenesc RepoVirtual 
class RepoVirtual {

public:
	virtual const vector<Car> getAll()const noexcept = 0;

	virtual void store(const Car& c) = 0;

	virtual void remove(string elem) = 0;

	virtual void modify(string numar, string nouP, string nouM, string nouT) = 0;

	virtual const Car& search(string numar) const = 0;

	virtual ~RepoVirtual() = default;


};

class CarRepo : public RepoVirtual {
private:
	//lista de masini
	map<string, Car>cars;

public:

	CarRepo() = default;
	CarRepo(const CarRepo& ot) = delete;
	virtual ~CarRepo() = default;


	//adauga o masina 
	virtual void store(const Car& c);

	//returneaza toate masinile
	virtual const vector<Car> getAll()const noexcept;

	//sterge o masina data prin nr de inmatriculare
	virtual void remove(string elem);

	//modifica o masina data prin nr cu noile valori date
	virtual void modify(string numar, string nouP, string nouM, string nouT);

	//cauta o masina data prin numar
	virtual const Car& search(string numar) const;
};

//lista interactiva
class CarWishlist {
private:
	RepoVirtual& repo;
	vector<Car> wishlist;

public:
	CarWishlist(RepoVirtual&repo) :repo{ repo } {};

	void addToWishlist(const Car& c);

	void deleteAll()noexcept;

	const vector<Car> getAllWishlist();

	void addRandom(int cate);

	void deleteCar(string nr);

};

class CarRepoFile :public RepoVirtual {
private:
	std::string fName;
	map<string, Car>cars;
	void loadFromFile();
	void writeToFile();

public:
	CarRepoFile(std::string fName) : fName{ fName } {
		loadFromFile(); //incarcam date din fisier
	}

	virtual void store(const Car& c) {
		for (const auto& elem : cars) {
			if (elem.first == c.getnrInmatriculare()) {
				throw RepoException("Masina exista deja!\n\n");
			}
		}
		cars.insert(pair<string, Car>(c.getnrInmatriculare(), c));

		writeToFile();
	}

	virtual void remove(string elem) {
		int found = 0;
		for (auto const& c : cars) {
			if (c.first == elem) {
				found = 1;
				cars.erase(elem);
				break;
			}
		}
		if (found == 0)
			throw RepoException("Masina cu numarul dat nu exista!\n\n");
		else
			writeToFile();
	}
	virtual void modify(string numar, string nouP, string nouM, string nouT) {
		int found = 0;
		for (auto& c : cars) {
			if (c.first == numar) {
				found = 1;
				c.second.setModel(nouM);
				c.second.setProd(nouP);
				c.second.setTip(nouT);
			}
		}
		if (found == 0)
			throw RepoException("Masina cu numarul dat nu exista!\n\n");
		else
			writeToFile();
	}

	virtual const Car& search(string numar) const {
		auto rez = std::find_if(cars.begin(), cars.end(), [numar](const auto& c) {return c.first == numar; });
		if (!(rez != cars.end())) {
			throw RepoException("Masina cu numarul dat nu exista!\n\n");

		}
		else {
			const Car& gasit = (*rez).second;
			return gasit;
		}
	}

	virtual const vector<Car> getAll()const noexcept {
		vector<Car>rez;
		std::transform(cars.begin(), cars.end(), std::back_inserter(rez), [](const pair<string, Car>pereche) {return pereche.second; });
		return rez;
	}

};

class CarRepoLab :public RepoVirtual {
private:
	double p; //probabilitatea
	map<string, Car>cars;

public:
	CarRepoLab(double p) :p{ p } {}

	//adauga o masina 
	virtual void store(const Car& c);
	//returneaza toate masinile
	virtual const vector<Car> getAll()const noexcept;

	//sterge o masina data prin nr de inmatriculare
	virtual void remove(string elem);

	//modifica o masina data prin nr cu noile valori date
	virtual void modify(string numar, string nouP, string nouM, string nouT);

	//cauta o masina data prin numar
	virtual const Car& search(string numar) const;

};

void testRepo();
