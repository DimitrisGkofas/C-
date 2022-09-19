#include "engine.h"
#include "object.h"

Engine::Engine() {
	
}

void Engine::readMap(vector<string> &map,const char *filename) {
    fstream newfile;
    newfile.open(filename,ios::in);
    if (newfile.is_open()) {
        string line;
		int i=0;
        while(getline(newfile,line)) {
            map.push_back(line);
			i++;
		}
        newfile.close();
    }
}

void Engine::setChar(vector<string> &map,int x,int y,const char c) {
	map[y].at(x)=c;
}

char Engine::getChar(const vector<string> &map,int x,int y) {
    return map[y].at(x);
}

Object* Engine::getPotter() {
	return Potter;
}

Object* Engine::getMalfoi() {
	return Malfoi;
}

Object* Engine::getGem() {
	return Gem;
}

bool Engine::moveChar(vector<string> &map,int x,int y,int vx,int vy,const char c) {
	if(!(getChar(map,x+vx,y+vy)=='*')) {
		setChar(map,x,y,'.');
		setChar(map,x+vx,y+vy,c);
		return true;
	} else
		return false;
}

int Engine::getMapWidth(const vector<string> &map) {
    return map[0].size();
}

int Engine::getMapHeight(const vector<string> &map) {
    return map.size();
}

void Engine::writeMessage(const string message,int xpos,int ypos) {
	for(int i=0;i<message.size();i++)
		mvaddch(ypos,i+xpos,message.at(i));
}

void Engine::drawMap(const vector<string> &map,int xpos,int ypos) {
	//cout << "The Map:" << endl;
	//for(int i=0;i<getMapHeight(map);i++)
		//cout << map[i] << endl;
	
	for(int i=0;i<getMapWidth(map);i++) {
		for(int j=0;j<getMapHeight(map);j++) {
			char c=getChar(map,i,j);
			//floor
			if(c==' ' || c=='.') {
				attron(COLOR_PAIR(FLOOR_PAIR));
				mvaddch(j+ypos,i+xpos,c);
				attroff(COLOR_PAIR(FLOOR_PAIR));
			}
			//wall
			if(c=='*') {
				attron(COLOR_PAIR(WALL_PAIR));
				mvaddch(j+ypos,i+xpos,c);
				attroff(COLOR_PAIR(WALL_PAIR));
			}
			//potter
			if(c==Potter->getName()) {
				attron(COLOR_PAIR(P_PAIR));
				mvaddch(j+ypos,i+xpos,c);
				attroff(COLOR_PAIR(P_PAIR));
			}
			//malfoi
			if(c==Malfoi->getName()) {
				attron(COLOR_PAIR(M_PAIR));
				mvaddch(j+ypos,i+xpos,c);
				attroff(COLOR_PAIR(M_PAIR));
			}
			//gem
			if(c==Gem->getName()) {
				attron(COLOR_PAIR(G_PAIR));
				mvaddch(j+ypos,i+xpos,c);
				attroff(COLOR_PAIR(G_PAIR));
			}
		}
	}
}

void Engine::initPlayers(vector<string> &map) {
	
	Potter=new Object('M');
	Malfoi=new Object('L');
	Gem=new Object('G');
	do {
		Potter->setXpos(rand()%getMapWidth(map));
		Potter->setYpos(rand()%getMapHeight(map));
	} while(getChar(map,Potter->getXpos(),Potter->getYpos())!=' ');
	do {
		Malfoi->setXpos(rand()%getMapWidth(map));
		Malfoi->setYpos(rand()%getMapHeight(map));
	} while(getChar(map,Malfoi->getXpos(),Malfoi->getYpos())!=' ');
	do {
		Gem->setXpos(rand()%getMapWidth(map));
		Gem->setYpos(rand()%getMapHeight(map));
	} while(getChar(map,Gem->getXpos(),Gem->getYpos())!=' ');
	
	setChar(map,Potter->getXpos(),Potter->getYpos(),Potter->getName());
	setChar(map,Malfoi->getXpos(),Malfoi->getYpos(),Malfoi->getName());
	setChar(map,Gem->getXpos(),Gem->getYpos(),Gem->getName());
	
}

void Engine::gemMotion(vector<string> &map) {
	
	//srand(time(0));
	
	if(!(rand()%15)) {
		
		setChar(map,Gem->getXpos(),Gem->getYpos(),' ');
		
		do {
			Gem->setXpos(rand()%getMapWidth(map));
			Gem->setYpos(rand()%getMapHeight(map));
		} while(getChar(map,Gem->getXpos(),Gem->getYpos())!=' ');
	
		setChar(map,Gem->getXpos(),Gem->getYpos(),Gem->getName());
	}
}
////////////////////////////////////////////////////////////////////////////////
void Engine::add_edge(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}

bool Engine::BFS(vector<int> adj[], int src, int dest, int v,
         int pred[], int dist[])
{
    list<int> queue;
 
    bool visited[v];
 
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}

int Engine::moveToShortestDistance(const vector<string> &map,vector<int> adj[], int s,int dest, int v)
{
	int mapWidth=getMapWidth(map);
	
	int move=0;

    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false)
        return move;
 
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
 
	if(mapWidth) {
		int x0 = path[0] % mapWidth;
		int y0 = ( path[0] - x0 ) / mapWidth;
		int x1 = path[1] % mapWidth;
		int y1 = ( path[1] - x1 ) / mapWidth;
		if((x1-x0)==1)
			move=1;
		if((x1-x0)==-1)
			move=2;
		if((y1-y0)==1)
			move=3;
		if((y1-y0)==-1)
			move=4;
	}
	return move;
}

int Engine::shortestDistance(const vector<string> &map,vector<int> adj[], int s,int dest, int v)
{
	int mapWidth=getMapWidth(map);
	
	int pdist=-1;

    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false)
        return pdist;

	pdist=dist[dest];
	return pdist;
}
////////////////////////////////////////////////////////////////////////////////
void Engine::addEadges(const vector<string> &map,vector<int> adj[]) {
	int mapWidth=getMapWidth(map);
	int mapHeight=getMapHeight(map);
    for(int i=1;i<mapWidth-1;i++) {
        for(int j=1;j<mapHeight-1;j++) {
            if(getChar(map,i,j)!='*') {
                int vId=i+mapWidth*j;
                if(getChar(map,i+1,j)!='*')
                    add_edge(adj, vId, vId+1);
                if(getChar(map,i,j+1)!='*')
                    add_edge(adj, vId, vId+mapWidth);
            }
        }
    }
}

int Engine::setMapXY_MapX(const vector<string> &map,const int x,const int y) {
	return x+getMapWidth(map)*y;
}

Engine::~Engine() {
	delete Potter;
	delete Malfoi;
	delete Gem;
}