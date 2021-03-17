#include "Lab13_14_GUI.h"
#include <QtWidgets/QApplication>

#include "carrepo.h"
#include "carservice.h"
#include "validator.h"
#include "Car.h"
#include "GUI.h"
#include "GuiModel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	CarRepoFile repo{ "cars.txt" };
	CarWishlist cos{ repo };
	CarValidator valid;
	CarService serv{ repo,valid,cos };
	//CarGUI gui{ serv };
	//gui.show();
	CarGuiModel guimodel{ serv };
	guimodel.show();

    return a.exec();
}
