#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class b2RevoluteJoint;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	PhysBody* LeftFlipper;
	PhysBody* RightFlipper;
	PhysBody* LeftFlipperjoint;
	PhysBody* RightFlipperjoint;

private:

	b2RevoluteJoint* LFlipperLeftFlipper;
	b2RevoluteJoint* RFlipperRightFlipper;
};