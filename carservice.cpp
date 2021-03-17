#include "carservice.h"
#include <assert.h>
#include <string>
#include <map>
#include <algorithm>
#include "export.h"

using std::string;
using std::map;

void CarService::add(string nr, string prod, string model, string tip) {

	Car c{ nr,prod,model,tip };
	valid.validate(c);
	repo.store(c);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, c));
}


void CarService::sterge(string elem) {
	auto c = repo.search(elem);
	repo.remove(elem);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, c));
}

void CarService::modifica(string numar, string nouP, string nouM, string nouT) {
	auto c = repo.search(numar);
	repo.modify(numar, nouP, nouM, nouT);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, c));
}

const Car& CarService::cauta(string nume)const {

	return repo.search(nume);

}

void CarService::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu mai exista operatii\n");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

vector<Car> CarService::filtrareProd(string prod) const {

	vector<Car>rez;
	vector<Car>allCars{ repo.getAll() };
	std::copy_if(allCars.begin(), allCars.end(), std::back_inserter(rez), [prod](const Car& c) {return c.getProducator() == prod; });
	vector<Car>dest;
	for (const auto& c : rez) {
		dest.push_back(c);
	}
	return dest;

}

vector<Car> CarService::filtrareTip(string tip) const {


	vector<Car>rez;
	vector<Car> allCars{ repo.getAll() };
	std::copy_if(allCars.begin(), allCars.end(), std::back_inserter(rez), [tip](const Car& c) {return c.getTip() == tip; });
	vector<Car>dest;
	for (const auto& c : rez) {
		dest.push_back(c);
	}
	return dest;
}

vector<Car> CarService::sortNr() const {

	vector<Car> copie{ repo.getAll() };
	std::sort(copie.begin(), copie.end(), [](const Car& c1, const Car& c2) {return c1.getnrInmatriculare() < c2.getnrInmatriculare(); });
	vector<Car>dest;
	for (const auto& c : copie) {
		dest.push_back(c);
	}
	return dest;
}

vector<Car> CarService::sortTip() const {


	vector<Car> copie{ repo.getAll() };
	std::sort(copie.begin(), copie.end(), [](const Car& c1, const Car& c2) {return c1.getTip() < c2.getTip(); });
	vector<Car>dest;
	for (const auto& c : copie) {
		dest.push_back(c);
	}
	return dest;
}

vector<Car> CarService::sortProdModel()const {

	vector<Car> copie{ repo.getAll() };
	std::sort(copie.begin(), copie.end(), [](const Car& c1, const Car& c2) {	if (c1.getProducator() == c2.getProducator())
		return c1.getModel() < c2.getModel();
	else return c1.getProducator() < c2.getProducator(); });
	vector<Car>dest;
	for (const auto& c : copie) {
		dest.push_back(c);
	}
	return dest;

}

//vector<Car> CarService::generalSort(MaiMicF maiMicF) const {
//	vector<Car> copie{ repo.getAll() };
//	for (size_t i = 0; i < copie.size(); i++) {
//		for (size_t j = i + 1; j < copie.size(); j++) {
//			if (!maiMicF(copie[i], copie[j])) {
//				Car aux = copie[i];
//				copie[i] = copie[j];
//				copie[j] = aux;
//			}
//		}
//	}
//	return copie;
//}
//
//vector<Car> CarService::sortNr()const {
//	return generalSort(cmpNumar);
//
//}
//
//vector<Car> CarService::sortTip()const {
//	return generalSort(cmpTip);
//
//}

map<string, CarDTO> CarService::Create_map() {
	map<string, CarDTO> m;
	for (const auto& car : repo.getAll()) {
		CarDTO dto;
		int ok = 0;
		string tip = car.getTip();
		for (auto& el : m) {
			if (el.first == tip) {
				el.second.setCount(el.second.getCount() + 1);
				ok = 1;
			}
		}
		if (ok == 0) {
			dto.setTip(tip);
			dto.setCount(1);
			m.insert(pair<string, CarDTO>(tip, dto));
		}
	}
	return m;
}

vector<CarDTO>CarService::raport() {
	vector<CarDTO> rez;
	CarDTO dto;
	map<string, CarDTO> m = Create_map();
	//for (const auto& car : repo.getAll()) {
	//	string tip = car.getTip();
	//	dto = m[tip];
	//	dto.setNr(car.getnrInmatriculare());
	//	rez.push_back(dto);
	//}
	std::transform(m.begin(), m.end(), std::back_inserter(rez), [](const pair<string, CarDTO>pereche) {return pereche.second; });
	return rez;
}


//Lista interactiva
void CarService::addToWishlist(string nr) {
	const auto c = repo.search(nr);
	cos.addToWishlist(c);
	undoActions.push_back(std::make_unique<UndoWishlist>(cos, nr));
	notify();
}

const vector<Car> CarService::getAllWishlist() {
	return cos.getAllWishlist();
}

void CarService::deleteAll() {
	cos.deleteAll();
	notify();
}

