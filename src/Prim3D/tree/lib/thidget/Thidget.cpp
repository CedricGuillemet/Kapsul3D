#include "Thidget.h"


Thidget::Thidget() : visible(false) {}

Thidget::~Thidget() {}

void Thidget::setVisible(bool v) {visible = v;}

bool Thidget::mouse(float, float) {return false;}
void Thidget::click(bool) {}

