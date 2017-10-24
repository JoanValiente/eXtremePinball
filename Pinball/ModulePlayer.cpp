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
	b2Vec2 flipper_ver[7];
	flipper_ver[0].Set(36, 8);
	flipper_ver[1].Set(15, 8);
	flipper_ver[2].Set(2, 10);
	flipper_ver[3].Set(0, 14);
	flipper_ver[4].Set(3, 18);
	flipper_ver[5].Set(15, 20);
	flipper_ver[6].Set(35, 20);	
	

	for (int i = 0; i < 7; i++) {
		flipper_ver[i].x = PIXEL_TO_METERS(flipper_ver[i].x);
		flipper_ver[i].y = PIXEL_TO_METERS(flipper_ver[i].y);
	}

	//Flipper
	/*
	b2BodyDef flipR;
	flipR.type = b2_dynamicBody;
	flipR.position.x = 169.0f;
	flipR.position.y = 0;
	b2BodyDef flipL;
	flipL.type = b2_dynamicBody;
	flipL.position.x = 169.0f;
	flipL.position.y = 0;
	b2Body* f1 = App->physics->world->CreateBody(&flipL);
	b2Body* f2 = App->physics->world->CreateBody(&flipR);



	b2PolygonShape flipper;
	flipper.Set(flipper_ver, 7);



	b2FixtureDef fixture;
	fixture.density = 1.0f;
	fixture.shape = &flipper;
	f1->CreateFixture(&fixture);
	f2->CreateFixture(&fixture);

	LeftFlipper = new PhysBody();
	LeftFlipper->body = f1;
	f1->SetUserData(LeftFlipper);


	RightFlipper = new PhysBody();
	RightFlipper->body = f2;
	f2->SetUserData(RightFlipper);
	*/
	//

	// --------------------------------------------LEFT FLIPPER------------------------------------------

	LeftFlipperjoint = App->physics->CreateCircle(104, 519, 6, b2_staticBody, 1.0f);
	LeftFlipper = App->physics->CreateRectangle(110, 519, 45, 10, b2_dynamicBody);

	b2RevoluteJointDef LeftJointDef;
	LeftJointDef.bodyA = LeftFlipper->body;
	LeftJointDef.bodyB = LeftFlipperjoint->body;
	LeftJointDef.collideConnected = false;

	b2Vec2 LsetA = { -0.32f, 0.0f };
	b2Vec2 LsetB = LeftFlipperjoint->body->GetLocalCenter();

	LeftJointDef.localAnchorA.Set(LsetA.x, LsetA.y);
	LeftJointDef.localAnchorB.Set(LsetB.x, LsetB.y);

	LeftJointDef.enableLimit = true;
	LeftJointDef.lowerAngle = -30 * DEGTORAD;
	LeftJointDef.upperAngle = 25 * DEGTORAD;

	// --------------------------------------------RIGHT FLIPPER------------------------------------------

	RightFlipperjoint = App->physics->CreateCircle(210, 519, 6, b2_staticBody, 1.0f);
	RightFlipper = App->physics->CreateRectangle(204, 519, 45, 10, b2_dynamicBody);

	b2RevoluteJointDef RightJointDef;
	RightJointDef.bodyA = RightFlipper->body;
	RightJointDef.bodyB = RightFlipperjoint->body;
	RightJointDef.collideConnected = false;

	b2Vec2 RsetA = { 0.32f, 0.0f };
	b2Vec2 RsetB = RightFlipperjoint->body->GetLocalCenter();

	RightJointDef.localAnchorA.Set(RsetA.x, RsetA.y);
	RightJointDef.localAnchorB.Set(RsetB.x, RsetB.y);

	RightJointDef.enableLimit = true;
	RightJointDef.lowerAngle = -30 * DEGTORAD;
	RightJointDef.upperAngle = 25 * DEGTORAD;

	// --------------------------------------------------------------------------------------



	// LEFT FLIPPER
	LFlipperLeftFlipper = (b2RevoluteJoint*)App->physics->world->CreateJoint(&LeftJointDef);

	// RIGHT FLIPPER
	RFlipperRightFlipper = (b2RevoluteJoint*)App->physics->world->CreateJoint(&RightJointDef);

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
		LFlipperLeftFlipper->GetBodyA()->ApplyAngularImpulse(-0.3f, true);
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		RFlipperRightFlipper->GetBodyA()->ApplyAngularImpulse(0.3f, true);

	return UPDATE_CONTINUE;
}



