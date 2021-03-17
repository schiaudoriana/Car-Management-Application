#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include <qpainter.h>
#include <qimage.h>

#include "observer.h"
#include "carservice.h"

class CosReadOnly :public QWidget,public Observer{
	CarService& serv;
public:
	CosReadOnly(CarService& serv) :serv{ serv } {
		serv.addObserver(this);
	}

	void paintEvent(QPaintEvent* ev)override {
		QPainter p{ this };
	
		auto img1 = QImage("audi.jpg");
		auto img2 = QImage("mercedes.jpg");
		auto img3 = QImage("ford.jpg");
		auto img4 = QImage("wolkswagen");
		for (auto& car : serv.getAllWishlist()) {
			int x = rand() % 400;
			int y = rand() % 400;
			if (car.getProducator() == "audi")
				p.drawImage(x, y, img1.scaled(100, 70));
			else if (car.getProducator() == "mercedes")
				p.drawImage(x, y, img2.scaled(100, 70));
			else if (car.getProducator() == "ford")
				p.drawImage(x, y, img3.scaled(100, 70));
			else if (car.getProducator() == "wolkswagen")
				p.drawImage(x, y, img4.scaled(100, 70));
			else
				p.drawRect(x, y, 80, 80);
		}
		
	}

	void update()override {
		repaint();
	}

	 ~CosReadOnly() {
		 serv.removeObserver(this);
	}

}; 