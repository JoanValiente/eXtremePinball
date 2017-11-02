#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleWindow.h"
#include "ModuleUI.h"

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

	create = true;

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	map_texture = App->textures->Load("pinball/map.png");
	ball = App->textures->Load("pinball/ball.png");
	box = App->textures->Load("pinball/box.png");
	cones[0] = App->textures->Load("pinball/cone1.png");
	cones[1] = App->textures->Load("pinball/cone2.png");
	cones[2] = App->textures->Load("pinball/cone3.png");
	cones[3] = App->textures->Load("pinball/cone4.png");

	

	int map_shape[98] = {
		520, 750,
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
		294, 540,
		312, 540,
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
		0, 750
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

	int beam[8]{
		107, 63,
		119, 57,
		133, 86,
		122, 92
	};

	int wall_left[]{
		44, 428,
		49, 428,
		49, 484,
		98, 510,
		92, 515,
		44, 488
	};


	int wall_right[]{
		258, 429,
		264, 429,
		264, 488,
		220, 516,
		218, 510,
		258, 486
	};

	//-------------------------------------------Sensors-------------------------------------------------------

	GreenSensors[0] = App->physics->CreateRectangleSensor(158, 27, 15, 16);
	GreenSensors[1] = App->physics->CreateRectangleSensor(132, 35, 12, 12);
	GreenSensors[2] = App->physics->CreateRectangleSensor(111, 45, 10, 10);
	GreenSensors[3] = App->physics->CreateRectangleSensor(96, 60, 7, 7);

	RedSensors[0] = App->physics->CreateRectangleSensor(131, 61, 11, 11);
	RedSensors[1] = App->physics->CreateRectangleSensor(145, 90, 11, 11);
	RedSensors[2] = App->physics->CreateRectangleSensor(167, 61, 11, 11);
	RedSensors[3] = App->physics->CreateRectangleSensor(179, 90, 11, 11);

	// -------------------------------------------Spring-------------------------------------------------------
	
	spring = App->physics->CreateRectangle(303, 450, 15, 4, b2_dynamicBody);
	springSurface = App->physics->CreateRectangle(303, 525, 15, 10, b2_staticBody);
	spring->body->GetFixtureList()->SetDensity(8.0f);
	
	b2PrismaticJointDef springJoint;
	springJoint.collideConnected = true;
	springJoint.bodyA = spring->body;
	springJoint.bodyB = springSurface->body;

	springJoint.localAnchorA.Set(0, 0);
	springJoint.localAnchorB.Set(0, -0.65f);
	springJoint.localAxisA.Set(0, -1);
	springJoint.enableLimit = true;
	springJoint.lowerTranslation = -0.02;
	springJoint.upperTranslation = 1;
	(b2PrismaticJoint*)App->physics->world->CreateJoint(&springJoint);



	//--------------------------------------------------------------------------------------------------------
	map = App->physics->CreateChain(0, 0, map_shape, 98);
	map->body->SetType(b2_staticBody);
	map->body->GetFixtureList()->SetRestitution(0.5f);

	end = App->physics->CreateRectangleSensor(150, 700, 400, 10);


	bouncers[0] = App->physics->CreateCircle(180, 145, 18, b2_staticBody,1);
	bouncers[1] = App->physics->CreateCircle(135, 198, 18, b2_staticBody,1);
	bouncers[2] = App->physics->CreateCircle(219, 200, 18, b2_staticBody,1);
	bouncers[3] = App->physics->CreateChain(0, 0, bouncer_left, 6);
	bouncers[4] = App->physics->CreateChain(115, 0, bouncer_right, 6);

	for (int i = 0; i < 3; i++) {
		for (int i = 0; i < 5; i++) {
			if (i >= 3) {
				bouncers[i]->body->SetType(b2_staticBody);
				bouncers[i]->body->GetFixtureList()->SetRestitution(1.5f);
			}
			else {
				bouncers[i]->body->GetFixtureList()->SetRestitution(1.5f);
			}
		}
	}

	walls[0] = App->physics->CreateChain(0, 0, beam, 8);
	walls[1] = App->physics->CreateChain(35, 0, beam, 8);
	walls[2] = App->physics->CreateChain(70, 0, beam, 8);
	walls[3] = App->physics->CreateChain(0, 0, wall_left, 12);
	walls[4] = App->physics->CreateChain(0, 0, wall_right, 12);


	for (int i = 0; i < 5; i++) {
		walls[i]->body->SetType(b2_staticBody);
		if (i < 3) {
			walls[i]->body->GetFixtureList()->SetRestitution(0.5f);
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
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && circles.count() == 0)
	{
		circles.add(App->physics->CreateCircle(304, 350, 6, b2_dynamicBody, 1.0f));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN && circles.count() == 0){
			circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 6, b2_dynamicBody, 1.0f));
			circles.getLast()->data->listener = this;
			circles.getLast()->data->body->SetBullet(true);
	}

	if (create == true) {

		/*
		circles.add(App->physics->CreateCircle(304, 350, 6, b2_dynamicBody, 1.0f));
		circles.getLast()->data->listener = this;
		circles.getLast()->data->body->SetBullet(true);
		*/

		for (int i = 0; i < 9; i++) {
			if (boxes[i] != nullptr) {
				App->physics->world->DestroyBody(boxes[i]->body);
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
				boxes[i]->body->GetFixtureList()->SetRestitution(2.5f);
			}
			else {
				boxes[i]->body->GetFixtureList()->SetRestitution(0.2f);
			}
		}
		create = false;
	}

	spring->body->ApplyForce(b2Vec2(0, -20), b2Vec2(0, 0), true);


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		spring->body->ApplyForce(b2Vec2(0, 21), b2Vec2(0, 0), true);
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

	for (int i = 0; i < 7; i++) {
		int x, y;
		if (boxes[i] != nullptr) {
			boxes[i]->GetPosition(x, y);
			if (i < 3) {
					App->renderer->Blit(box, x, y, NULL);
			}
			else if (i < 7) {
				App->renderer->Blit(cones[i - 3], x - 4, y, NULL);
			}
				
		}
	}

	Destroy();

	App->window->SetTitle("eXtreme Paintball");

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	for (int i = 0; i < 9; i++)
	{
		if (bodyB == boxes[i]) 
		{
			toDestroy = boxes[i];
			boxes[i] = nullptr;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (bodyB == bouncers[i]) 
		{
			App->ui->score += 10;

		}
	}

	if (bodyB == end) {
		toDestroy = circles.getLast()->data;
		circles.clear();
		App->ui->lifes--;
		create = true;
	}

}
void ModuleSceneIntro::Destroy(){
	
	if (toDestroy != nullptr) {
		App->physics->world->DestroyBody(toDestroy->body);
		toDestroy = nullptr;
	}
}