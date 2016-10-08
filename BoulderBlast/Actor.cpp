#include "Actor.h"
#include "StudentWorld.h"
#include  "Level.h" 

//BASE OBJECT
BaseObject::BaseObject(int id, StudentWorld* world, int x, int y) : GraphObject(id, x, y), myWorld(world), m_alive(true)
{
	setVisible(true);
}
bool BaseObject::alive()
{
	return m_alive;
}
void BaseObject::setDead()
{
	m_alive = false;
}
StudentWorld* BaseObject::getWorld() const
{
	return myWorld;
}

//ALIVE OBJECT
aliveObject::aliveObject(int id, StudentWorld* world, int x, int y, Direction dir, int health) : BaseObject(id, world, x, y), m_health(health)
{
	aliveObject::setDirection(dir);
}

int aliveObject::getHealth()
{
	return m_health;
}

void aliveObject::editHealth(int x)
{
	if (m_health + x >= 20) //max health = 20
		m_health = 20;
	else
		m_health += x;
}

//PLAYER
Player::Player(int id, StudentWorld* world, int x, int y, Direction dir, int health) : aliveObject(id, world, x, y, dir, health), m_ammo(20)
{}

int Player::getAmmo()
{
	return m_ammo;
}

void Player::editAmmo(int x)
{
	if (m_ammo + x <= 0)
		m_ammo = 0;
	else
		m_ammo += x;
}