void CarService::addRandom(int cate) {
	cos.addRandom(cate);
	notify();
}

void CarService::exporthtml(string fisier) const {
	exportHtml(fisier, cos.getAllWishlist());
}


//TESTE	
void testAdd() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,repo2 };
	serv.add("a", "b", "asdf", "234e");
	const auto& cars = serv.getAll();
	assert(cars.size() == 1);
	try {
		serv.add(" ", "ceva", "ceva", "123d");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	try {
		serv.add("da", " ", "123d", "dadf");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	try {
		serv.add("da", "dada", " ", "da23");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	try {
		serv.add("dadadadad", "ceva", "ceva", " ");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}

}
void testDeleteService() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,repo2 };
	string numar = "b";
	serv.add("a", "b", "asdf", "234e");
	serv.add("b", "c", "asdf", "234e");
	assert(serv.getAll().size() == 2);
	serv.sterge(numar);
	assert(serv.getAll().size() == 1);
	assert(serv.getAll()[0].getnrInmatriculare() == "a");


}

void testModificaService() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo, valid,repo2 };
	string numar = "b";
	serv.add("a", "b", "asdf", "234e");
	serv.modifica("a", "m", "n", "123");
	assert(serv.getAll()[0].getProducator() == "m");
	assert(serv.getAll()[0].getModel() == "n");

}

void testSearchService() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo, valid,repo2 };
	serv.add("a", "b", "asdf", "234e");
	Car found = serv.cauta("a");
	assert(found.getProducator() == "b");
	assert(found.getModel() == "asdf");
	assert(found.getTip() == "234e");

}

void testFiltrari() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,repo2 };
	serv.add("a", "b", "asdf", "234e");
	serv.add("b", "b", "asdf", "24e");
	serv.add("c", "c", "asdf", "2e");
	auto listFiltered = serv.filtrareProd("b");
	assert(listFiltered.size() == 2);
	listFiltered = serv.filtrareTip("2e");
	assert(listFiltered.size() == 1);

}

void testSortari() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,repo2 };
	serv.add("b", "c", "sdf", "ebc");
	serv.add("a", "b", "asdf", "amn");
	serv.add("c", "c", "asdf", "zty");
	auto sortedList = serv.sortNr();
	assert(sortedList.size() == 3);
	assert(sortedList[0].getnrInmatriculare() == "a");
	assert(sortedList[1].getnrInmatriculare() == "b");
	assert(sortedList[2].getnrInmatriculare() == "c");

	sortedList = serv.sortTip();
	assert(sortedList[0].getTip() == "amn");
	assert(sortedList[1].getTip() == "ebc");
	assert(sortedList[2].getTip() == "zty");

	sortedList = serv.sortProdModel();
	assert(sortedList[0].getnrInmatriculare() == "a");
	assert(sortedList[1].getnrInmatriculare() == "c");
	assert(sortedList[2].getnrInmatriculare() == "b");



}
void testServiceRepo2() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,repo2 };
	serv.add("b", "c", "sdf", "ebc");
	serv.add("a", "b", "asdf", "amn");
	serv.add("c", "c", "asdf", "zty");
	serv.addToWishlist("a");
	serv.addToWishlist("b");
	assert(serv.getAllWishlist().size() == 2);
	serv.deleteAll();
	assert(serv.getAllWishlist().size() == 0);
	serv.addRandom(2);
	assert(serv.getAllWishlist().size() == 2);
}
void testUndo() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,repo2 };
	serv.add("b", "c", "sdf", "ebc");
	serv.add("a", "b", "asdf", "amn");
	serv.sterge("a");
	serv.undo();
	assert(serv.getAll().size() == 2);
	serv.addToWishlist("b");
	assert(serv.getAllWishlist().size() == 1);
	serv.undo();
	assert(serv.getAllWishlist().size() == 0);
	serv.modifica("b", "a", "a", "a");
	serv.undo();
	auto c = serv.cauta("b");
	assert(c.getProducator() == "c");
	serv.undo();
	assert(serv.getAll().size() == 1);
	serv.undo();
	assert(serv.getAll().size() == 0);
	try {
		serv.undo();
		assert(false);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Nu mai exista operatii\n");
		assert(true);
	}


}

void testExport() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,repo2 };
	serv.add("b", "c", "sdf", "ebc");
	serv.add("a", "b", "asdf", "amn");
	serv.add("c", "c", "asdf", "zty");
	serv.addRandom(2);
	serv.exporthtml("testExport.html");
	std::ifstream fin("testExport.html");
	assert(fin.is_open());
	int countLines = 0;
	while (!fin.eof()) {
		string line;
		fin >> line;
		countLines++;
	}
	fin.close();
	assert(countLines == 22);

}

void testService() {
	testAdd();
	testDeleteService();
	testModificaService();
	testSearchService();
	testFiltrari();
	testSortari();
	testServiceRepo2();
	testUndo();
	testExport();

}


