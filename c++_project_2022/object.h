#include <string>
#include <bits/stdc++.h>
#include <curses.h>

using namespace std;

class Engine;

class Object {
	private:
	int xpos,ypos;
	char name;
	public:
	Object(const char name);
	void setXpos(int xpos);
	void setYpos(int ypos);
	int getXpos();
	int getYpos();
	char getName();
};