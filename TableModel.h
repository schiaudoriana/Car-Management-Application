#pragma once
#include <QAbstractTableModel>
#include "Car.h"
#include <vector>
#include <qdebug.h>

class TableModel :public QAbstractTableModel {
	std::vector<Car>cars;
public:
	TableModel(const std::vector<Car>& cars) :cars{ cars } {}

	int rowCount(const QModelIndex& parent = QModelIndex())const override {
		return cars.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex())const override {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::DisplayRole) {
			Car c = cars[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(c.getnrInmatriculare());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(c.getProducator());

			}
			else if (index.column() == 2) {
				return QString::fromStdString(c.getModel());

			}
			else if (index.column() == 3) {
				return QString::fromStdString(c.getTip());

			}
		}

		return QVariant{};
	}

	void refresh() {
		emit layoutChanged();
	}

	void setCars(const vector<Car>cars) {
		this->cars = cars;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};