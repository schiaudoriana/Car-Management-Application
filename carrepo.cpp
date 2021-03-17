#include "carrepo.h"
#include <assert.h>
#include <algorithm>
#include <random>
#include <fstream>



const vector<Car> CarRepo::getAll()const noexcept {
	vector<Car>rez;
	//for (const auto c : cars) {
	//	rez.push_back(c.second);
	//}
	std::transform(cars.begin(), cars.end(), std::back_inserter(rez), [](const pair<string, Car>pereche) {return pereche.second; });
	return rez;
}

void CarRepo::store(const Car& c) {
	for (const auto& elem : cars) {
		if (elem.first == c.getnrInmatriculare()) {
			throw RepoException("Masina exista deja!\n\n");
		}
	}
	cars.insert(pair<string, Car>(c.getnrInmatriculare(), c));

}


void CarRepo::remove(string elem) {

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
	return;
}

void CarRepo::modify(string numar, string nouP, string nouM, string nouT) {

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
		return;

}

const Car& CarRepo::search(string numar) const {


	auto rez = std::find_if(cars.begin(), cars.end(), [numar](const auto& c) {return c.first == numar; });
	if (!(rez != cars.end())) {
		throw RepoException("Masina cu numarul dat nu exista!\n\n");

	}
	else {
		const Car& gasit = (*rez).second;
		return gasit;
	}

}


//Lista interactiva
void CarWishlist::addToWishlist(const Car& c) {
	wishlist.push_back(c);
}

const vector<Car> CarWishlist::getAllWishlist() {
	return wishlist;
}

void CarWishlist::deleteAll()noexcept {
	wishlist.clear();
	
}

void CarWishlist::addRandom(int cate) {
	if (size_t(cate) > repo.getAll().size()) {
		throw RepoException("Nu sunt suficiente masini!\n\n");
	}
	else {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> const dist(0, repo.getAll().size() - 1);
		vector<Car> dest{ repo.getAll() };
		for (int i = 0; i < cate; i++) {
			const int rndNr = dist(mt);// numar aleator intre [0,size-1]
			wishlist.push_back(dest[rndNr]);
		}
	}
	

}

void CarWishlist::deleteCar(string nr) {
	int index = 0;
	for (auto c : wishlist) {
		if (c.getnrInmatriculare() == nr)
		{
			wishlist.erase(wishlist.begin() + index);
			break;
		}
		index++;
	}
}

//CarRepoFile methods
void CarRepoFile::loadFromFile() {
	std::ifstream fin(fName);
	if (!fin.is_open()) {
		throw RepoException("Nu se poate deschide fisierul:" + fName);
	}
	while (!fin.eof()) {
		std::string nr;
		fin >> nr;
		std::string prod;
		fin >> prod;
		std::string model;
		fin >> model;
		std::string tip;
		fin >> tip;
		if (nr != "") {
			Car c{ nr.c_str(),prod.c_str(),model.c_str(),tip.c_str() };
			cars.insert(pair<string, Car>(c.getnrInmatriculare(), c));
		}
	}

	fin.close();
}

void CarRepoFile::writeToFile() {
	std::ofstream fout(fName);
	//if (!fout.is_open()) {
	//	throw RepoException("Nu se poate deschide fisierul:" + fName);
	//}
	for (auto& c : getAll()) {
		fout << c.getnrInmatriculare() << " ";
		fout << c.getProducator() << " ";
		fout << c.getModel() << " ";
		fout << c.getTip() << endl;

	}
	fout.close();
}


//CarRepoLab
const vector<Car> CarRepoLab::getAll()const noexcept {
	vector<Car>rez;
	std::transform(cars.begin(), cars.end(), std::back_inserter(rez), [](const pair<string, Car>pereche) {return pereche.second; });
	return rez;
}

void CarRepoLab::store(const Car& c) {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<>const dist(0.0, 1.0);
	auto randomnr = dist(mt);
	if (randomnr > p) {
		throw RepoException("REPO EXCEPTION-adauga\n\n");
	}
	else
		cars.insert(pair<string, Car>(c.getnrInmatriculare(), c));

}

void CarRepoLab::remove(string elem) {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<>const dist(0.0, 1.0);
	auto randomnr = dist(mt);
	if (randomnr > p) {
		throw RepoException("REPO EXCEPTION-sterge\n\n");
	}
	else {
		for (auto const& c : cars) {
			if (c.first == elem) {
				cars.erase(elem);
				break;
			}
		}
	}
}

void CarRepoLab::modify(string numar, string nouP, string nouM, string nouT) {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<>const dist(0.0, 1.0);
	auto randomnr = dist(mt);
	if (randomnr > p) {
		throw RepoException("REPO EXCEPTION-modifica\n\n");
	}
	else {
		for (auto& c : cars) {
			if (c.first == numar) {
				c.second.setModel(nouM);
				c.second.setProd(nouP);
				c.second.setTip(nouT);
			}
		}
	}

}

