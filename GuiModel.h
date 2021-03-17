#pragma once
#include <vector>
#include <qwidget.h>
#include <QtWidgets/qlabel.h>
#include <qlistwidget.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include <QtWidgets/qboxlayout.h>
#include <qgridlayout.h>
#include <qformlayout.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include "TableModel.h"
#include "carservice.h"


#include "Wishlist.h"

class CarGuiModel :public QWidget {
	CarService& service;
	TableModel* model;
	QTableView* table = new QTableView;
public:
	CarGuiModel(CarService& service) :service{ service } {
		initGui();
		//loadData();
		model = new TableModel{ service.getAll() };
		table->setModel(model);
		initConnect();
		
	}

private:

	QLineEdit* txtNr = new QLineEdit;
	QLineEdit* txtProd = new QLineEdit;
	QLineEdit* txtModel = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtExtra = new QLineEdit; //camp suplimentar pentru a stabili filtrarea

	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnAdd = new QPushButton{ "&Add" };
	QPushButton* btnDelete = new QPushButton{ "&Delete" };
	QPushButton* btnModify = new QPushButton{ "&Modify" };
	QPushButton* btnList = new QPushButton{ "&All" };
	QPushButton* btnFProd = new QPushButton{ "&Filter Producator" };
	QPushButton* btnFTip = new QPushButton{ "&Filter Tip" };
	QPushButton* btnSortNr = new QPushButton{ "Sort Numar" };
	QPushButton* btnSortTip = new QPushButton{ "Sort Tip" };
	QPushButton* btnSortProdModel = new QPushButton{ "Sort Producator+Model" };
	QPushButton* btnUndo = new QPushButton{ "Undo" };
	QPushButton* btnWishlist = new QPushButton{ "Wishlist" };
	QPushButton* btnAddCos = new QPushButton{ "Add cos" };
	QPushButton* btnAddRandom = new QPushButton{ "Add random cos" };
	QPushButton* btnDeleteCos = new QPushButton{ "Goleste cos" };
	QPushButton* btnCrud = new QPushButton{ "CosCRUD" };
	QPushButton* btnReadonly = new QPushButton{ "CosReadOnly" };

	QComboBox* comboBox = new QComboBox;

	void initGui() {
		QHBoxLayout* layoutMain = new QHBoxLayout{};
		setLayout(layoutMain);

		layoutMain->addWidget(table);

		auto layout2 = new QVBoxLayout{};
		auto layout3 = new QVBoxLayout{};
		auto formLayout = new QFormLayout;
		formLayout->addRow("Nr inmatriculare", txtNr);
		formLayout->addRow("Producator", txtProd);
		formLayout->addRow("Model", txtModel);
		formLayout->addRow("Tip", txtTip);
		formLayout->addRow("Extra field", txtExtra);
		layout3->addLayout(formLayout);

		auto buttonL = new QHBoxLayout;
		buttonL->addWidget(btnAdd);
		buttonL->addWidget(btnDelete);
		buttonL->addWidget(btnModify);
		//buttonL->addWidget(btnFProd);
		//buttonL->addWidget(btnFTip);
		layout3->addLayout(buttonL);

		auto buttonsLayout = new QHBoxLayout;
		buttonsLayout->addWidget(btnSortNr);
		buttonsLayout->addWidget(btnSortTip);
		buttonsLayout->addWidget(btnSortProdModel);

		//Grid Layout-ex lab 10
		QGridLayout* gridLayout = new QGridLayout;
		gridLayout->addWidget(btnFProd);
		gridLayout->addWidget(btnFTip);
		gridLayout->addWidget(comboBox);
		//gridLayout->addWidget(btnWishlist);
		gridLayout->addWidget(btnCrud);
		gridLayout->addWidget(btnReadonly);
		gridLayout->addWidget(btnAddCos);
		gridLayout->addWidget(btnAddRandom);
		gridLayout->addWidget(btnDeleteCos);
		gridLayout->addWidget(btnExit);

		layout2->addLayout(layout3);
		layout2->addLayout(buttonsLayout);
		layoutMain->addLayout(layout2);

		comboBox->addItem("All");
		comboBox->addItem("Undo");
		layoutMain->addLayout(gridLayout);
	}

	void loadData(std::vector<Car>cars) {
		model->setCars(cars);
		model->refresh();
	}

