#pragma once
#include <vector>
#include <string>
#include "Car.h"
#include <fstream>



void exportHtml(const std::string& fisier, const std::vector<Car>wishlist) {
	std::ofstream fout(fisier);
	fout << "====LISTA MASINI====" << " <p> ";
	fout << "<html><body>" << endl;
	fout << "<table border=\"1\" style=\"width:100 % \">" << endl;
	for (auto& elem : wishlist) {
		fout << "<tr>";
		fout << "<td>" << elem.getnrInmatriculare() << "</td>" << endl;
		fout << "<td>" << elem.getProducator() << "</td>" << endl;
		fout << "<td>" << elem.getModel() << "</td>" << endl;
		fout << "<td>" << elem.getTip() << "</td>" << endl;
		fout << "</tr>" << endl;
	}
	fout << "</table>" << endl;
	fout << "</body></html>" << endl;
	fout.close();
}
