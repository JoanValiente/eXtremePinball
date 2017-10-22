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
	circle = NULL;
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

	circle = App->textures->Load("pinball/wheel.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);


	int map_shape[82] = {
		312, -88,
		314, -450,
		312, -466,
		298, -492,
		268, -526,
		231, -548,
		185, -561,
		153, -562,
		118, -548,
		89, -529,
		69, -508,
		77, -475,
		38, -454,
		26, -488,
		20, -502,
		2, -499,
		6, -437,
		21, -358,
		36, -312,
		59, -267,
		72, -250,
		52, -208,
		31, -166,
		30, -67,
		108, -26,
		109, -19,
		66, 29,
		290, 25,
		208, -14,
		208, -25,
		282, -61,
		280, -189,
		267, -202,
		266, -256,
		295, -268,
		296, -354,
		272, -367,
		272, -388,
		297, -397,
		297, -432,
		299, -89
	};

	PhysBody* map;
	map = App->physics->CreateChain(350, 650, map_shape, 82);
	map->body->SetType(b2_staticBody);
	map->body->GetFixtureList()->SetDensity(0.1f);

	
	PhysBody* bouncers[3];

	bouncers[0] = App->physics->CreateCircle(520, 220, 17, b2_staticBody);
	bouncers[1] = App->physics->CreateCircle(550, 270, 17, b2_staticBody);
	bouncers[2] = App->physics->CreateCircle(490, 270, 17, b2_staticBody);

	for (int i = 0; i < 3; i++) {
		bouncers[i]->body->GetFixtureList()->SetRestitution(1.5f);
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
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 6, b2_dynamicBody));
		circles.getLast()->data->listener = this;
	}
	
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
