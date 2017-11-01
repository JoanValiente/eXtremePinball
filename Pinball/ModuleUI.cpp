#include "Application.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include<stdio.h>

ModuleUI::ModuleUI(Application * app, bool start_enabled) : Module (app, start_enabled)
{
}

ModuleUI::~ModuleUI() 
{
}

bool ModuleUI::Start() 
{
	bool ret = true;
	LOG("Loading UI");

	font_score = App->fonts->Load("pinball/font.png", "0123456789", 1);

	score = 0;
	lifes = 5;

	return ret;
}

bool ModuleUI::CleanUp() 
{
	bool ret = true;

	LOG("Unloading UI");

	App->fonts->UnLoad(font_score);

	return ret;
}

update_status ModuleUI::Update() {

	char str[10];
	sprintf_s(str, "%i", score);
	App->fonts->BlitText(50, 10, font_score, str);

	char str2[10];
	sprintf_s(str2, "%i", lifes);
	App->fonts->BlitText(260, 10, font_score, str2);



	return UPDATE_CONTINUE;
}