const Car& CarRepoLab::search(string numar) const {
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_real_distribution<>const dist(0.0, 1.0);
	auto randomnr = dist(mt);
	if (randomnr > p) {
		throw RepoException("REPO EXCEPTION-cautare\n\n");
	}
	else {
		auto rez = std::find_if(cars.begin(), cars.end(), [numar](const auto& c) {return c.first == numar; });
		if (rez != cars.end()) {
			const Car& gasit = (*rez).second;
			return gasit;
		}
		else
			return Car{ "0","0","0","0" };
	}

}




//TESTS
void testAddRepo() {

	CarRepo repo;
	Car c{ "a","b","c","12d" };
	repo.store(c);
	const auto& cars = repo.getAll();
	assert(cars.size() == 1);
	try {
		repo.store(c);
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
}

void testRemoveRepo() {
	CarRepo repo;
	string numar1 = "df";
	string numar2 = "bc";
	Car c1{ "ab","b","c","123d" };
	Car c2{ "df","d","s","12f" };
	Car c3{ "bc","ws","2","23" };
	Car c4{ "ceva","sad","Sdf","q3" };
	repo.store(c1);
	repo.store(c2);
	repo.store(c3);
	repo.store(c4);
	const auto& allCars = repo.getAll();
	assert(allCars.size() == 4);
	repo.remove("ceva");
	assert(repo.getAll().size() == 3);
	repo.remove(numar1);
	assert(repo.getAll().size() == 2);
	assert(repo.getAll()[0].getnrInmatriculare() == "ab");
	repo.remove(numar2);
	assert(repo.getAll().size() == 1);
	assert(repo.getAll()[0].getnrInmatriculare() == "ab");
	repo.remove("ab");
	assert(repo.getAll().size() == 0);
	try {
		repo.remove("c");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}


}

void testModifyRepo() {
	CarRepo repo;
	Car c1{ "ab","b","c","123d" };
	repo.store(c1);
	repo.modify("ab", "n", "p", "125f");
	const auto& allCars = repo.getAll();
	assert(allCars[0].getProducator() == "n");
	assert(allCars[0].getModel() == "p");
	assert(allCars[0].getTip() == "125f");
	try {
		repo.modify("bc", "a", "b", "12");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

}

void testSearchRepo() {
	CarRepo repo;
	Car c1{ "ab","b","c","123d" };
	repo.store(c1);
	Car found = repo.search("ab");
	assert(found.getnrInmatriculare() == "ab");
	assert(found.getProducator() == "b");
	assert(found.getModel() == "c");
	assert(found.getTip() == "123d");
	try {
		Car c3 = repo.search("c");
		assert(false);
	}
	catch (RepoException & ex) {
		assert(true);
		assert(ex.getMessage() == "Masina cu numarul dat nu exista!\n\n");
	}

}

void testRepo2() {
	CarRepo repo;
	CarWishlist repo2{ repo };
	Car c1{ "a","b","c","d" };
	Car c2{ "b","c","d","e" };
	repo.store(c1);
	repo.store(c2);
	assert(repo.getAll().size() == 2);
	repo2.addToWishlist(c1);
	assert(repo2.getAllWishlist().size() == 1);
	repo2.addToWishlist(c2);
	assert(repo2.getAllWishlist().size() == 2);
	repo2.deleteCar("b");
	assert(repo2.getAllWishlist().size() == 1);
	repo2.deleteAll();
	repo2.addRandom(1);
	assert(repo2.getAllWishlist().size() == 1);
	repo2.deleteAll();
	try {
		repo2.addRandom(5);
		assert(false);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Nu sunt suficiente masini!\n\n");
		assert(true);
	}
}

void testRepoFile() {
	std::ofstream fout("testCar.txt", std::ios::trunc);
	fout.close();
	CarRepoFile repo{ "testCar.txt" };
	repo.store(Car{ "12","ab","ab","ab" });
	repo.store(Car{ "14","bc","ab","ab" });
	repo.store(Car{ "15","cd","ab","ab" });
	assert(repo.getAll().size() == 3);
	auto c = repo.search("12");
	assert(c.getProducator() == "ab");
	repo.remove("15");
	assert(repo.getAll().size() == 2);
	try {
		repo.remove("1");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		repo.store(Car{ "12", "ceva", "sf", "asdfj" });
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	repo.modify("12", "ceva", "altceva", "ceva");
	c = repo.search("12");
	assert(c.getProducator() == "ceva");
	assert(c.getTip() == "ceva");
	try {
		repo.search("10");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		repo.modify("2", "ceva", "ceva", "ceva");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	try {
		CarRepoFile repo2{ "nou/car.txt" };
		assert(false);
	}
	catch (RepoException & ex) {
		assert(ex.getMessage() == "Nu se poate deschide fisierul:nou/car.txt");
		assert(true);
	}


}


void testRepo() {
	testAddRepo();
	testRemoveRepo();
	testModifyRepo();
	testSearchRepo();
	testRepo2();
	testRepoFile();
}