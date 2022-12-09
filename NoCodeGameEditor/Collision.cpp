#include "Collision.h"

Collision::Collision()
{

}

Collision::Collision(Player* t_player, Grid* t_grid, Weapon* t_weapon) :
	m_player(t_player), m_grid(t_grid), m_weapon(t_weapon)
{
}

Collision::~Collision()
{

}

void Collision::setColliders(sf::RectangleShape* t_objectOne, std::vector<Colliders*> t_objectTwo, int t_sizeOne, float t_weight)
{
	for (int i = 0; i < t_sizeOne; i++)
	{
		checkCollision(t_objectOne, t_objectTwo.at(i)->getBounds(), t_weight);
	}
}

void Collision::setColliders(std::vector<Obstacle*> t_objectOne, std::vector<Colliders*> t_objectTwo, int t_sizeOne, int t_sizeTwo, float t_weight)
{
	for (int i = 0; i < t_sizeOne; i++)
	{
		for (int j = 0; j < t_sizeTwo; j++)
		{
			checkCollision(t_objectOne.at(i)->getBounds(), t_objectTwo.at(j)->getBounds(), t_weight);
		}
	}
}

void Collision::setColliders(std::vector<Obstacle*> t_objectOne, int t_sizeOne, float t_weight)
{
	for (int i = 0; i < t_sizeOne; i++)
	{
		for (int j = 0; j < t_sizeOne; j++)
		{
			if (j < t_sizeOne - 1)
			{
				checkCollision(t_objectOne.at(i)->getBounds(), t_objectOne.at(j+1)->getBounds(), t_weight);
			}
		}
	}
}

void Collision::setColliders(sf::RectangleShape* t_objectOne, std::vector<Obstacle*> t_objectTwo, int t_size, float t_weight)
{
	for (int i = 0; i < t_size; i++)
	{
		checkCollision(t_objectOne, t_objectTwo.at(i)->getBounds(), t_weight);
	}
}

void Collision::setColliders()
{
	std::vector<Obstacle*>::iterator it;
	for (it = m_grid->m_statues.begin(); it != m_grid->m_statues.end();)
	{
		Obstacle* l_obstacle = *it;
		if (checkCollision(m_weapon->getWeaponBounds(), l_obstacle->getBounds(), 0.4f))
		{
			it = m_grid->m_statues.erase(it);
			m_grid->noOfObstacles--;
		}
		else
		{
			it++;
		}
	}
}


void Collision::update(sf::Time t_deltaTime)
{
	if (m_grid->m_vectColliders.size() > 0)
	{
		setColliders(m_player->getBounds(), m_grid->m_vectColliders, m_grid->m_vectColliders.size(), 0.0f);
		setColliders(m_grid->m_statues, m_grid->m_vectColliders, m_grid->m_statues.size(), m_grid->m_vectColliders.size(), 0.0f);
		setColliders(m_player->getBounds(), m_grid->m_statues, m_grid->m_statues.size(), 0.4f);
		setColliders(m_grid->m_statues, m_grid->m_statues.size(), 0.5f);
		if (m_weapon->m_weaponUsed)
		{
			setColliders();
		}
	}

}

bool Collision::checkCollision(sf::RectangleShape* t_objectOne, sf::RectangleShape* t_objectTwo, float t_push)
{
	sf::Vector2f l_objectTwoPosition = t_objectTwo->getPosition();
	sf::Vector2f l_objectTwoSize = t_objectTwo->getSize() / 2.0f;
	sf::Vector2f l_objectOnePosition = t_objectOne->getPosition();
	sf::Vector2f l_objectOneHalfSize = t_objectOne->getSize() / 2.0f;

	float l_deltaX = l_objectTwoPosition.x - l_objectOnePosition.x;
	float l_deltaY = l_objectTwoPosition.y - l_objectOnePosition.y;

	float l_intersectX = abs(l_deltaX) - (l_objectTwoSize.x + l_objectOneHalfSize.x);
	float l_intersectY = abs(l_deltaY) - (l_objectTwoSize.y + l_objectOneHalfSize.y);

	if (l_intersectX < 0.0f && l_intersectY < 0.0f)
	{
		t_push = std::min(std::max(t_push, 0.0f), 1.0f); // clamping

		if (l_intersectX > l_intersectY)
		{
			if (l_deltaX > 0.0f)
			{
				move(l_intersectX * (1.0f - t_push), 0.0f, t_objectOne);
				move(-l_intersectX * t_push, 0.0f, t_objectTwo);
			}
			else
			{
				move(-l_intersectX * (1.0f - t_push), 0.0f, t_objectOne);
				move(l_intersectX * t_push, 0.0f, t_objectTwo);
			}
		}
		else
		{
			if (l_deltaY > 0.0f)
			{
				move(0.0f, l_intersectY * (1.0f - t_push), t_objectOne);
				move(0.0f, -l_intersectY * t_push, t_objectTwo);
			}
			else
			{
				move(0.0f, -l_intersectY * (1.0f - t_push), t_objectOne);
				move(0.0f, l_intersectY * t_push, t_objectTwo);
			}
		}
		return true;
	}
	return false;
}

void Collision::move(float t_deltaX, float t_deltaY, sf::RectangleShape* t_object)
{
	t_object->move(t_deltaX, t_deltaY);
}
