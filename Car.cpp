#include "Car.h"
#include <assert.h>


bool cmpNumar(const Car& c1, const Car& c2) {
	return c1.getnrInmatriculare() < c2.getnrInmatriculare();

}

bool cmpTip(const Car& c1, const Car& c2) {
	return c1.getTip() < c2.getTip();

}


void testCar() {
	Car c1{ "a","b","c","1123" };
	Car c2{ "d","a","b","122" };
	Car c3{ "a","4","d","24" };
	assert(cmpNumar(c1, c2) == 1);
	assert(cmpTip(c1, c2) == 1);
	//assert(c1 != c2);
	//assert(c1 == c3);
	c1.setModel("new");
	c1.setProd("new");
	c1.setTip("new");
	assert(c1.getModel() == "new");
	assert(c1.getProducator() == "new");
	assert(c1.getTip() == "new");
}