void Player::doSomething()
{	
	int ch;
	int x, y;
	if (!alive())
		return;
	//USER PRESSES KEY
	if (getWorld()->getKey(ch)) //moves player based on key pres
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			x = Player::getX();
			y = Player::getY();
			Player::setDirection(Direction::left);
			if ((getWorld()->objectHere(x - 1, y) == 0
				|| getWorld()->getObject(x - 1, y, IID_JEWEL) != nullptr
				|| getWorld()->getObject(x - 1, y, IID_EXTRA_LIFE) != nullptr
				|| getWorld()->getObject(x - 1, y, IID_RESTORE_HEALTH) != nullptr
				|| getWorld()->getObject(x - 1, y, IID_AMMO) != nullptr
				|| getWorld()->getObject(x - 1, y, IID_EXIT) != nullptr) 
				&& !(getWorld()->getObject(x - 1, y, IID_SNARLBOT) != nullptr)
				&& !(getWorld()->getObject(x - 1, y, IID_KLEPTOBOT) != nullptr)
				&& !(getWorld()->getObject(x - 1, y, IID_ANGRY_KLEPTOBOT) != nullptr))
			{
				Player::moveTo(x - 1, y);
			}

			//ROCK INTO HOLE
			if ((getWorld()->getObject(x - 1, y, IID_BOULDER) != nullptr) && getWorld()->getObject(x - 2, y, IID_HOLE) != nullptr)
			{
				getWorld()->getObject(x - 1, y, IID_BOULDER)->moveTo(x - 2, y);
				Player::moveTo(x - 1, y);
			}

			//MOVING A ROCK
			else if ((getWorld()->getObject(x - 1, y, IID_BOULDER) != nullptr) && getWorld()->objectHere(x - 2, y) == 0)
			{
				getWorld()->getObject(x - 1, y, IID_BOULDER)->moveTo(x - 2, y);
				Player::moveTo(x - 1, y);
			}
			
			break;

		case KEY_PRESS_RIGHT:
			x = Player::getX();
			y = Player::getY();
			Player::setDirection(Direction::right);
			if ((getWorld()->objectHere(x + 1, y) == 0
				|| getWorld()->getObject(x + 1, y, IID_JEWEL) != nullptr
				|| getWorld()->getObject(x + 1, y, IID_EXTRA_LIFE) != nullptr
				|| getWorld()->getObject(x + 1, y, IID_RESTORE_HEALTH) != nullptr
				|| getWorld()->getObject(x + 1, y, IID_AMMO) != nullptr
				|| getWorld()->getObject(x + 1, y, IID_EXIT) != nullptr)
				&& !(getWorld()->getObject(x + 1, y, IID_SNARLBOT) != nullptr)
				&& !(getWorld()->getObject(x + 1, y, IID_KLEPTOBOT) != nullptr)
				&& !(getWorld()->getObject(x + 1, y, IID_ANGRY_KLEPTOBOT) != nullptr))
				
			{
				Player::moveTo(x + 1, y);
			}

			//ROCK INTO HOLE
			if ((getWorld()->getObject(x + 1, y, IID_BOULDER) != nullptr) && getWorld()->getObject(x + 2, y, IID_HOLE) != nullptr)
			{
				getWorld()->getObject(x + 1, y, IID_BOULDER)->moveTo(x + 2, y);
				Player::moveTo(x + 1, y);
			}

			//MOVING A ROCK
			else if ((getWorld()->getObject(x + 1, y, IID_BOULDER) != nullptr) && getWorld()->objectHere(x + 2, y) == 0)
			{
				getWorld()->getObject(x + 1, y, IID_BOULDER)->moveTo(x + 2, y);
				Player::moveTo(x + 1, y);
			}
			break;

		case KEY_PRESS_UP:
			x = Player::getX();
			y = Player::getY();
			Player::setDirection(Direction::up);
			if ((getWorld()->objectHere(x, y + 1) == 0
				|| getWorld()->getObject(x, y + 1, IID_JEWEL) != nullptr
				|| getWorld()->getObject(x, y + 1, IID_EXTRA_LIFE) != nullptr
				|| getWorld()->getObject(x, y + 1, IID_RESTORE_HEALTH) != nullptr
				|| getWorld()->getObject(x, y + 1, IID_AMMO) != nullptr
				|| getWorld()->getObject(x, y + 1, IID_EXIT) != nullptr)
				&& !(getWorld()->getObject(x, y + 1, IID_SNARLBOT) != nullptr)
				&& !(getWorld()->getObject(x, y + 1, IID_KLEPTOBOT) != nullptr)
				&& !(getWorld()->getObject(x, y + 1, IID_ANGRY_KLEPTOBOT) != nullptr))
			{
				Player::moveTo(x, y + 1);
			}

			//ROCK INTO HOLE
			if ((getWorld()->getObject(x, y + 1, IID_BOULDER) != nullptr) && getWorld()->getObject(x, y + 2, IID_HOLE) != nullptr)
			{
				getWorld()->getObject(x, y + 1, IID_BOULDER)->moveTo(x, y + 2);
				Player::moveTo(x, y + 1);
			}

			//MOVING A ROCK
			else if ((getWorld()->getObject(x, y + 1, IID_BOULDER) != nullptr) && getWorld()->objectHere(x, y + 2) == 0)
			{
				getWorld()->getObject(x, y + 1, IID_BOULDER)->moveTo(x, y + 2);
				Player::moveTo(x, y + 1);
			}
			break;

		case KEY_PRESS_DOWN: 
			x = Player::getX();
			y = Player::getY();
			Player::setDirection(Direction::down);
			if ((getWorld()->objectHere(x, y - 1) == 0
				|| getWorld()->getObject(x, y - 1, IID_JEWEL) != nullptr
				|| getWorld()->getObject(x, y - 1, IID_EXTRA_LIFE) != nullptr
				|| getWorld()->getObject(x, y - 1, IID_RESTORE_HEALTH) != nullptr
				|| getWorld()->getObject(x, y - 1, IID_AMMO) != nullptr
				|| getWorld()->getObject(x, y - 1, IID_EXIT) != nullptr)
				&& !(getWorld()->getObject(x, y - 1, IID_SNARLBOT) != nullptr)
				&& !(getWorld()->getObject(x, y - 1, IID_KLEPTOBOT) != nullptr)
				&& !(getWorld()->getObject(x, y - 1, IID_ANGRY_KLEPTOBOT) != nullptr))
			{
				Player::moveTo(x, y - 1);
			}

			//ROCK INTO HOLE
			if ((getWorld()->getObject(x, y - 1, IID_BOULDER) != nullptr) && getWorld()->getObject(x, y - 2, IID_HOLE) != nullptr)
			{
				getWorld()->getObject(x, y - 1, IID_BOULDER)->moveTo(x, y - 2);
				Player::moveTo(x, y - 1);
			}

			//MOVING A ROCK
			else if ((getWorld()->getObject(x, y - 1, IID_BOULDER) != nullptr) && getWorld()->objectHere(x, y - 2) == 0)
			{
				getWorld()->getObject(x, y - 1, IID_BOULDER)->moveTo(x, y - 2);
				Player::moveTo(x, y - 1);
			}
			break;

		case KEY_PRESS_SPACE:
			x = Player::getX();
			y = Player::getY();

			//CREATES BULLETS
			if (m_ammo > 0)
			{
				if (Player::getDirection() == GraphObject::left) //left
				{
					getWorld()->playSound(SOUND_PLAYER_FIRE);
					getWorld()->createBullet(x - 1, y, 0);
					m_ammo--;
					break;
				}
				else if (Player::getDirection() == GraphObject::right) //right
				{
					getWorld()->playSound(SOUND_PLAYER_FIRE);
					getWorld()->createBullet(x + 1, y, 1);
					m_ammo--;
					break;
				}
				else if (Player::getDirection() == GraphObject::up) //up
				{
					getWorld()->playSound(SOUND_PLAYER_FIRE);
					getWorld()->createBullet(x, y + 1, 2);
					m_ammo--;
					break;
				}
				else if (Player::getDirection() == GraphObject::down) //down
				{
					getWorld()->playSound(SOUND_PLAYER_FIRE);
					getWorld()->createBullet(x, y - 1, 3);
					m_ammo--;
					break;
				}
			}
			break;
		case KEY_PRESS_ESCAPE: //KILL PLAYER
			setDead();
		}
	}
}

