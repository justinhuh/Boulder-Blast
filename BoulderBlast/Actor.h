#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
#include "GraphObject.h"
#include "GameConstants.h"
#include "GameWorld.h"

class StudentWorld;

class BaseObject : public GraphObject
{
public:
	BaseObject(int id, StudentWorld* world);
	BaseObject(int id, StudentWorld* world, int x, int y);
	virtual ~BaseObject(){};

	virtual void doSomething() = 0;
	bool alive(); //returns true if alive
	void setDead(); //sets objects to dead
	virtual void damage(){};
	int random(int min, int max); //get random number

	StudentWorld* getWorld() const;
private:
	StudentWorld* myWorld;
	bool m_alive;
};

class aliveObject : public BaseObject
{
public:
	aliveObject(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	~aliveObject(){};
	virtual void doSomething(){};
	int getHealth(); //returns health
	void editHealth(int x); //changes health value
private:
	int m_health;
	Direction m_dir;
};

class Player : public aliveObject
{
public:
	Player(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	~Player(){};
	virtual void doSomething();
	virtual void damage();
	int getAmmo(); //returns ammo
	void editAmmo(int x); //changes ammo value
private:
	int m_ammo;
};

class Wall:public BaseObject
{
public:
	Wall(int id, StudentWorld* world, int x, int y);
	virtual void doSomething(){};
	virtual void damage(){};
};

class Boulder:public aliveObject
{
public:
	Boulder(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	virtual void doSomething(){};
	virtual void damage();
};

class Hole : public BaseObject
{
public:
	Hole(int id, StudentWorld* world, int x, int y);
	virtual void doSomething();
	virtual void damage(){};
};

class Jewel : public BaseObject
{
public:
	Jewel(int id, StudentWorld* world, int x, int y);
	virtual void doSomething();
	virtual void damage(){};
};

class Exit : public BaseObject
{
public:
	Exit(int id, StudentWorld* world, int x, int y);
	virtual void doSomething();
	virtual void damage(){};
};

class Bullet : public aliveObject
{
public:
	Bullet(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	virtual void doSomething();
	bool damageCheck();
};

class ExtraLife : public BaseObject
{
public:
	ExtraLife(int id, StudentWorld* world, int x, int y);
	virtual void doSomething();
	virtual void damage(){};
};

class RestoreHealth : public BaseObject
{
public:
	RestoreHealth(int id, StudentWorld* world, int x, int y);
	virtual void doSomething();
	virtual void damage(){};
};

class Ammo : public BaseObject
{
public:
	Ammo(int id, StudentWorld* world, int x, int y);
	virtual void doSomething();
	virtual void damage(){};
};

class Robot : public aliveObject
{
public:
	Robot(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	virtual void doSomething() = 0;
	virtual void damage() = 0;
	bool CanFire(); //fires bullet if possible and returns true
	virtual void move(Direction dir); //moves in one direction until obstacle found

	int getTicks();
	void editTicks(int x);
	int getTickAction();
private:
	int m_ticks;
	int m_tickAction;
};

class Snarlbot : public Robot
{
public:
	Snarlbot(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	virtual void doSomething();
	virtual void damage();
};

class KleptoBot : public Robot
{
public:
	KleptoBot(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	virtual void doSomething();
	virtual void damage();
	virtual void move(Direction dir);
	void direction(); //changes direction 
	bool pickup(); //pick up goodies if possible
	int getDistance(); //return distance
	int getDcount(); //return distance count
	int getGoodieType(); //return goodie type
private:
	int m_distance;
	int m_distanceCount;
	int m_goodieType;
};

class AngryKleptoBot : public KleptoBot
{
public:
	AngryKleptoBot(int id, StudentWorld* world, int x, int y, Direction dir, int health);
	virtual void doSomething();
};

class KleptoBotFactory : public BaseObject
{
public:
	KleptoBotFactory(int id, StudentWorld* world, int x, int y, int type);
	virtual void doSomething();
	virtual void damage(){};
	int getRobotType(); //return robot type
	int botCount(); //finds number of bots in specifed area
private:
	int m_robotType;
};
#endif // ACTOR_H_