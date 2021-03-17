#pragma once
#include <string>
#include "Car.h"
#include "carrepo.h"
#include "validator.h"
#include "undo.h"
#include "observer.h"
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

typedef bool(*MaiMicF)(const Car&, const Car&);



class CarService:public Observable {
private:
	RepoVirtual& repo;
	CarValidator& valid;
	CarWishlist& cos;
	vector<unique_ptr<ActiuneUndo>> undoActions;

public:
	//constructor
	CarService(RepoVirtual& repo, CarValidator& valid, CarWishlist& cos) noexcept :repo{ repo }, valid{ valid }, cos{ cos }{
	}
	CarService(const CarService& ot) = delete;
	CarService() = default;
	//~CarService();

	void add(string nr, string prod, string model, string tip);
	//creeaza masina, o valideaza si daca e valida o adauga in lista
	//nr-string,prod-string,model-string, tip-string

	const vector<Car> getAll()const noexcept {
		//returneaza lista tuturor masinilor
		return repo.getAll();
	}

	void sterge(string elem);
	//sterge masina din lista data prin nr de inmatriculare
	//arunca RepoException daca nu exista
	//elem-string(reprezinta nr de inmatriculare)

	void modifica(string numar, string nouP, string nouM, string nouT);
	//modifica masina data prin nr de inmatriculare cu noile campuri
	//numar-string(nr de inmatriculare), nouP-string(noul producator),nouM-string(noul model), nouT-string(noul tip)

	const Car& cauta(string nume)const;
	//cauta masina data prin nume
	//arunca RepoException daca nu exista
	//numa-string(nr de inmatriculare)

	vector<Car> filtrareProd(string prod) const;
	//filtreaza masinile in functie de producator 
	//prod-string(reprezinta filtrul)
	//returneaza un vector cu masinile care respecta filtrul

	vector<Car> filtrareTip(string tip) const;
	//filtreaza in functie de tip
	//tip-string(filtrul)
	//returneaza un vector cu masinile care respecta filtrul

	vector<Car> sortNr()const;
	//sorteaza dupa nr de inmatriculare crescator
	//returneaza un vector cu masini ordonat

	vector<Car> sortTip()const;
	//sorteaza dupa tip crescator
	//returneaza un vector cu masini ordonat

	vector<Car> sortProdModel()const;
	//sorteaza dupa producator si model
	//returneaza un vector cu masini ordonat


	//vector<Car> generalSort(MaiMicF maiMicF) const;

	map<string, CarDTO> Create_map();

	vector<CarDTO> raport();

	void undo();

	//Lista interactiva
	void addToWishlist(string nr);

	const vector<Car> getAllWishlist();

	void deleteAll();

	void addRandom(int cate);

	void exporthtml(string fisier) const;

};


void testService();





