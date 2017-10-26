#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void Destroy();

public:
	p2List<PhysBody*> circles;
	PhysBody* boxes[9];
	PhysBody* map;
	PhysBody* bouncers[5];
	PhysBody* walls[5];

	SDL_Texture* map_texture;
	SDL_Texture* ball;
	SDL_Texture* box;
	SDL_Texture* cones[4];

	PhysBody* sensor;
	bool sensed;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
	int destroy = 100;

private:
	PhysBody *spring;
	PhysBody *springSurface;
	PhysBody *limit;
};
