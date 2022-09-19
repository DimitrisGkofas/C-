#include "object.h"
#include "engine.h"

Object::Object(const char name) {
	xpos=ypos=0;
	this->name=name;
}

void Object::setXpos(int xpos) {
	this->xpos=xpos;
}

void Object::setYpos(int ypos) {
	this->ypos=ypos;
}

int Object::getXpos() {
	return xpos;
}

int Object::getYpos() {
	return ypos;
}

char Object::getName() {
	return name;
}