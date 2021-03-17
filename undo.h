#pragma once
#include "Car.h"
#include "carrepo.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
private:
	Car addedCar;
	RepoVirtual& repo;
public:
	UndoAdauga(RepoVirtual& repo, const Car& c) : repo{ repo }, addedCar{ c }{}

	void doUndo()override {
		repo.remove(addedCar.getnrInmatriculare());

	}
};

class UndoSterge :public ActiuneUndo {
private:
	Car deletedCar;
	RepoVirtual& repo;
public:
	UndoSterge(RepoVirtual& repo, const Car& c) :repo{ repo }, deletedCar{ c }{}

	void doUndo() override {
		repo.store(deletedCar);
	}
};

class UndoModifica :public ActiuneUndo {
private:
	Car modifiedCar;
	RepoVirtual& repo;
public:
	UndoModifica(RepoVirtual& repo, const Car& c) :repo{ repo }, modifiedCar{ c }{}

	void doUndo() override {
		repo.modify(modifiedCar.getnrInmatriculare(), modifiedCar.getProducator(), modifiedCar.getModel(), modifiedCar.getTip());
	}
};

class UndoWishlist :public ActiuneUndo {
private:
	string addedCar;
	CarWishlist& cos;
public:
	UndoWishlist(CarWishlist& cos, string nr) :cos{ cos }, addedCar{ nr }{}

	void doUndo() override {
		cos.deleteCar(addedCar);
	}

};
