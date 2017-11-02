#include "Application.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

#include<stdio.h>

ModuleUI::ModuleUI(Application * app, bool start_enabled) : Module (app, start_enabled)
{
	play.PushBack({ 0,0,98,48 });
	high_score.PushBack({ 0,48,197,46 });
}

ModuleUI::~ModuleUI() 
{
}

bool ModuleUI::Start() 
{
	bool ret = true;
	LOG("Loading UI");

	font_score = App->fonts->Load("pinball/font.png", "0123456789", 1);
	menu = App->textures->Load("pinball/menu.png");


	score = 0;
	lifes = 0;
	scoreaux = 0;

	return ret;
}

bool ModuleUI::CleanUp() 
{
	bool ret = true;

	LOG("Unloading UI");

	App->fonts->UnLoad(font_score);
	App->textures->Unload(menu);

	return ret;
}

update_status ModuleUI::Update() {

	char str[10];
	sprintf_s(str, "%i", score);
	App->fonts->BlitText(35, 10, font_score, str);

	char str2[10];
	sprintf_s(str2, "%i", lifes);
	if (lifes >= 0) {
		App->fonts->BlitText(275, 10, font_score, str2);
	}

	if (App->ui->lifes == 0) {
		SDL_Rect r;
		r.x = r.y = 0; r.h = 600; r.w = 338;
		App->renderer->DrawQuad(r, 0, 0, 0, 100);

		if (score > scoreaux) {
			scoreaux = score;
		}

		char str3[10];
		sprintf_s(str3, "%i", scoreaux);
		if (lifes >= 0) {
			App->fonts->BlitText(160, 330, font_score, str3);
		}

		App->renderer->Blit(menu, 120, 200, &(play.GetCurrentFrame()));
		App->renderer->Blit(menu, 75, 270, &(high_score.GetCurrentFrame()));
	}

	return UPDATE_CONTINUE;
}