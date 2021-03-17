#include "validator.h"

void CarValidator::validate(const Car& c) {
	//adauga mesaj in cazul in care unul din campuri este invalid
	vector<string> msgs;
	if (c.getnrInmatriculare() == " ") msgs.push_back("Nr inmatriculare invalid! ");
	if (c.getProducator() == " ") msgs.push_back("Producator invalid! ");
	if (c.getModel() == " ") msgs.push_back("Model invalid!");
	if (c.getTip() == " ") msgs.push_back("Tip invalid! ");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}

}


//ostream& operator<<(ostream& out, const ValidateException& ex) {
//	//suprascrie operatorul <<
//	for (const auto& msg : ex.msgs) {
//		out << msg << " ";
//	}
//	return out;
//}