	void initConnect() {
		QObject::connect(btnExit, &QPushButton::clicked, [&]() {
			close();
			});

		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			auto numar = txtNr->text();
			auto prod = txtProd->text();
			auto model = txtModel->text();
			auto tip = txtTip->text();
			try {
				service.add(numar.toStdString(), prod.toStdString(), model.toStdString(), tip.toStdString());
				loadData(service.getAll());
			
				
			}
			catch (ValidateException&) {
				QMessageBox::information(nullptr, "Info", "Datele introduse nu sunt valide!");
			}
			catch (RepoException&) {
				QMessageBox::information(nullptr, "Info", "Masina cu nr dat exista deja!");
			}

			});

		QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
			auto numar = txtNr->text();
			try {
				service.sterge(numar.toStdString());
				loadData(service.getAll());
				
			}
			catch (RepoException&) {
				QMessageBox::information(nullptr, "Info", "Masina cu nr dat nu exista!");
			}
			});

		QObject::connect(btnModify, &QPushButton::clicked, [&]() {
			auto numar = txtNr->text();
			auto prod = txtProd->text();
			auto model = txtModel->text();
			auto tip = txtTip->text();
			try {
				service.modifica(numar.toStdString(), prod.toStdString(), model.toStdString(), tip.toStdString());
				loadData(service.getAll());
			}
			catch (RepoException&) {
				QMessageBox::information(nullptr, "Info", "Masina cu nr dat nu exista!");
			}

			});


		QObject::connect(btnFProd, &QPushButton::clicked, [&]() {
			auto field = txtExtra->text();
			auto filtered = service.filtrareProd(field.toStdString());
			loadData(filtered);

			});

		QObject::connect(btnFTip, &QPushButton::clicked, [&]() {
			auto field = txtExtra->text();
			auto filtered = service.filtrareTip(field.toStdString());
			loadData(filtered);

			});

		QObject::connect(btnSortTip, &QPushButton::clicked, [&]() {

			auto sorted = service.sortTip();
			loadData(sorted);
		});

		QObject::connect(btnSortNr, &QPushButton::clicked, [&]() {
			auto sorted = service.sortNr();
			loadData(sorted);
			});

		QObject::connect(btnSortProdModel, &QPushButton::clicked, [&]() {
			auto sorted = service.sortProdModel();
			loadData(sorted);

			});



		QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			if (table->selectionModel()->selectedIndexes().isEmpty()) {
				txtNr->setText("");
				txtProd->setText("");
				txtModel->setText("");
				txtTip->setText("");
				return;
			}
			int selRow = table->selectionModel()->selectedIndexes().at(0).row();
			auto cel0Index = table->model()->index(selRow, 0);
			auto cel1Index = table->model()->index(selRow, 1);
			auto cel2Index = table->model()->index(selRow, 2);
			auto cel3Index = table->model()->index(selRow, 3);
			auto cel0Val = table->model()->data(cel0Index, Qt::DisplayRole).toString();
			auto cel1Val = table->model()->data(cel1Index, Qt::DisplayRole).toString();
			auto cel2Val = table->model()->data(cel2Index, Qt::DisplayRole).toString();
			auto cel3Val = table->model()->data(cel3Index, Qt::DisplayRole).toString();
			txtNr->setText(cel0Val);
			txtProd->setText(cel1Val);
			txtModel->setText(cel2Val);
			txtTip->setText(cel3Val);

			});

		//comboBox-ex lab 10
		QObject::connect(comboBox, QOverload<int>::of(&QComboBox::activated), [&](int index) {
			if (comboBox->currentIndex() == 0) {
				loadData(service.getAll());
			}
			else
				try {
				service.undo();
				loadData(service.getAll());
			}
			catch (RepoException&) {
				QMessageBox::information(nullptr, "Info", "Nu se mai poate face undo!");
			}
			});

		QObject::connect(btnWishlist, &QPushButton::clicked, [&]() {
			auto wishlist = new WishlistGUI{ service };
			wishlist->show();
			});

		QObject::connect(btnCrud, &QPushButton::clicked, [&]() {
			auto cosCrud = new CosGuiTabel{ service };
			cosCrud->show();
			});

		QObject::connect(btnReadonly, &QPushButton::clicked, [&]() {
			auto cosReadOnly = new CosReadOnly{ service };
			cosReadOnly->show();
			});

		QObject::connect(btnAddCos, &QPushButton::clicked, [&]() {
			auto numar = txtNr->text();
			try {
				service.addToWishlist(numar.toStdString());
				
			}
			catch (RepoException) {
				QMessageBox::information(nullptr, "Warning", "Masina cu nr dat nu exista!");

			}
			});

		QObject::connect(btnAddRandom, &QPushButton::clicked, [&]() {
			auto number = txtExtra->text();
			try {
				service.addRandom(number.toInt());
			}
			catch (RepoException) {
				QMessageBox::information(nullptr, "Warning", "Nu sunt suficiente masini!");
			}
			});

		QObject::connect(btnDeleteCos, &QPushButton::clicked, [&]() {
			service.deleteAll();
			});

	
	}
};