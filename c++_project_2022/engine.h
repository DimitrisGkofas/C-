#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <curses.h>
#include <time.h>

using namespace std;

#define FLOOR_PAIR 1
#define WALL_PAIR 2
#define P_PAIR 3
#define M_PAIR 4
#define G_PAIR 5

class Object;

class Engine {
	private:
	Object *Potter;
	Object *Malfoi;
	Object *Gem;
	public:
	Engine();
	void readMap(vector<string> &map,const char *filename);
	void setChar(vector<string> &map,int x,int y,const char c);
	char getChar(const vector<string> &map,int x,int y);
	Object* getPotter();
	Object* getMalfoi();
	Object* getGem();
	bool moveChar(vector<string> &map,int x,int y,int vx,int vy,const char c);
	int getMapWidth(const vector<string> &map);
	int getMapHeight(const vector<string> &map);
	void writeMessage(const string message,int xpos,int ypos);
	void drawMap(const vector<string> &map,int xpos,int ypos);
	void initPlayers(vector<string> &map);
	void gemMotion(vector<string> &map);
	////////////////////////////////////////////////////////////////////////////////
	void add_edge(vector<int> adj[], int src, int dest);
	bool BFS(vector<int> adj[], int src, int dest, int v,int pred[], int dist[]);
	int moveToShortestDistance(const vector<string> &map,vector<int> adj[], int s,int dest, int v);
	int shortestDistance(const vector<string> &map,vector<int> adj[], int s,int dest, int v);
	////////////////////////////////////////////////////////////////////////////////
	void addEadges(const vector<string> &map,vector<int> adj[]);
	int setMapXY_MapX(const vector<string> &map,const int x,const int y);
	~Engine();
};

