#include "engine.h"
#include "object.h"

using namespace std;

int main(int argc,char *argv[]) {
	srand(time(0));
	if(argc<2)
		return 0;
	vector<string> map;
	Engine *e=new Engine();
	e->readMap(map,argv[1]);
	
	initscr ();
	clear ();
	
	start_color();
	init_pair(FLOOR_PAIR,COLOR_YELLOW,COLOR_BLUE);
	init_pair(WALL_PAIR,COLOR_BLUE,COLOR_BLACK);
	init_pair(P_PAIR,COLOR_RED,COLOR_YELLOW);
	init_pair(M_PAIR,COLOR_RED,COLOR_GREEN);
	init_pair(G_PAIR,COLOR_RED,COLOR_CYAN);
	
	keypad (stdscr,TRUE);
	
	e->initPlayers(map);
	
	int ch=0;
	
	bool exit=false;
	
	do{
		
		if(!exit) {
			
		e->drawMap(map,10,10);
		
		ch=getch();
		int v = e->getMapWidth(map)*e->getMapHeight(map);

		vector<int> adj[v];
		e->addEadges(map,adj);
    
		int sourceP = e->setMapXY_MapX(map,e->getPotter()->getXpos(),e->getPotter()->getYpos());
		int sourceG = e->setMapXY_MapX(map,e->getGem()->getXpos(),e->getGem()->getYpos());
		int dest = e->setMapXY_MapX(map,e->getMalfoi()->getXpos(),e->getMalfoi()->getYpos());

		int move=0;
		int pdist=e->shortestDistance(map,adj, sourceP, dest, v);
		int gdist=e->shortestDistance(map,adj, sourceG, dest, v);
		
		if(pdist<0 || gdist<0) {
			e->writeMessage("Game Ended, Malfoi can't reach Potter or Gem!",10,9);
			exit=true;
		}
		
		if(pdist < gdist)
			move=e->moveToShortestDistance(map,adj, sourceP, dest, v);
		else
			move=e->moveToShortestDistance(map,adj, sourceG, dest, v);
		
		/*
		if(move==0)
			e->writeMessage("Best next move: No move",10,9);
		if(move==1)
			e->writeMessage("Best next move: Right move",10,9);
		if(move==2)
			e->writeMessage("Best next move: Left move",10,9);
		if(move==3)
			e->writeMessage("Best next move: Down move",10,9);
		if(move==4)
			e->writeMessage("Best next move: Up move",10,9);
		*/
		
		Object *p=e->getPotter();
		Object *m=e->getMalfoi();
		Object *g=e->getGem();
		
		if(ch=='a') {
			if(e->moveChar(map,p->getXpos(),p->getYpos(),-1,0,p->getName()))
				p->setXpos(p->getXpos()-1);
		}
		if(ch=='d') {
			if(e->moveChar(map,p->getXpos(),p->getYpos(),1,0,p->getName()))
				p->setXpos(p->getXpos()+1);
		}
		if(ch=='w') {
			if(e->moveChar(map,p->getXpos(),p->getYpos(),0,-1,p->getName()))
				p->setYpos(p->getYpos()-1);
		}
		if(ch=='s') {
			if(e->moveChar(map,p->getXpos(),p->getYpos(),0,1,p->getName()))
				p->setYpos(p->getYpos()+1);
		}
		
		if(move==2) {
			if(e->moveChar(map,m->getXpos(),m->getYpos(),-1,0,m->getName()))
				m->setXpos(m->getXpos()-1);
		}
		if(move==1) {
			if(e->moveChar(map,m->getXpos(),m->getYpos(),1,0,m->getName()))
				m->setXpos(m->getXpos()+1);
		}
		if(move==4) {
			if(e->moveChar(map,m->getXpos(),m->getYpos(),0,-1,m->getName()))
				m->setYpos(m->getYpos()-1);
		}
		if(move==3) {
			if(e->moveChar(map,m->getXpos(),m->getYpos(),0,1,m->getName()))
				m->setYpos(m->getYpos()+1);
		}
		
		e->gemMotion(map);
		
		if((p->getXpos()==m->getXpos() && p->getYpos()==m->getYpos() || p->getXpos()==m->getXpos()-1 && p->getYpos()==m->getYpos() ||
		p->getXpos()==m->getXpos()+1 && p->getYpos()==m->getYpos() || p->getXpos()==m->getXpos() && p->getYpos()==m->getYpos()-1 ||
		p->getXpos()==m->getXpos() && p->getYpos()==m->getYpos()+1)) {
			e->writeMessage("I catched you Potter, YOU LOSE!",10,9);
			exit=true;
		}

		if((p->getXpos()==g->getXpos() && p->getYpos()==g->getYpos())) {
			e->writeMessage("I won Malfoi, YOU LOSE!",10,9);
			exit=true;
		}
		
		if((g->getXpos()==m->getXpos() && g->getYpos()==m->getYpos())) {
			e->writeMessage("I catched the Gem Potter, YOU LOSE!",10,9);
			exit=true;
		}
		
		if(ch==27) {
			e->writeMessage("Game Ended!",10,9);
			exit=true;
		}
		
		} else {
			if(ch!=27)
				ch=getch();
		}
		
	}while(!exit || ch!=27);
	
	endwin ();
	cout<<"Hello World"<<endl;
	delete e;
	return 0;
}