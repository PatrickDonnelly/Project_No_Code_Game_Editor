#include "Collision.h"

/// <summary>
/// Default Constructor
/// </summary>
Collision::Collision()
{

}

/// <summary>
/// Deconstructor
/// </summary>
Collision::~Collision()
{
}

/// <summary>
/// Checks collision between two objects and uses a weight to determine how the force is split
/// between objects. Acts like a weight.
/// </summary>
/// <param name="t_objectOne"></param>
/// <param name="t_objectTwo"></param>
/// <param name="t_push"></param>
/// <returns></returns>
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

/// <summary>
/// Checks collision between two objects
/// </summary>
/// <param name="t_objectOne"></param>
/// <param name="t_objectTwo"></param>
/// <returns></returns>
bool Collision::checkCollision(sf::RectangleShape* t_objectOne, sf::RectangleShape* t_objectTwo)
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
		return true;
	}

	return false;
}

/// <summary>
/// Moves the object
/// </summary>
/// <param name="t_deltaX"></param>
/// <param name="t_deltaY"></param>
/// <param name="t_object"></param>
void Collision::move(float t_deltaX, float t_deltaY, sf::RectangleShape* t_object)
{
	t_object->move(t_deltaX, t_deltaY);
}
