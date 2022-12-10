#pragma once
#ifndef ROOMDATA_HPP
#define ROOMDATA_HPP

#include <SFML/Graphics.hpp>
#include "Colliders.h"
#include "Obstacle.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <list>
#include <queue>

class RoomData
{
public:
	RoomData();
	~RoomData();

	std::vector<Obstacle*> m_roomStatues;

};
#endif // !ROOMDATA_HPP

