#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <qmessagebox.h>
#include <QtWidgets/qcombobox.h>
#include <QTWidgets/qgridlayout.h>
#include <QtWidgets/qlabel.h>

#include "carservice.h"
#include "carrepo.h"
#include "CosGui.h"
#include "CosReadOnly.h"


class saveHtml :public QDialog {
	CarService& serv;
public:
	saveHtml(CarService& serv) :serv{ serv } {
		initGUI();
		initConnect();
	}


private:
	QLineEdit* txt = new QLineEdit;
	QPushButton* btn = new QPushButton{ "&OK" };

	void initGUI() {
		QVBoxLayout* lay = new QVBoxLayout{};
		setLayout(lay);
		lay->addWidget(new QLabel{ "Enter the name of a file to save the list to a html: \n" });
		lay->addWidget(txt);
		btn->setFixedWidth(50);
		lay->addWidget(btn, NULL, Qt::AlignCenter);

	}

	void initConnect() {
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			auto fisier = txt->text();
			serv.exporthtml(fisier.toStdString());
			close();
			});
	}
};

class WishlistGUI :public QWidget /*,public Observer*/ {
	CarService& service;
public:
	WishlistGUI(CarService& service) :service{ service } {
		initGUI();
		loadData();
		initConnect();
	}

	//void update()override {
	//	loadData();
	//}

	//~WishlistGUI() {
	//	service.removeObserver(this);
	//}

	

private:
	QListWidget* lista = new QListWidget;
	QPushButton* btnExit = new QPushButton{ "Exit" };
	QPushButton* btnAdd = new QPushButton{ "Add" };
	QPushButton* btnAddRandom = new QPushButton{ "Add random" };
	QPushButton* btnDeleteAll = new QPushButton{ "Goleste lista" };
	QPushButton* btnSave = new QPushButton{ "Save to html" };
	QLineEdit* txtNr = new QLineEdit;
	QLineEdit* txtProd = new QLineEdit;
	QLineEdit* txtModel = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtExtra = new QLineEdit{ "Enter a number" };

	void initGUI() {
		QHBoxLayout* layoutMain = new QHBoxLayout{};
		setLayout(layoutMain);


		layoutMain->addWidget(lista);

		QVBoxLayout* layoutMiddle = new QVBoxLayout{};

		QFormLayout* formLayout = new QFormLayout{};
		formLayout->addRow("Nr inmatriculare", txtNr);
		formLayout->addRow("Producator", txtProd);
		formLayout->addRow("Model", txtModel);
		formLayout->addRow("Tip", txtTip);

		layoutMiddle->addLayout(formLayout);
		layoutMiddle->addWidget(txtExtra);
		QHBoxLayout* buttons = new QHBoxLayout{};
		buttons->addWidget(btnAdd);
		buttons->addWidget(btnAddRandom);
		buttons->addWidget(btnDeleteAll);
		buttons->addWidget(btnSave);
		buttons->addWidget(btnExit);


		layoutMiddle->addLayout(buttons);

		layoutMain->addLayout(layoutMiddle);

	}

	void loadData() {
		lista->clear();
		for (const auto& car : service.getAllWishlist()) {
			lista->addItem(QString::fromStdString(car.getnrInmatriculare()));
		}
	}

	void initConnect() {
		//service.addObserver(this);
		QObject::connect(btnExit, &QPushButton::clicked, [&]() {
			close();
			});

		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			auto numar = txtNr->text();
			try {
				service.addToWishlist(numar.toStdString());
				lista->addItem(numar);

			}
			catch (RepoException) {
				QMessageBox::information(nullptr, "Warning", "Masina cu nr dat nu exista!");

			}
			});

		QObject::connect(btnDeleteAll, &QPushButton::clicked, [&]() {
			lista->clear();
			service.deleteAll();
			});

		QObject::connect(btnAddRandom, &QPushButton::clicked, [&]() {
			auto number = txtExtra->text();
			try {
				lista->clear();
				service.addRandom(number.toInt());
				for (const auto& car : service.getAllWishlist()) {
					lista->addItem(QString::fromStdString(car.getnrInmatriculare()));
				}
			}
			catch (RepoException) {
				QMessageBox::information(nullptr, "Warning", "Nu sunt suficiente masini!");
			}

			});

		QObject::connect(btnSave, &QPushButton::clicked, [&]() {
			saveHtml* htmlDialog = new saveHtml{ service };
			htmlDialog->show();

			});

		QObject::connect(lista, &QListWidget::itemSelectionChanged, [&]() {
			if (lista->selectedItems().isEmpty()) {
				//daca nu e nimic selectat golesc campurile
				txtNr->setText("");
				txtProd->setText("");
				txtModel->setText("");
				txtTip->setText("");
				return;
			}
			QListWidgetItem* currentItem = lista->selectedItems().at(0);
			txtNr->setText(currentItem->text());
			auto c = service.cauta(currentItem->text().toStdString());
			txtProd->setText(QString::fromStdString(c.getProducator()));
			txtModel->setText(QString::fromStdString(c.getModel()));
			txtTip->setText(QString::fromStdString(c.getTip()));

			});

	}


};
