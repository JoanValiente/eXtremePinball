#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePhysics.h"

#include "Box2D/Box2D/Box2D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	b2Vec2 flipper_ver[8];
	flipper_ver[0].Set(412 - 402, 543 - 532);
	flipper_ver[1].Set(423 - 402, 542 - 532);
	flipper_ver[2].Set(432 - 402, 540 - 532);
	flipper_ver[3].Set(431 - 402, 535 - 532);
	flipper_ver[4].Set(421 - 402, 534 - 532);
	flipper_ver[5].Set(406 - 402, 533 - 532);
	flipper_ver[6].Set(402 - 402, 537 - 532);
	flipper_ver[7].Set(405 - 402, 543 - 532);

	for (int i = 0; i < 8; i++) {
		flipper_ver[i].x = PIXEL_TO_METERS(flipper_ver[i].x);
		flipper_ver[i].y = PIXEL_TO_METERS(flipper_ver[i].y);
	}

	//Flipper
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(0, 0);
	b2Body* b = App->physics->world->CreateBody(&body);
	b2PolygonShape flipper;
	flipper.Set(flipper_ver, 8);

	b2FixtureDef fixture;
	fixture.density = 1.0f;
	fixture.shape = &flipper;
	b->CreateFixture(&fixture);

	LeftFlipper = new PhysBody();
	LeftFlipper->body = b;
	b->SetUserData(LeftFlipper);

	RightFlipper = new PhysBody();
	RightFlipper->body = b;
	b->SetUserData(RightFlipper);
	//

	// --------------------------------------------LEFT FLIPPER------------------------------------------

	LeftFlipperjoint = App->physics->CreateCircle(480, 600, 6, b2_staticBody);

	b2RevoluteJointDef LeftJointDef;
	LeftJointDef.bodyA = LeftFlipper->body;
	LeftJointDef.bodyB = LeftFlipperjoint->body;
	LeftJointDef.collideConnected = false;

	b2Vec2 LsetA = { 0.13f, 0.12f };
	b2Vec2 LsetB = LeftFlipperjoint->body->GetLocalCenter();

	LeftJointDef.localAnchorA.Set(LsetA.x, LsetA.y);
	LeftJointDef.localAnchorB.Set(LsetB.x, LsetB.y);

	LeftJointDef.enableLimit = true;
	LeftJointDef.lowerAngle = -45 * DEGTORAD;
	LeftJointDef.upperAngle = 45 * DEGTORAD;

	// --------------------------------------------RIGHT FLIPPER------------------------------------------

	RightFlipperjoint = App->physics->CreateCircle(540, 600, 6, b2_staticBody);

	
	b2RevoluteJointDef RightJointDef;
	RightJointDef.bodyA = RightFlipper->body;
	RightJointDef.bodyB = RightFlipperjoint->body;
	RightJointDef.collideConnected = false;

	b2Vec2 RsetA = { 0.13f, 0.12f };
	b2Vec2 RsetB = RightFlipperjoint->body->GetLocalCenter();

	RightJointDef.localAnchorA.Set(RsetA.x, RsetA.y);
	RightJointDef.localAnchorB.Set(RsetB.x, RsetB.y);

	RightJointDef.enableLimit = true;
	RightJointDef.lowerAngle = -45 * DEGTORAD;
	RightJointDef.upperAngle = 45 * DEGTORAD;

	// --------------------------------------------------------------------------------------
	/*
	//Motor
	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = 10.0f;
	jointDef.motorSpeed = 0.0f;
	*/

	// LEFT FLIPPER
	LFlipperLeftFlipper = (b2RevoluteJoint*)App->physics->world->CreateJoint(&LeftJointDef);

	// RIGHT FLIPPER
//	RFlipperRightFlipper = (b2RevoluteJoint*)App->physics->world->CreateJoint(&RightJointDef);

	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		LFlipperLeftFlipper->GetBodyA()->ApplyAngularImpulse(-0.1f, true);
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		RFlipperRightFlipper->GetBodyA()->ApplyAngularImpulse(-0.1f, true);
	return UPDATE_CONTINUE;
}