void Player::damage()
{
	editHealth(-2); //decrease health
	if (getHealth() <= 0)
	{
		setDead();
		getWorld()->playSound(SOUND_PLAYER_DIE);
	}
	else
		getWorld()->playSound(SOUND_PLAYER_IMPACT);
}

//WALL
Wall::Wall(int id, StudentWorld* world, int x, int y) : BaseObject(id, world, x, y)
{}

//BOULDER
Boulder::Boulder(int id, StudentWorld* world, int x, int y, Direction dir, int health) : aliveObject(id, world, x, y, dir, health)
{}

void Boulder::damage()
{
	editHealth(-2);
	if (getHealth() <= 0)
	{
		setDead();
	}
}


//HOLE
Hole::Hole(int id, StudentWorld* world, int x, int y) : BaseObject(id, world, x, y)
{}

void Hole::doSomething()
{
	if (!Hole::alive())
		return;
	if (getWorld()->getObject(Hole::getX(), Hole::getY(), IID_BOULDER) != nullptr) //if boulder gets pushed into hole
	{
		getWorld()->getObject(Hole::getX(), Hole::getY(), IID_BOULDER)->setDead();
		Hole::setDead();	
	}
}

//JEWEL
Jewel::Jewel(int id, StudentWorld* world, int x, int y) : BaseObject(id, world, x, y)
{}

void Jewel::doSomething()
{
	if (!Jewel::alive())
		return;
	if (getWorld()->getObject(Jewel::getX(), Jewel::getY(), IID_PLAYER) != nullptr) //if player steps on it
	{
		getWorld()->increaseScore(50);
		Jewel::setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
	}
}

//EXIT
Exit::Exit(int id, StudentWorld* world, int x, int y) : BaseObject(id, world, x, y)
{
	setVisible(false);
}

void Exit::doSomething() 
{
	if (getWorld()->getObject(Exit::getX(), Exit::getY(), IID_PLAYER) != nullptr && Exit::isVisible()) //if player steps on exit
	{
		getWorld()->playSound(SOUND_FINISHED_LEVEL);
		getWorld()->increaseScore(2000);
		getWorld()->changeFinished(); //notify StudentWorld
		getWorld()->increaseScore(getWorld()->getBonus());
	}
} 

//BULLET
Bullet::Bullet(int id, StudentWorld* world, int x, int y, Direction dir, int health) : aliveObject(id, world, x, y, dir, health)
{}

void Bullet::doSomething()
{
	if (!Bullet::alive())
		return;
	if (damageCheck()) //check if bullet hit something
		return;

	//MOVE
	if (Bullet::getDirection() == GraphObject::left)
	{
		Bullet::moveTo(Bullet::getX() - 1, Bullet::getY());
		if (damageCheck()); //check if bullet hit something again
		return;
	}
	if (Bullet::getDirection() == GraphObject::right)
	{
		Bullet::moveTo(Bullet::getX() + 1, Bullet::getY());
		if (damageCheck());
		return;
	}
	if (Bullet::getDirection() == GraphObject::up)
	{
		Bullet::moveTo(Bullet::getX(), Bullet::getY() + 1);
		if (damageCheck());
		return;
	}
	if (Bullet::getDirection() == GraphObject::down)
	{
		Bullet::moveTo(Bullet::getX(), Bullet::getY() - 1);
		if (damageCheck());
		return;
	}
}

