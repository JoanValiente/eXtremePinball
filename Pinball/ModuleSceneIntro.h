#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

class PhysBody;
struct SDL_Texture;

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
	void Create();

public:
	p2List<PhysBody*> circles;
	PhysBody* boxes[13];
	PhysBody* map;
	PhysBody* bouncers[5];
	PhysBody* walls[5];
	PhysBody* end;
	PhysBody* GreenSensors[4];
	PhysBody* RedSensors[4];
	PhysBody* BouncerSensors[3];
	PhysBody* toDestroy;

	SDL_Texture* map_texture;
	SDL_Texture* ball;
	SDL_Texture* box;
	SDL_Texture* cones[4];
	SDL_Texture* skate_texture;
	SDL_Texture* skate_texture_2;
	SDL_Texture* sensors_texture;
	SDL_Texture* bouncer;
	SDL_Texture* metal;

	Animation skate;
	Animation skate_2;
	Animation greensensor1;
	Animation greensensor2;
	Animation greensensor3;
	Animation greensensor4;
	Animation redsensor;
	Animation shiny_bouncer;

	uint bonusfx;
	uint bottombouncersfx;
	uint bouncersfx;
	uint boxesfx;
	uint sensorsfx;
	uint startfx;

private:
	PhysBody *spring;
	PhysBody *springSurface;
	PhysBody *limit;
	
	float springDown = 1.4f;
	bool create;
	bool skate1 = false;
	bool skate2 = false;
	//-----------------------------------------------
	bool GreenSensor1 = false;
	bool GreenSensor2 = false;
	bool GreenSensor3 = false;
	bool GreenSensor4 = false;
	//----------------------------------------------
	bool RedSensor1 = false;
	bool RedSensor2 = false;
	bool RedSensor3 = false;
	bool RedSensor4 = false;
	//----------------------------------------------
	bool ShinyBouncer1 = false;
	bool ShinyBouncer2 = false;
	bool ShinyBouncer3 = false;
	//----------------------------------------------
	bool ShinySensor = false;
	PhysBody* sensor;
	PhysBody* skate1sensor;
	PhysBody* skate2sensor;
	bool sensed;
};

