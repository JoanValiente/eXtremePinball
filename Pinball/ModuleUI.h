#include "Module.h"
#include "Globals.h"
#include "Animation.h"


struct SDL_Texture;

class ModuleUI : public Module
{

public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();


	bool Start();
	bool CleanUp();
	update_status Update();

	int score;
	int scoreaux;
	int lifes;

	SDL_Texture* menu;

	Animation play;
	Animation high_score;


private:
	int font_score;
	

};