bool Bullet::damageCheck() //return true if object is hit
{
	//call damage function of hit object
	if (getWorld()->getObject(getX(), getY(), IID_BOULDER) != nullptr)
	{
		getWorld()->getObject(getX(), getY(), IID_BOULDER)->damage();
		setDead();
		return true;
	}
	if (getWorld()->getObject(getX(), getY(), IID_PLAYER) != nullptr)
	{
		getWorld()->getObject(getX(), getY(), IID_PLAYER)->damage();
		setDead();
		return true;
	}
	if (getWorld()->getObject(getX(), getY(), IID_WALL) != nullptr)
	{
		getWorld()->getObject(getX(), getY(), IID_WALL)->damage();
		setDead();
		return true;
	}
	if (getWorld()->getObject(getX(), getY(), IID_SNARLBOT) != nullptr)
	{
		getWorld()->getObject(getX(), getY(), IID_SNARLBOT)->damage();
		setDead();
		return true;
	}
	if (getWorld()->getObject(getX(), getY(), IID_KLEPTOBOT) != nullptr)
	{
		getWorld()->getObject(getX(), getY(), IID_KLEPTOBOT)->damage();
		setDead();
		return true;
	}
	if (getWorld()->getObject(getX(), getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
	{
		getWorld()->getObject(getX(), getY(), IID_ANGRY_KLEPTOBOT)->damage();
		setDead();
		return true;
	}

	return false;
}
//EXTRA LIFE
ExtraLife::ExtraLife(int id, StudentWorld* world, int x, int y) : BaseObject(id, world, x, y)
{}

void ExtraLife::doSomething()
{
	if (!ExtraLife::alive())
		return;
	if (getWorld()->getObject(ExtraLife::getX(), ExtraLife::getY(), IID_PLAYER) != nullptr) //if player steps on it
	{
		getWorld()->increaseScore(1000);
		ExtraLife::setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->incLives();
	}
}
//RESTORE HEALTH
RestoreHealth::RestoreHealth(int id, StudentWorld* world, int x, int y) : BaseObject(id, world, x, y)
{}

void RestoreHealth::doSomething()
{
	if (!RestoreHealth::alive())
		return;
	if (getWorld()->getObject(RestoreHealth::getX(), RestoreHealth::getY(), IID_PLAYER) != nullptr) //if player steps on it
	{
		getWorld()->increaseScore(500);
		RestoreHealth::setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->getPlayer()->editHealth(20);
	}
}

//AMMO
Ammo::Ammo(int id, StudentWorld* world, int x, int y) : BaseObject(id, world, x, y)
{}

void Ammo::doSomething()
{
	if (!Ammo::alive())
		return;
	if (getWorld()->getObject(Ammo::getX(), Ammo::getY(), IID_PLAYER) != nullptr)
	{
		getWorld()->increaseScore(100);
		Ammo::setDead();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->getPlayer()->editAmmo(20); //increase ammo by 20
	}
}
Robot::Robot(int id, StudentWorld* world, int x, int y, Direction dir, int health) : aliveObject(id, world, x, y, dir, health), m_ticks(0)
{
	int ticks = ((28 - getWorld()->getLevel()) / 4);
	if (ticks < 3)
		ticks = 3;
	m_tickAction = ticks;
}
int Robot::getTicks()
{
	return m_ticks;
}
void Robot::editTicks(int x)
{
	m_ticks += x;
}
int Robot::getTickAction()
{
	return m_tickAction;
}
int BaseObject::random(int min, int max)
{
	//returns a random int between min and max
	int range = (max - min) + 1;
	return  min + rand() % range;
}
Snarlbot::Snarlbot(int id, StudentWorld* world, int x, int y, Direction dir, int health) : Robot(id, world, x, y, dir, health)
{}

void Snarlbot::doSomething()
{
	if (!alive())
		return;
	if (!(getTicks() == getTickAction()))
	{
		editTicks(1);
		return;
	}
	if (CanFire()) //can and does fire
	{
		editTicks(-getTicks());
		return;
	}
	
	move(getDirection()); //move
	editTicks(-getTicks());
	return;
}

bool Robot::CanFire()
{
	//if there are no obstacles before a player is found, fire a bullet
	int check = 0;
	if (getDirection() == right)
	{		
		for (int a = getX() + 1; a < 15; a++)
		{
			if (getWorld()->isObstacle(a, getY()))
				check = 1;
			if (getWorld()->getObject(a, getY(), IID_HOLE) != nullptr)
				check = 0;
			if (getWorld()->getObject(a, getY(), IID_PLAYER) != nullptr && check == 0)
			{
				getWorld()->createBullet(getX() + 1, getY(), 1);
				getWorld()->playSound(SOUND_ENEMY_FIRE);
				return true;
			}
		}
	}
	check = 0;

	if (getDirection() == left)
	{
		for (int a = getX() - 1; a > 0; a--)
		{
			if (getWorld()->isObstacle(a, getY()))
				check = 1;
			if (getWorld()->getObject(a, getY(), IID_HOLE) != nullptr)
				check = 0;
			if (getWorld()->getObject(a, getY(), IID_PLAYER) != nullptr && check == 0)
			{
				getWorld()->createBullet(getX() - 1, getY(), 0);
				getWorld()->playSound(SOUND_ENEMY_FIRE);
				return true;
			}
		}
	}
	check = 0;

	if (getDirection() == up)
	{
		for (int a = getY() + 1; a < 15; a++)
		{
			if (getWorld()->isObstacle(getX(), a))
				check = 1;
			if (getWorld()->getObject(getX(), a, IID_HOLE) != nullptr)
				check = 0;
			if (getWorld()->getObject(getX(), a, IID_PLAYER) != nullptr && check == 0)
			{
				getWorld()->createBullet(getX(), getY() + 1, 2);
				getWorld()->playSound(SOUND_ENEMY_FIRE);
				return true;
			}
		}
	}
	check = 0;

	if (getDirection() == down)
	{
		for (int a = getY() - 1; a > 0; a--)
		{
			if (getWorld()->isObstacle(getX(), a))
				check = 1;
			if (getWorld()->getObject(getX(), a, IID_HOLE) != nullptr)
				check = 0;
			if (getWorld()->getObject(getX(), a, IID_PLAYER) != nullptr && check == 0)
			{
				getWorld()->createBullet(getX(), getY() - 1, 3);
				getWorld()->playSound(SOUND_ENEMY_FIRE);
				return true;
			}
		}
	}
	check = 0;
	return false;
}

void Robot::move(Direction dir)
{
	//if theres a space in the dir direction, move it one space that direction else switch direction
	switch (dir)
	{
	case::GraphObject::right:
	{
		if (getDirection() == right && !getWorld()->isObstacle(getX() + 1, getY()))
			moveTo(getX() + 1, getY());
		else
			setDirection(GraphObject::left);
		break;
	}
	case::GraphObject::left:
	{
		if (getDirection() == left && !getWorld()->isObstacle(getX() - 1, getY()))
			moveTo(getX() - 1, getY());
		else
			setDirection(GraphObject::right);
		break;
	}
	case::GraphObject::up:
	{
		if (getDirection() == up && !getWorld()->isObstacle(getX(), getY() + 1))
			moveTo(getX(), getY() + 1);
		else
			setDirection(GraphObject::down);
		break;
	}
	case::GraphObject::down:
	{
		if (getDirection() == down && !getWorld()->isObstacle(getX(), getY() - 1))
			moveTo(getX(), getY() - 1);
		else
			setDirection(GraphObject::up);
		break;
	}
	default:
		break;
	}	
}

void Snarlbot::damage()
{
	editHealth(-2);
	if (getHealth() <= 0) //if health = 0, dead
	{
		setDead();
		getWorld()->playSound(SOUND_ROBOT_DIE);
		getWorld()->increaseScore(100);
	}
	else
		getWorld()->playSound(SOUND_ROBOT_IMPACT);
}
KleptoBot::KleptoBot(int id, StudentWorld* world, int x, int y, Direction dir, int health) : Robot(id, world, x, y, dir, health), m_distanceCount(0), m_goodieType(0)
{
	m_distance = random(1, 6);
}

void KleptoBot::doSomething()
{
	if (!alive())
		return;
	if (!(getTicks() == getTickAction()))
	{
		editTicks(1);
		return;
	}
	//---------
	if (pickup()) //tries to pickup goodie
	{
		editTicks(-getTicks());
		return;
	}
	//---------4
	int temp = m_distanceCount;
	if (m_distanceCount < m_distance)
		move(KleptoBot::getDirection());
	if (temp < m_distanceCount) //bot moved succesfully
	{
		editTicks(-getTicks());
		return;
	}	
	//---------

	direction();

	editTicks(-getTicks());
	return;
}
bool KleptoBot::pickup()
{
	//if goodie is there, 1 in 10 chance to pick it up
	if (getWorld()->getObject(getX(), getY(), IID_AMMO) != nullptr)
	{
		int arand = random(1, 10);
		if (arand == 5)
		{
			getWorld()->getObject(getX(), getY(), IID_AMMO)->setDead();
			m_goodieType = 1;
			getWorld()->playSound(SOUND_ROBOT_MUNCH);
			return true;
		}
	}
	if (getWorld()->getObject(getX(), getY(), IID_EXTRA_LIFE) != nullptr)
	{
		int arand = random(1, 10);
		if (arand == 5)
		{
			getWorld()->getObject(getX(), getY(), IID_EXTRA_LIFE)->setDead();
			m_goodieType = 2;
			getWorld()->playSound(SOUND_ROBOT_MUNCH);
			return true;
		}
	}
	if (getWorld()->getObject(getX(), getY(), IID_RESTORE_HEALTH) != nullptr)
	{
		int arand = random(1, 10);
		if (arand == 5)
		{
			getWorld()->getObject(getX(), getY(), IID_RESTORE_HEALTH)->setDead();
			m_goodieType = 3;
			getWorld()->playSound(SOUND_ROBOT_MUNCH);
			return true;
		}
	}

	return false;
}
void KleptoBot::direction()
{
	//finds a random direction and moves one space to that direction
	bool tried1 = false;
	bool tried2 = false;
	bool tried3 = false;
	bool tried4 = false;
	bool triedAll = false;
	bool found = false;
	m_distance = random(1, 6);
	m_distanceCount = 0;

	while (!found && !triedAll)
	{
		int xrand = random(1, 4);

		if (xrand == 1 && !tried1)
		{
			if (!getWorld()->isObstacle(getX() + 1, getY()) && getWorld()->getObject(getX() + 1, getY(), IID_PLAYER) == nullptr)
			{
				setDirection(right);
				move(right);
				found = true;
			}
			else
				tried1 = true;
		}
		if (xrand == 2 && !tried2)
		{
			if (!getWorld()->isObstacle(getX() - 1, getY()) && getWorld()->getObject(getX() - 1, getY(), IID_PLAYER) == nullptr)
			{
				setDirection(left);
				move(left);
				found = true;
			}
			else
				tried2 = true;
		}
		if (xrand == 3 && !tried3)
		{
			if (!getWorld()->isObstacle(getX(), getY() + 1) && getWorld()->getObject(getX(), getY() + 1, IID_PLAYER) == nullptr)
			{
				setDirection(up);
				move(up);
				found = true;
			}
			else
				tried3 = true;
		}
		if (xrand == 4 && !tried4)
		{
			if (!getWorld()->isObstacle(getX(), getY() - 1) && getWorld()->getObject(getX(), getY() - 1, IID_PLAYER) == nullptr)
			{
				setDirection(down);
				move(down);
				found = true;
			}
			else
				tried4 = true;
		}

		if (tried1 && tried2 && tried3 && tried4)
		{
			triedAll = true;
		}
	}
	if (triedAll)
	{
		int trand = random(1, 4);
		switch (trand)
		{
		case 1:
			setDirection(right);
			break;
		case 2:
			setDirection(left);
			break;
		case 3:
			setDirection(up);
			break;
		case 4:
			setDirection(down);
			break;
		}
	}
}
void KleptoBot::damage()
{
	editHealth(-2);
	if (getHealth() <= 0)
	{
		setDead();
		getWorld()->playSound(SOUND_ROBOT_DIE);
		getWorld()->increaseScore(10);
		if (m_goodieType > 0)
		{
			int goodie = m_goodieType;

			switch (goodie) //drops goodie based on type picked up
			{
			case 1:
				getWorld()->createAmmo(getX(), getY());
				break;
			case 2:
				getWorld()->createExtraLife(getX(), getY());
				break;
			case 3:
				getWorld()->createRestoreHealth(getX(), getY());
				break;
			}
		}
	}
	else
		getWorld()->playSound(SOUND_ROBOT_IMPACT);
}

void KleptoBot::move(Direction dir)
{
	//if there is space to move, move one space, update distance count
	switch (dir)
	{
	case::GraphObject::right:
	{
	if (!getWorld()->isObstacle(getX() + 1, getY()) && getWorld()->getObject(getX() + 1, getY(), IID_PLAYER) == nullptr)
	{
	moveTo(getX() + 1, getY());
	m_distanceCount++;
	return;
	}break;
	}
	case::GraphObject::left:
	{
	if (!getWorld()->isObstacle(getX() - 1, getY()) && getWorld()->getObject(getX() - 1, getY(), IID_PLAYER) == nullptr)
	{
	moveTo(getX() - 1, getY());
	m_distanceCount++;
	return;
	}break;
	}

	case::GraphObject::up:
	{
	if (!getWorld()->isObstacle(getX(), getY() + 1) && getWorld()->getObject(getX(), getY() + 1, IID_PLAYER) == nullptr)
	{
	moveTo(getX(), getY() + 1);
	m_distanceCount++;
	return;
	}break;
	}

	case::GraphObject::down:
	{
	if (!getWorld()->isObstacle(getX(), getY() - 1) && getWorld()->getObject(getX(), getY() - 1, IID_PLAYER) == nullptr)
	{
	moveTo(getX(), getY() - 1);
	m_distanceCount++;
	return;
	}break;
	}
	default:
	return;
	}
}
AngryKleptoBot::AngryKleptoBot(int id, StudentWorld* world, int x, int y, Direction dir, int health) : KleptoBot(id, world, x, y, dir, health)
{}

void AngryKleptoBot::doSomething()
{
	if (!alive())
		return;
	if (!(getTicks() == getTickAction()))
	{
		editTicks(1);
		return;
	}

	if (KleptoBot::Robot::CanFire()) //if robot fired
	{
		editTicks(-getTicks());
		return;
	}

	if (pickup()) //if goodie was picked up
	{
		editTicks(-getTicks());
		return;
	}

	//checks to see if distance before turning has been met
	int temp = getDistance();
	if (getDcount() < getDistance())
		move(KleptoBot::getDirection());
	if (temp < getDcount()) //bot moved succesfully
	{
		editTicks(-getTicks());
		return;
	}

	//changes to random direction
	direction();

	editTicks(-getTicks());
	return;

}

int KleptoBot::getDistance()
{
	return m_distance;
}

int KleptoBot:: getDcount()
{
	return m_distanceCount;
}

int KleptoBot::getGoodieType()
{
	return m_goodieType;
}

KleptoBotFactory::KleptoBotFactory(int id, StudentWorld* world, int x, int y, int type) : BaseObject(id, world, x, y), m_robotType(type)
{}

void KleptoBotFactory::doSomething()
{
	if (botCount() < 3)
	{
		int nrand = random(1, 50);
		if (nrand == 25)
		{
			if (m_robotType == 1 && getWorld()->getObject(getX(), getY(), IID_KLEPTOBOT) == nullptr) //if regular kleptobot factory
				getWorld()->createKleptoBot(getX(), getY());
			if (m_robotType == 2 && getWorld()->getObject(getX(), getY(), IID_ANGRY_KLEPTOBOT) == nullptr) //if angry klepotbot factory
				getWorld()->createAngryKleptoBot(getX(), getY());
			getWorld()->playSound(SOUND_ROBOT_BORN);
			return;
		}
	}
	return;
}

//USES 2 FOR LOOPS TO SEE HOW MANY KLEPTOBOTS ARE IN SPECIFIED AREA
int KleptoBotFactory::botCount()
{
	int count = 0;
	int xright = 0;
	int xleft = 0;
	int yup = 0;
	int ydown = 0;

	xright = getX() + 3;
	if (xright > 14)
		xright = 14;

	xleft = getX() - 3;
	if (xleft < 0)
		xleft = 0;

	yup = getY() + 3;
	if (yup > 14)
		yup = 14;

	ydown = getY() - 3;
	if (ydown < 0)
		ydown = 0;

	for (int a = yup; a >= ydown; a--)
	{
		for (int b = xleft; b <= xright; b++)
		{
			if (getWorld()->getObject(b, a, IID_KLEPTOBOT) != nullptr || getWorld()->getObject(b, a, IID_ANGRY_KLEPTOBOT) != nullptr)
				count++;
		}
	}
	return count;
}
