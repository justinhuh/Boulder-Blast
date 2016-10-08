#include "StudentWorld.h"
#include <string>
#include "Level.h"
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir), m_bonus(1000), m_finished(false)
{}

int StudentWorld::init()
{
	m_bonus = 1000;
	m_finished = false;

	//format level number
	ostringstream oss;
	int level = getLevel();
	oss.fill('0');
	oss << setw(2) << level;
	string finlevel = oss.str();

	//load level.dat
	Level lev(assetDirectory());
	Level::LoadResult result = lev.loadLevel("level" + finlevel + ".dat");
	if (result == Level::load_fail_file_not_found || level > 99)	//player won
	{
		return GWSTATUS_PLAYER_WON;
	}
	else if (result == Level::load_fail_bad_format) //level error
	{
		return GWSTATUS_LEVEL_ERROR;
	}
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level\n";

		//loop through all x and y coordinates and create appropriate objects
		for (int x = 0; x < 15; x++)
		{
			for (int y = 0; y < 15; y++)
			{
				Level::MazeEntry ge = lev.getContentsOf(x, y);
				switch (ge)
				{
				case Level::player:
				{
					plr = new Player(IID_PLAYER, this, x, y, GraphObject::right, 20);
					vObjects.push_back(plr);
					break;
				}
				case Level::wall:
				{
					vObjects.push_back(new Wall(IID_WALL, this, x, y));
					break;
				}
				case Level::boulder:
				{
					vObjects.push_back(new Boulder(IID_BOULDER, this, x, y, GraphObject::none, 10));
					break;
				}
				case Level::hole:
				{
					vObjects.push_back(new Hole(IID_HOLE, this, x, y));
					break;
				}
				case Level::jewel:
				{
					vObjects.push_back(new Jewel(IID_JEWEL, this, x, y));
					break;
				}
				case Level::exit:
				{
					vObjects.push_back(new Exit(IID_EXIT, this, x, y));
					break;
				}
				case Level::extra_life:
				{
					vObjects.push_back(new ExtraLife(IID_EXTRA_LIFE, this, x, y));
					break;
				}
				case Level::restore_health:
				{
					vObjects.push_back(new RestoreHealth(IID_RESTORE_HEALTH, this, x, y));
					break;
				}
				case Level::ammo:
				{
					vObjects.push_back(new Ammo(IID_AMMO, this, x, y));
					break;
				}
				case Level::horiz_snarlbot:
				{
					vObjects.push_back(new Snarlbot(IID_SNARLBOT, this, x, y, GraphObject::right, 10));
					break;
				}
				case Level::vert_snarlbot:
				{
					vObjects.push_back(new Snarlbot(IID_SNARLBOT, this, x, y, GraphObject::down, 10));
					break;
				}
				case Level::kleptobot_factory:
				{
					vObjects.push_back(new KleptoBotFactory(IID_ROBOT_FACTORY, this, x, y, 1));
					break;				
				}
				case Level::angry_kleptobot_factory:
				{
					vObjects.push_back(new KleptoBotFactory(IID_ROBOT_FACTORY, this, x, y, 2));
					break;
				}
				default:
					break;
				}
			}
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	int check = 0;
	
	//stat line updated
	setDisplayText();

	//all objects do something
	for (int x = 0; x < vObjects.size(); x++)
	{
		vObjects[x]->doSomething();
		if (!getPlayer()->alive()) //player died
		{
			decLives();
			return GWSTATUS_PLAYER_DIED;
		}
		if (m_finished) //level finished
		{
			return GWSTATUS_FINISHED_LEVEL;
		}
	}

	//kill all dead
    killAllDead();

	//exit appears if all jewels are gone
	for (int a = 0; a < vObjects.size(); a++)
	{
		if (getObject(vObjects[a]->getX(), vObjects[a]->getY(), IID_JEWEL) != nullptr)
			check = 1;
	}
	if (check == 0 && findObject(IID_EXIT)->isVisible() == false)
	{
		findObject(IID_EXIT)->setVisible(true);
		playSound(SOUND_REVEAL_EXIT);
	}

	//bonus countdown
	if (m_bonus > 0)
		m_bonus--;

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::setDisplayText()
{
	int score = getScore();
	int level = getLevel();
	unsigned int bonus = m_bonus;
	int lives = getLives();

	string s = formatDisplay(score, level, lives, getPlayer()->getHealth(), getPlayer()->getAmmo(), m_bonus); //format properly
	setGameStatText(s);
}

string StudentWorld::formatDisplay(int score, int level, int lives, int health, int ammo, unsigned int bonus)
{
	//to format health
	ostringstream oss;
	double hlt = (health/20.0) * 100;
	oss.fill(' ');
	oss << setw(3) << hlt;
	string finhlt = oss.str();
	
	//to format score
	ostringstream oss2;
	int sc = score;
	oss2.fill('0');
	oss2 << setw(7) << sc;
	string finsc = oss2.str();

	//to format level
	ostringstream oss3;
	int lv = level;
	oss3.fill('0');
	oss3 << setw(2) << lv;
	string finlv = oss3.str();

	//to format lives
	ostringstream oss4;
	int lvs = lives;
	oss4.fill(' ');
	oss4 << setw(2) << lvs;
	string finlvs = oss4.str();

	//to format ammo
	ostringstream oss5;
	int am = ammo;
	oss5.fill(' ');
	oss5 << setw(3) << am;
	string finam = oss5.str();

	//to format bonus
	ostringstream oss6;
	int bo = m_bonus;
	oss6.fill(' ');
	oss6 << setw(4) << bo;
	string finbo = oss6.str();

	return "Score: " + finsc + "  Level: " + finlv + "  Lives: " + finlvs + "  Health: " + finhlt + "%  Ammo: " + finam + "  Bonus: " + finbo;
}

int StudentWorld::objectHere(int x, int y)
{
	//returns 1 if object is found
	for (int a = 0; a < vObjects.size(); a++)
	{
		if (vObjects[a]->getX() == x && vObjects[a]->getY() == y)
			return 1;
	}
	return 0;
}

BaseObject* StudentWorld::getObject(int x, int y, int id)
{
	//returns pointer to object with matching x, y and object ID
	for (int z = 0; z < vObjects.size(); z++)
	{
		if (vObjects[z]->getID() == id)
		{
			if (vObjects[z]->getX() == x && vObjects[z]->getY() == y)
			{
				return vObjects[z];
			}
		}
	}
	return nullptr;
}

void StudentWorld::cleanUp()
{
	//delete objects
	for (int x = 0; x < vObjects.size(); x++)
	{
		delete vObjects[x];
	}
	vObjects.clear(); //clear vector
}

void StudentWorld::killAllDead()
{
	//if object is dead, delete it
	for (int x = 0; x < vObjects.size(); x++)
	{
		if (!vObjects[x]->alive())
		{
			delete vObjects[x];
			vObjects.erase(vObjects.begin() + x);
		}
	}
	if (!plr->alive())
		delete plr;
}

Player* StudentWorld::getPlayer()
{
	return plr;
}

void StudentWorld::createBullet(int x, int y, int dir)
{
	//creates bullet based on direction
	if (dir == 0)
	{
		vObjects.push_back(new Bullet(IID_BULLET, this, x, y, GraphObject::left, 0));
		return;
	}
	else if (dir == 1)
	{
		vObjects.push_back(new Bullet(IID_BULLET, this, x, y, GraphObject::right, 0));
		return;
	}
	else if (dir == 2)
	{
		vObjects.push_back(new Bullet(IID_BULLET, this, x, y, GraphObject::up, 0));
		return;
	}
	else if (dir == 3)
	{
		vObjects.push_back(new Bullet(IID_BULLET, this, x, y, GraphObject::down, 0));
		return;
	}
}

int StudentWorld::getBonus()
{
	return m_bonus;
}

BaseObject* StudentWorld::findObject(int id)
{
	//returns pointer to object with matching object ID
	for (int a = 0; a < vObjects.size(); a++)
	{
		if (vObjects[a]->getID() == id)
			return vObjects[a];
	}
	return nullptr;
}

bool StudentWorld::isObstacle(int x, int y)
{
	//checks for these obstacles and returns true if found
	if (getObject(x, y, IID_BOULDER) != nullptr)
		return true;
	if (getObject(x, y, IID_WALL) != nullptr)
		return true;
	if (getObject(x, y, IID_SNARLBOT) != nullptr)
		return true;
	if (getObject(x, y, IID_HOLE) != nullptr)
		return true;
	if (getObject(x, y, IID_ROBOT_FACTORY) != nullptr)
		return true;
	if (getObject(x, y, IID_KLEPTOBOT) != nullptr)
		return true;
	if (getObject(x, y, IID_ANGRY_KLEPTOBOT) != nullptr)
		return true;

	return false;
}

void StudentWorld::changeFinished() //notifies student world that level is finished
{
	m_finished = true;
}

//create kleptobot
void StudentWorld::createKleptoBot(int x, int y)
{
	vObjects.push_back(new KleptoBot(IID_KLEPTOBOT, this, x, y, GraphObject::right, 5));
}

//create ammo pack
void StudentWorld::createAmmo(int x, int y)
{
	vObjects.push_back(new Ammo(IID_AMMO, this, x, y));
}

//create extra life
void StudentWorld::createExtraLife(int x, int y)
{
	vObjects.push_back(new Ammo(IID_EXTRA_LIFE, this, x, y));
}

//create restore health
void StudentWorld::createRestoreHealth(int x, int y)
{
	vObjects.push_back(new Ammo(IID_RESTORE_HEALTH, this, x, y));
}

//create angry kleptobot
void StudentWorld::createAngryKleptoBot(int x, int y)
{
	vObjects.push_back(new AngryKleptoBot(IID_ANGRY_KLEPTOBOT, this, x, y, GraphObject::right, 8));
}

StudentWorld::~StudentWorld()
{
	StudentWorld::cleanUp();
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
