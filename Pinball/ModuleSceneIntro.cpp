#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	map_texture = App->textures->Load("pinball/map.png");
	ball = App->textures->Load("pinball/ball.png");


	int map_shape[98] = {
		233, 572,
		206, 558,
		206, 546,
		277, 510,
		280, 385,
		266, 372,
		265, 320,
		294, 306,
		294, 219,
		272, 205,
		270, 188,
		294, 177,
		291, 118,
		257, 117,
		248, 88,
		232, 65,
		209, 50,
		220, 36,
		248, 50,
		278, 78,
		294, 114,
		295, 147,
		294, 520,
		312, 520,
		312, 114,
		299, 82,
		279, 57,
		248, 33,
		217, 17,
		183, 10,
		144, 14,
		111, 27,
		85, 48,
		66, 70,
		75, 99,
		36, 119,
		23, 78,
		12, 72,
		4, 80,
		6, 122,
		14, 181,
		26, 240,
		48, 290,
		74, 323,
		29, 408,
		29, 509,
		106, 546,
		107, 554,
		90, 571
	};

	int bouncer_left[6]{
		96, 494,
		68, 436,
		65, 477,
	};
	int bouncer_right[6]{
		96, 494,
		124, 436,
		127, 477
	};


	// -------------------------------------------Spring-------------------------------------------------------
	
	spring = App->physics->CreateRectangle(304, 492, 11, 6, b2_dynamicBody);
	springSurface = App->physics->CreateRectangle(304, 503, 11, 10, b2_staticBody);



	b2PrismaticJointDef springJoint;
	springJoint.collideConnected = true;
	springJoint.bodyA = spring->body;
	springJoint.bodyB = springSurface->body;

	springJoint.localAnchorA.Set(0, 0);
	springJoint.localAnchorB.Set(0, -1);
	springJoint.localAxisA.Set(0, -1);
	springJoint.enableLimit = true;
	springJoint.lowerTranslation = -0.02;
	springJoint.upperTranslation = 1;
	(b2PrismaticJoint*)App->physics->world->CreateJoint(&springJoint);

	//--------------------------------------------------------------------------------------------------------
	map = App->physics->CreateChain(0, 0, map_shape, 98);
	map->body->SetType(b2_staticBody);
	map->body->GetFixtureList()->SetRestitution(0.5f);

	
	PhysBody* bouncers[5];

	bouncers[0] = App->physics->CreateCircle(180, 145, 18, b2_staticBody,1);
	bouncers[1] = App->physics->CreateCircle(135, 198, 18, b2_staticBody,1);
	bouncers[2] = App->physics->CreateCircle(219, 200, 18, b2_staticBody,1);
	bouncers[3] = App->physics->CreateChain(0, 0, bouncer_left, 6);
	bouncers[4] = App->physics->CreateChain(115, 0, bouncer_right, 6);

	for (int i = 0; i < 3; i++) {
		for (int i = 0; i < 5; i++) {
			if (i >= 3) {
				bouncers[i]->body->SetType(b2_staticBody);
				bouncers[i]->body->GetFixtureList()->SetRestitution(4);
			}
			else {
				bouncers[i]->body->GetFixtureList()->SetRestitution(1.5f);
			}
		}
	}


	boxes[0] = App->physics->CreateRectangle(21, 111, 15, 15, b2_staticBody);
	boxes[1] = App->physics->CreateRectangle(27, 127, 15, 15, b2_staticBody);
	boxes[2] = App->physics->CreateRectangle(33, 142, 15, 15, b2_staticBody);
	boxes[3] = App->physics->CreateRectangle(274, 224, 15, 15, b2_staticBody);
	boxes[4] = App->physics->CreateRectangle(282, 250, 15, 15, b2_staticBody);
	boxes[5] = App->physics->CreateRectangle(282, 278, 15, 15, b2_staticBody);
	boxes[6] = App->physics->CreateRectangle(271, 297, 15, 15, b2_staticBody);
	boxes[7] = App->physics->CreateRectangle(272, 511, 15, 15, b2_staticBody);
	boxes[8] = App->physics->CreateRectangle(34, 511, 15, 15, b2_staticBody);



	for (int i = 0; i < 9; i++) {
		boxes[i]->body->SetType(b2_staticBody);
		if (i >= 7) {
			boxes[i]->body->GetFixtureList()->SetRestitution(4);
		}
		else {
			boxes[i]->body->GetFixtureList()->SetRestitution(0.3f);
		}
	}

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 6, b2_dynamicBody, 2.0f));
		circles.getLast()->data->listener = this;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		spring->body->ApplyForce(b2Vec2(0, 10), b2Vec2(0, 0), true);
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		spring->body->ApplyForce(b2Vec2(0, -100), b2Vec2(0, 0), true);
	}
	
	
	App->renderer->Blit(map_texture, 0, 0, NULL, 1.0f);
		

	p2List_item<PhysBody*>* c = circles.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;


	
	for (int i = 0; i < 7; i++) {
		if (bodyB == boxes[i]) {
			
		}
	}

	
}
