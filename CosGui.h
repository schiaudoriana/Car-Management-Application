#include <qwidget.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>

#include "observer.h"
#include "carservice.h"

using std::vector;

class CosGuiTabel :public QWidget, public Observer {
	CarService& serv;
public:
	CosGuiTabel(CarService&serv) :serv{ serv } {
		initGui();
		connectSignals();
		loadTable(serv.getAllWishlist());

	}

	void update()override {
		loadTable(serv.getAllWishlist());
	}

	~CosGuiTabel() {
		serv.removeObserver(this);
	}

private:
	QTableWidget* lst=new QTableWidget;
	QPushButton* btnDel = new QPushButton{ "Goleste cos" };
	QPushButton* btnGenerate=new QPushButton{ "Adauga random" };
	QPushButton* btnAdd = new QPushButton{ "Adauga" };
	QLineEdit* txt = new QLineEdit;

	void initGui() {
		QHBoxLayout* layout = new QHBoxLayout;
		setLayout(layout);
		layout->addWidget(lst);
		layout->addWidget(txt);
		layout->addWidget(btnDel);
		layout->addWidget(btnAdd);
		layout->addWidget(btnGenerate);
	}

	void connectSignals() {
		serv.addObserver(this);
		QObject::connect(btnDel, &QPushButton::clicked, [&]() {
			serv.deleteAll();
			loadTable(serv.getAllWishlist());
			});
		QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
			try {
				int numar = txt->text().toInt();
				serv.addRandom(numar);
			}
			catch (RepoException&) {
				QMessageBox::information(nullptr, "info", "nu sunt suficiente masini");
			}
			});

		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			auto numar = txt->text();
			try {
				serv.addToWishlist(numar.toStdString());
				loadTable(serv.getAllWishlist());

			}
			catch (RepoException) {
				QMessageBox::information(nullptr, "Warning", "Masina cu nr dat nu exista!");

			}
			});
	}

	void loadTable(const vector<Car>&cars) {
		lst->clear();
		lst->setRowCount(cars.size());
		lst->setColumnCount(4);
		for (int i = 0; i < cars.size(); i++) {
			lst->setItem(i, 0, new QTableWidgetItem(cars[i].getnrInmatriculare().c_str()));
			lst->setItem(i, 1, new QTableWidgetItem(cars[i].getProducator().c_str()));
			lst->setItem(i, 2, new QTableWidgetItem(cars[i].getModel().c_str()));
			lst->setItem(i, 3, new QTableWidgetItem(cars[i].getTip().c_str()));

		}

	}
};
