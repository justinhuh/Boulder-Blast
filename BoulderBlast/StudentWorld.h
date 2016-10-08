#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();

	int objectHere(int x, int y);
	string formatDisplay(int score, int level, int lives, int health, int ammo, unsigned int bonus);

	void killAllDead(); //kills dead objects
	void createBullet(int x, int y, int dir);
	void createKleptoBot(int x, int y);
	void createAngryKleptoBot(int x, int y);
	void createAmmo(int x, int y);
	void createExtraLife(int x, int y);
	void createRestoreHealth(int x, int y);
	void setDisplayText();
	bool isObstacle(int x, int y); //returns true if obstacle exists at x, y
	void changeFinished(); //level is finished
	Player* getPlayer(); //returns pointer to player
	BaseObject* getObject(int x, int y, int id); //returns pointer to object with matching x, y, actor ID
	BaseObject* findObject(int id); //returns pointer to object with matching ID

	int getBonus();
private:
	int m_bonus;
	bool m_finished;
	vector<BaseObject*> vObjects;
	vector<Exit*> vExits;

	Player* plr;
};

#endif // STUDENTWORLD_H_
