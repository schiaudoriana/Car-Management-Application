#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab13_14_GUI.h"

class Lab13_14_GUI : public QMainWindow
{
    Q_OBJECT

public:
    Lab13_14_GUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab13_14_GUIClass ui;
};
