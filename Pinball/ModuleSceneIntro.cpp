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


	skate.PushBack({ 164,0,164,162 });
	skate.PushBack({ 328,0,164,162 });
	skate.PushBack({ 656,0,164,162 });
	skate.PushBack({ 820,0,164,162 });
	skate.PushBack({ 984,0,164,162 });
	skate.PushBack({ 0,162,164,162 });
	skate.PushBack({ 164,162,164,162 });
	skate.PushBack({ 328,162,164,162 });
	skate.PushBack({ 656,162,164,162 });
	skate.PushBack({ 820,162,164,162 });
	skate.PushBack({ 984,162,164,162 });
	skate.speed = 0.2f; 

	skate_2.PushBack({0,0,110,140 });
	skate_2.PushBack({ 110,0,110,140 });
	skate_2.PushBack({ 220,0,110,140 });
	skate_2.PushBack({ 330,0,110,140 });
	skate_2.PushBack({ 440,0,110,140 });
	skate_2.PushBack({ 550,0,110,140 });
	skate_2.PushBack({ 660,0,110,140 });
	skate_2.PushBack({ 770,0,110,140 });
	skate_2.PushBack({ 880,0,110,140 });
	skate_2.PushBack({ 990,0,110,140 });
	skate_2.PushBack({ 1100,0,110,140 });
	skate_2.PushBack({ 1210,0,110,140 });
	skate_2.PushBack({ 0,140,110,140 });
	skate_2.PushBack({ 110,140,110,140 });
	skate_2.PushBack({ 220,140,110,140 });
	skate_2.PushBack({ 330,140,110,140 });
	skate_2.PushBack({ 440,140,110,140 });
	skate_2.PushBack({ 550,140,110,140 });
	skate_2.PushBack({ 660,140,110,140 });
	skate_2.PushBack({ 770,140,110,140 });
	skate_2.PushBack({ 880,140,110,140 });
	skate_2.PushBack({ 990,140,110,140 });
	skate_2.PushBack({ 1100,140,110,140 });
	skate_2.PushBack({ 1210,140,110,140 });
	skate_2.speed = 0.2f;

	greensensor1.PushBack({ 28,0,16,16 });
	greensensor1.speed = 0.01f;

	greensensor2.PushBack({ 0,77,12,12 });
	greensensor2.speed = 0.01f;

	greensensor3.PushBack({ 14,77,10,10 });
	greensensor3.speed = 0.01f;

	greensensor4.PushBack({ 27,77,7,7 });
	greensensor4.speed = 0.01f;

	redsensor.PushBack({ 77,0,16,16 });
	redsensor.speed = 0.01f;

	redsensor.PushBack({ 41,39,0,29 });
	redsensor.speed = 0.01f;

	shiny_bouncer.PushBack({ 0,29,36,36 });
	shiny_bouncer.speed = 0.2f;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->window->SetTitle("eXtreme Paintball");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	create = true;

	map_texture = App->textures->Load("pinball/map.png");
	ball = App->textures->Load("pinball/ball.png");
	box = App->textures->Load("pinball/box.png");
	skate_texture = App->textures->Load("pinball/skate.png");
	skate_texture_2 = App->textures->Load("pinball/skate2.png");
	sensors_texture = App->textures->Load("pinball/sensors.png");
	cones[0] = App->textures->Load("pinball/cone1.png");
	cones[1] = App->textures->Load("pinball/cone2.png");
	cones[2] = App->textures->Load("pinball/cone3.png");
	cones[3] = App->textures->Load("pinball/cone4.png");

	bouncersfx = App->audio->LoadFx("pinball/soundeffects/bouncers.wav");
	startfx = App->audio->LoadFx("pinball/soundeffects/start.wav");
	sensorsfx = App->audio->LoadFx("pinball/soundeffects/sensors.wav");
	bottombouncersfx = App->audio->LoadFx("pinball/soundeffects/bottombouncers.wav");
	bonusfx = App->audio->LoadFx("pinball/soundeffects/bonus.wav");
	boxesfx = App->audio->LoadFx("pinball/soundeffects/boxes.wav");
	ballfx = App->audio->LoadFx("pinball/soundeffects/ballbouncing.wav");

	

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

	BouncerSensors[0] = App->physics->CreateCircleSensor(180, 145, 22);
	BouncerSensors[1] = App->physics->CreateCircleSensor(135, 198, 22);
	BouncerSensors[2] = App->physics->CreateCircleSensor(219, 200, 22);

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

	skate1sensor = App->physics->CreateRectangleSensor(285,130,15,15);
	skate2sensor = App->physics->CreateRectangleSensor(65, 350, 15, 15);

	bouncers[0] = App->physics->CreateCircle(180, 145, 18, b2_staticBody,1);
	bouncers[1] = App->physics->CreateCircle(135, 198, 18, b2_staticBody,1);
	bouncers[2] = App->physics->CreateCircle(219, 200, 18, b2_staticBody,1);

	bouncers[3] = App->physics->CreateChain(0, 0, bouncer_left, 6);
	bouncers[4] = App->physics->CreateChain(115, 0, bouncer_right, 6);
	bouncers[3]->body->SetBullet(true);
	bouncers[4]->body->SetBullet(true);

	for (int i = 0; i < 3; i++) {
		for (int i = 0; i < 5; i++) {
			if (i >= 3) {
				bouncers[i]->body->SetType(b2_staticBody);
				bouncers[i]->body->GetFixtureList()->SetRestitution(1.0f);
			}
			else {
				bouncers[i]->body->GetFixtureList()->SetRestitution(1.0f);
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

	App->audio->PlayFx(startfx);
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(map_texture);
	App->textures->Unload(ball);
	App->textures->Unload(box);
	App->textures->Unload(skate_texture);
	App->textures->Unload(skate_texture_2);
	App->textures->Unload(sensors_texture);
	for (int i = 0; i < 4; i++) {
		App->textures->Unload(cones[i]);
	}


	/*
	map_texture = App->textures->Load("pinball/map.png");
	ball = App->textures->Load("pinball/ball.png");
	box = App->textures->Load("pinball/box.png");
	skate_texture = App->textures->Load("pinball/skate.png");
	skate_texture_2 = App->textures->Load("pinball/skate2.png");
	sensors_texture = App->textures->Load("pinball/sensors.png");
	cones[0] = App->textures->Load("pinball/cone1.png");
	cones[1] = App->textures->Load("pinball/cone2.png");
	cones[2] = App->textures->Load("pinball/cone3.png");
	cones[3] = App->textures->Load("pinball/cone4.png");

	bouncersfx = App->audio->LoadFx("pinball/soundeffects/bouncers.wav");
	startfx = App->audio->LoadFx("pinball/soundeffects/start.wav");
	sensorsfx = App->audio->LoadFx("pinball/soundeffects/sensors.wav");
	bottombouncersfx = App->audio->LoadFx("pinball/soundeffects/bottombouncers.wav");
	bonusfx = App->audio->LoadFx("pinball/soundeffects/bonus.wav");
	boxesfx = App->audio->LoadFx("pinball/soundeffects/boxes.wav");
	*/
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

	if (create == true && App->ui->lifes >= 0) 
	{
		Create();
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

	if (skate1 == true) {
		App->renderer->Blit(skate_texture, 175, 1, &(skate.GetCurrentFrame()));
		if (skate.current_frame == 0) {
			skate.Reset();
			skate1 = false;
		}
	}
	
	if (skate2 == true) {
		App->renderer->Blit(skate_texture_2,1, 274, &(skate_2.GetCurrentFrame()));
		if (skate_2.current_frame == 0) {
			skate_2.Reset();
			skate2 = false;
		}
	}

	//------------------------------------------------------------------------------
	if (ShinyBouncer1 == true) {
		App->renderer->Blit(sensors_texture, 162, 127, &(shiny_bouncer.GetCurrentFrame()));
		if (shiny_bouncer.current_frame == 0) {
			shiny_bouncer.Reset();
			ShinyBouncer1 = false;
		}
	}
	if (ShinyBouncer2 == true) {
		App->renderer->Blit(sensors_texture, 117, 181, &(shiny_bouncer.GetCurrentFrame()));
		if (shiny_bouncer.current_frame == 0) {
			shiny_bouncer.Reset();
			ShinyBouncer2 = false;
		}
	}
	if (ShinyBouncer3 == true) {
		App->renderer->Blit(sensors_texture, 201, 183, &(shiny_bouncer.GetCurrentFrame()));
		if (shiny_bouncer.current_frame == 0) {
			shiny_bouncer.Reset();
			ShinyBouncer3 = false;
		}
	
	}
	//------------------------------------------------------------------------------
	if (GreenSensor1 == true) {
		App->renderer->Blit(sensors_texture, 150, 19, &(greensensor1.GetCurrentFrame()));
		if (greensensor1.current_frame == 0) {
			greensensor1.Reset();
			GreenSensor1 = false;
		}
	}
	if (GreenSensor2 == true) {
		App->renderer->Blit(sensors_texture, 126, 29, &(greensensor2.GetCurrentFrame()));
		if (greensensor2.current_frame == 0) {
			greensensor2.Reset();
			GreenSensor2 = false;
		}
	}
	if (GreenSensor3 == true) {
		App->renderer->Blit(sensors_texture, 106, 40, &(greensensor3.GetCurrentFrame()));
		if (greensensor3.current_frame == 0) {
			greensensor3.Reset();
			GreenSensor3 = false;
		}
	
	}
	if (GreenSensor4 == true) {
		App->renderer->Blit(sensors_texture, 94, 58, &(greensensor4.GetCurrentFrame()));
		if (greensensor4.current_frame == 0) {
			greensensor4.Reset();
			GreenSensor4 = false;
		}
	}
	//------------------------------------------------------------------------------
	if (RedSensor1 == true) {
		App->renderer->Blit(sensors_texture, 126, 56, &(redsensor.GetCurrentFrame()));
		if (redsensor.current_frame == 0) {
			redsensor.Reset();
			RedSensor1 = false;
		}
	}
	if (RedSensor2 == true) {
		App->renderer->Blit(sensors_texture, 140, 85, &(redsensor.GetCurrentFrame()));
		if (redsensor.current_frame == 0) {
			redsensor.Reset();
			RedSensor2 = false;
		}
	}
	if (RedSensor3 == true) {
		App->renderer->Blit(sensors_texture, 162, 56, &(redsensor.GetCurrentFrame()));
		if (redsensor.current_frame == 0) {
			redsensor.Reset();
			RedSensor3 = false;
		}

	}
	if (RedSensor4 == true) {
		App->renderer->Blit(sensors_texture, 174, 85, &(redsensor.GetCurrentFrame()));
		if (redsensor.current_frame == 0) {
			redsensor.Reset();
			RedSensor4 = false;
		}
	}
	//------------------------------------------------------------------------------
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	if (bodyA == circles.getLast()->data) {
		App->audio->PlayFx(ballfx);
	}
	for (int i = 0; i < 13; i++)
	{
		if (bodyB == boxes[i]) 
		{			
			if( i>=9 ){
				App->ui->score += 25;
				App->audio->PlayFx(bouncersfx);
			}

			else if (i == 8 || i == 7) {
				toDestroy = boxes[i];
				boxes[i] = nullptr;
				App->ui->score += 25;
				App->audio->PlayFx(bottombouncersfx);
			}

			else {
				toDestroy = boxes[i];
				boxes[i] = nullptr;
				App->ui->score += 25;
				App->audio->PlayFx(boxesfx);
			}

		}
	}


	if (bodyB == end) {
		toDestroy = circles.getLast()->data;
		circles.clear();
		App->ui->lifes--;
		create = true;
	}

	if (bodyB == skate1sensor) {
		skate1 = true;
		App->audio->PlayFx(bonusfx);
	}

	if (bodyB == skate2sensor) {
		skate2 = true;
		App->audio->PlayFx(bonusfx);
	}

	//-----------------------------------------------------------

	if (bodyB == GreenSensors[0]) {
		GreenSensor1 = true;
		App->audio->PlayFx(sensorsfx);
		App->ui->score += 5;
	}
	if (bodyB == GreenSensors[1]) {
		GreenSensor2 = true;
		App->audio->PlayFx(sensorsfx);
		App->ui->score += 5;
	}
	if (bodyB == GreenSensors[2]) {
		GreenSensor3 = true;
		App->audio->PlayFx(sensorsfx);
		App->ui->score += 5;
	}
	if (bodyB == GreenSensors[3]) {
		GreenSensor4 = true;
		App->audio->PlayFx(sensorsfx); 
		App->ui->score += 5;
	}
	//-----------------------------------------------------------
	if (bodyB == RedSensors[0]) {
		RedSensor1 = true;
		App->audio->PlayFx(sensorsfx);
		App->ui->score += 5;
	}
	if (bodyB == RedSensors[1]) {
		RedSensor2 = true;
		App->audio->PlayFx(sensorsfx);
		App->ui->score += 5;
	}
	if (bodyB == RedSensors[2]) {
		RedSensor3 = true;
		App->audio->PlayFx(sensorsfx);
		App->ui->score += 5;
	}
	if (bodyB == RedSensors[3]) {
		RedSensor4 = true;
		App->audio->PlayFx(sensorsfx);
		App->ui->score += 5;
	}
	//-----------------------------------------------------------
	if (bodyB == BouncerSensors[0]) {
		ShinyBouncer1 = true;
		App->audio->PlayFx(bouncersfx);
		App->ui->score += 10;
	}
	if (bodyB == BouncerSensors[1]) {
		ShinyBouncer2 = true;
		App->audio->PlayFx(bouncersfx);
		App->ui->score += 10;
	}
	if (bodyB == BouncerSensors[2]) {
		ShinyBouncer3 = true;
		App->audio->PlayFx(bouncersfx);
		App->ui->score += 10;
	}

	
	
}
void ModuleSceneIntro::Destroy(){
	
	if (toDestroy != nullptr) {
		App->physics->world->DestroyBody(toDestroy->body);
		toDestroy = nullptr;
	}
}

void ModuleSceneIntro::Create()
{
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
	boxes[9] = App->physics->CreateRectangle(45, 285, 15, 15, b2_staticBody);
	boxes[10] = App->physics->CreateRectangle(263, 345, 15, 15, b2_staticBody);
	boxes[11] = App->physics->CreateRectangle(270, 195, 15, 15, b2_staticBody);
	boxes[12] = App->physics->CreateRectangle(70, 105, 15, 15, b2_staticBody);


	for (int i = 0; i < 13; i++) {
		boxes[i]->body->SetType(b2_staticBody);
		if (i >= 7) {
			boxes[i]->body->GetFixtureList()->SetRestitution(1.5f);
		}
		else {
			boxes[i]->body->GetFixtureList()->SetRestitution(0.2f);
		}
	}
	create = false;

}

