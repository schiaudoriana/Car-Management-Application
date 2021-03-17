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

#include "carservice.h"
#include "Wishlist.h"


class CarGUI :public QWidget {
	CarService& service;
public:
	CarGUI(CarService& service) :service{ service } {
		initGUI();
		loadData();
		initConnect();
		//adaugaButoane(service.getAll());
	}

private:
	QListWidget* lst = new QListWidget;
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
	QPushButton* btnCrud = new QPushButton{ "CosCRUD" };
	QPushButton* btnReadonly = new QPushButton{ "CosReadOnly" };


	QComboBox* comboBox = new QComboBox;

	QWidget* btnDyn = new QWidget;
	QVBoxLayout* lyBtnDy = new QVBoxLayout;

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
				loadData();
				for (int i = 0; i < lyBtnDy->count(); ++i)
				{
					QWidget* widget = lyBtnDy->itemAt(i)->widget();
					if (widget != NULL)
					{
						widget->setVisible(false);
					}
				}
				//adaugaButoane(service.getAll());
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
				loadData();
				for (int i = 0; i < lyBtnDy->count(); ++i)
				{
					QWidget* widget = lyBtnDy->itemAt(i)->widget();
					if (widget != NULL)
					{
						widget->setVisible(false);
					}
				}
				//adaugaButoane(service.getAll());
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
				loadData();
			}
			catch (RepoException&) {
				QMessageBox::information(nullptr, "Info", "Masina cu nr dat nu exista!");
			}

			});


		QObject::connect(btnFProd, &QPushButton::clicked, [&]() {
			lst->clear();
			auto field = txtExtra->text();
			auto filtered = service.filtrareProd(field.toStdString());
			for (auto& c : filtered) {
				lst->addItem(QString::fromStdString(c.getnrInmatriculare()));
			}
			});

		QObject::connect(btnFTip, &QPushButton::clicked, [&]() {
			lst->clear();
			auto field = txtExtra->text();
			auto filtered = service.filtrareTip(field.toStdString());
			for (auto& c : filtered) {
				lst->addItem(QString::fromStdString(c.getnrInmatriculare()));
			}
			});

		QObject::connect(btnSortTip, &QPushButton::clicked, [&]() {
			lst->clear();
			auto sorted = service.sortTip();
			for (auto& c : sorted) {
				lst->addItem(QString::fromStdString(c.getnrInmatriculare()));
			}
			for (int i = 0; i < lyBtnDy->count(); ++i)
			{
				QWidget* widget = lyBtnDy->itemAt(i)->widget();
				if (widget != NULL)
				{
					widget->setVisible(false);
				}
			}
			//adaugaButoane(sorted);
			});

		QObject::connect(btnSortNr, &QPushButton::clicked, [&]() {
			lst->clear();
			auto sorted = service.sortNr();
			for (auto& c : sorted) {
				lst->addItem(QString::fromStdString(c.getnrInmatriculare()));
			}
			for (int i = 0; i < lyBtnDy->count(); ++i)
			{
				QWidget* widget = lyBtnDy->itemAt(i)->widget();
				if (widget != NULL)
				{
					widget->setVisible(false);
				}
			}
			//adaugaButoane(sorted);
			});

		QObject::connect(btnSortProdModel, &QPushButton::clicked, [&]() {
			lst->clear();
			auto sorted = service.sortProdModel();
			for (auto& c : sorted) {
				lst->addItem(QString::fromStdString(c.getnrInmatriculare()));
			}
			for (int i = 0; i < lyBtnDy->count(); ++i)
			{
				QWidget* widget = lyBtnDy->itemAt(i)->widget();
				if (widget != NULL)
				{
					widget->setVisible(false);
				}
			}
			//adaugaButoane(sorted);
			});



		QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
			if (lst->selectedItems().isEmpty()) {
				//daca nu e nimic selectat golesc campurile
				txtNr->setText("");
				txtProd->setText("");
				txtModel->setText("");
				txtTip->setText("");
				return;
			}
			QListWidgetItem* currentItem = lst->selectedItems().at(0);
			txtNr->setText(currentItem->text());
			auto c = service.cauta(currentItem->text().toStdString());
			txtProd->setText(QString::fromStdString(c.getProducator()));
			txtModel->setText(QString::fromStdString(c.getModel()));
			txtTip->setText(QString::fromStdString(c.getTip()));

			});

		//comboBox-ex lab 10
		QObject::connect(comboBox, QOverload<int>::of(&QComboBox::activated), [&](int index) {
			if (comboBox->currentIndex() == 0) {
				loadData();
			}
			else
				try {
				service.undo();
				loadData();
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

	}

	//adauga butoane dinamic
	void adaugaButoane(const vector<Car>& cars) {
		for (const auto& c : cars) {
			auto btn = new QPushButton{ QString::fromStdString(c.getnrInmatriculare()) };
			lyBtnDy->addWidget(btn);
			QObject::connect(btn, &QPushButton::clicked, [this, btn, c]() {
				service.sterge(c.getnrInmatriculare());
				loadData();
				for (int i = 0; i < lyBtnDy->count(); ++i)
				{
					QWidget* widget = lyBtnDy->itemAt(i)->widget();
					if (widget != NULL)
					{
						widget->setVisible(false);
					}
				}
				adaugaButoane(service.getAll());
				//lyBtnDy->removeWidget(btn);
				});
		}
	}


	void loadData() {
		lst->clear();
		for (const auto& car : service.getAll()) {
			lst->addItem(QString::fromStdString(car.getnrInmatriculare()));
		}
	}

	void initGUI() {
		QHBoxLayout* layoutMain = new QHBoxLayout{};
		setLayout(layoutMain);

		layoutMain->addWidget(lst);

		auto layout2 = new QVBoxLayout{};
		auto layout3 = new QVBoxLayout{};
		auto formLayout = new QFormLayout;
		formLayout->addRow("Nr inmatriculare", txtNr);
		formLayout->addRow("Producator", txtProd);
		formLayout->addRow("Model", txtModel);
		formLayout->addRow("Tip", txtTip);
		formLayout->addRow("Extra field(filter)", txtExtra);
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
		gridLayout->addWidget(btnExit);

		layout2->addLayout(layout3);
		layout2->addLayout(buttonsLayout);
		layoutMain->addLayout(layout2);

		comboBox->addItem("All");
		comboBox->addItem("Undo");
		layoutMain->addLayout(gridLayout);


		btnDyn->setLayout(lyBtnDy);
		layoutMain->addWidget(btnDyn);
	}

};

