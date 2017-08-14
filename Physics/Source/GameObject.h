#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include <map>

using namespace std;

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_CUBE,

		GO_WALL,
		GO_PILLAR,

		GO_PACHINKO_EXIT,
		GO_PACHINKO_WALL,
		GO_PACHINKO_MOVING_WALL,
		GO_PACHINKO_ROUND,
		GO_PACHINKO_PILLAR,
		GO_PACHINKO_MOVING_PILLAR,
		GO_PACHINKO_PADDLE,
		GO_PACHINKO_PADDLE_PILLAR,

		GO_PACHINKO_PORTAL_IN,
		GO_PACHINKO_PORTAL_OUT,
		GO_PACHINKO_BLACKHOLE,
		GO_PACHINKO_HEALTH,
		GO_PACHINKO_LENGTH,

		GO_TOTAL, //must be last
	};

	struct GAMEOBJECT_TYPE_MAP : public map<string, GAMEOBJECT_TYPE>
	{
		GAMEOBJECT_TYPE_MAP()
		{
			this->operator[]("wall") = GO_WALL;
			this->operator[]("pillar") = GO_PILLAR;
			this->operator[]("pachinko_exit") = GO_PACHINKO_EXIT;
			this->operator[]("pachinko_wall") = GO_PACHINKO_WALL;
			this->operator[]("pachinko_moving_wall") = GO_PACHINKO_MOVING_WALL;
			this->operator[]("pachinko_round") = GO_PACHINKO_ROUND;
			this->operator[]("pachinko_pillar") = GO_PACHINKO_PILLAR;
			this->operator[]("pachinko_moving_pillar") = GO_PACHINKO_MOVING_PILLAR;
			this->operator[]("pachinko_paddle") = GO_PACHINKO_PADDLE;
			this->operator[]("pachinko_paddle_pillar") = GO_PACHINKO_PADDLE_PILLAR;
			this->operator[]("pachinko_portal_in") = GO_PACHINKO_PORTAL_IN;
			this->operator[]("pachinko_portal_out") = GO_PACHINKO_PORTAL_OUT;
			this->operator[]("pachinko_blackhole") = GO_PACHINKO_BLACKHOLE;
			this->operator[]("pachinko_health") = GO_PACHINKO_HEALTH;
			this->operator[]("pachinko_length") = GO_PACHINKO_LENGTH;
		}
		~GAMEOBJECT_TYPE_MAP() {}
	};

	GAMEOBJECT_TYPE_MAP inputType;
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 dir;
	float theta;
	float momentOfInertia;
	float angularVelocity;
	float mass;
	bool active;
	bool colliding;
	bool leftRight;
	Vector3 color[3];
	int bullet_Count;
	int missle_Count;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();
};

#endif