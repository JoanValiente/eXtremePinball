#include "Module.h"
#include "Globals.h"



class ModuleUI : public Module
{

public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();


	bool Start();
	bool CleanUp();
	update_status Update();

	int score;
	int lifes;

private:
	int font_score;
	

};

