/*! \file walk.c
 *  \brief Walking gamestate.
 */
/*
 * Copyright (c) Sebastian Krzyszkowiak <dos@dosowisko.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "../common.h"
#include <allegro5/allegro_primitives.h>
#include <libsuperderpy.h>
#include <math.h>
#include <stdio.h>

struct GamestateResources {
	// This struct is for every resource allocated and used by your gamestate.
	// It gets created on load and then gets passed around to all other function calls.
	ALLEGRO_FONT* font;
	int option, blink;
	int offset;
	ALLEGRO_BITMAP* logo;

	ALLEGRO_SAMPLE* menu_sample;
	ALLEGRO_SAMPLE_INSTANCE* menu;
};

int Gamestate_ProgressCount = 1; // number of loading steps as reported by Gamestate_Load

static char* texts[] = {"Play", "Options", "Extras", "Quit",
	"Fullscreen: on", "Music: on", "Sounds: on", "Voice: on", "Pan to stereo channels: on", "Back",
	"Fullscreen: off", "Music: off", "Sounds: off", "Voice: off", "Pan to stereo channels: off", "Back"};

static void AdjustOption(struct Game* game, struct GamestateResources* data) {
	switch (data->option) {
		case 4:
			if (!game->config.fullscreen) {
				data->option += 6;
			}
#ifdef ALLEGRO_ANDROID
			data->option++;
#endif
			break;
		case 5:
			if (!game->config.music) {
				data->option += 6;
			}
			break;
		case 6:
			if (!game->config.fx) {
				data->option += 6;
			}
			break;
		case 7:
			if (!game->config.voice) {
				data->option += 6;
			}
			break;
		case 8:
			if (!game->data->pan) {
				data->option += 6;
			}
			break;
		case 10:
			if (game->config.fullscreen) {
				data->option -= 6;
			}
#ifdef ALLEGRO_ANDROID
			data->option++;
#endif
			break;
		case 11:
			if (game->config.music) {
				data->option -= 6;
			}
			break;
		case 12:
			if (game->config.fx) {
				data->option -= 6;
			}
			break;
		case 13:
			if (game->config.voice) {
				data->option -= 6;
			}
			break;
		case 14:
			if (game->data->pan) {
				data->option -= 6;
			}
			break;
	}
}

void Gamestate_Logic(struct Game* game, struct GamestateResources* data, double delta) {
	// Called 60 times per second. Here you should do all your game logic.
}

void Gamestate_Tick(struct Game* game, struct GamestateResources* data) {
	// Called 60 times per second (by default). Here you should do all your game
	// logic.
	data->blink++;
	if (data->blink >= 60) {
		data->blink = 0;
	}
	if (data->offset > 0) {
		data->offset--;
	}
}

void Gamestate_Draw(struct Game* game, struct GamestateResources* data) {
	// Called as soon as possible, but no sooner than next Gamestate_Logic call.
	// Draw everything to the screen here.

	al_draw_bitmap(data->logo, 0, 0, 0);

	int dy = data->offset;
	if (!game->data->touch) {
		dy = 0;
	}

	al_draw_filled_rectangle(0, 158 + dy, 320, 180, al_map_rgba(0, 0, 0, 64));

	if (data->blink < 45) {
		if (game->data->touch) {
			DrawTextWithShadow(data->font, al_map_rgb(255, 255, 255), 320 / 2.0, 165 + dy, ALLEGRO_ALIGN_CENTER, texts[data->option]);
			DrawTextWithShadow(data->font, al_map_rgb(255, 255, 255), 10, 165 + dy, ALLEGRO_ALIGN_LEFT, "<");
			DrawTextWithShadow(data->font, al_map_rgb(255, 255, 255), 310, 165 + dy, ALLEGRO_ALIGN_RIGHT, ">");
		} else {
			char text[255];
			snprintf(text, 255, "< %s >", texts[data->option]);
			DrawTextWithShadow(data->font, al_map_rgb(255, 255, 255), 320 / 2.0, 165, ALLEGRO_ALIGN_CENTER, text);
		}
	}
}

static void MenuSelect(struct Game* game, struct GamestateResources* data) {
	al_stop_sample_instance(game->data->button);
	al_play_sample_instance(game->data->button);
	data->blink = 0;
	switch (data->option) {
		case 0:
			SwitchCurrentGamestate(game, "game");
			break;
		case 1:
			data->option = 4;
			Speak(game, texts[data->option]);
			break;
		case 2:
			data->option = 14;
			Speak(game, texts[data->option]);
			break;
		case 3:
			UnloadAllGamestates(game);
			break;
		case 4:
		case 10:
			// fullscreen
			ToggleFullscreen(game);
			AdjustOption(game, data);
			Speak(game, texts[data->option]);
			break;
		case 5:
		case 11:
			// music
			game->config.music = game->config.music ? 0 : 10;
			SetConfigOption(game, "SuperDerpy", "music", game->config.music ? "10" : "0");
			al_set_mixer_gain(game->audio.music, game->config.music / 10.0);
			al_set_mixer_gain(game->data->audio.music, game->config.music / 10.0);
			AdjustOption(game, data);
			Speak(game, texts[data->option]);
			break;
		case 6:
		case 12:
			// sounds
			game->config.fx = game->config.fx ? 0 : 10;
			SetConfigOption(game, "SuperDerpy", "fx", game->config.fx ? "10" : "0");
			al_set_mixer_gain(game->audio.fx, game->config.fx / 10.0);
			al_set_mixer_gain(game->data->audio.fx, game->config.fx / 10.0);
			AdjustOption(game, data);
			Speak(game, texts[data->option]);
			break;
		case 7:
		case 13:
			// voices
			game->config.voice = game->config.voice ? 0 : 10;
			SetConfigOption(game, "SuperDerpy", "voice", game->config.voice ? "10" : "0");
			al_set_mixer_gain(game->audio.voice, game->config.voice / 10.0);
			al_set_mixer_gain(game->data->audio.voice, game->config.voice / 10.0);
			AdjustOption(game, data);
			Speak(game, texts[data->option]);
			break;
		case 8:
		case 14:
			game->data->pan = !game->data->pan;
			SetConfigOption(game, "ZjedzTrawke2", "pan", game->data->pan ? "1" : "0");
			AdjustOption(game, data);
			Speak(game, texts[data->option]);
			break;
		case 9:
		case 15:
			data->option = 0;
			Speak(game, texts[data->option]);
			break;
	}
}

static void MenuLeft(struct Game* game, struct GamestateResources* data) {
	al_stop_sample_instance(game->data->button);
	al_play_sample_instance(game->data->button);
	data->blink = 0;
	data->option--;

	if (data->option == 9) {
		data->option = 15;
	}
#ifdef ALLEGRO_ANDROID
	if (data->option == 10) {
		data->option = 15;
	}
#endif
	if (data->option == 3) {
		data->option = 9;
	}
#ifdef ALLEGRO_ANDROID
	if (data->option == 4) {
		data->option = 9;
	}
#endif
	if (data->option == -1) {
		data->option = 3;
	}

	if (data->option == 2) {
		data->option--;
	}

	AdjustOption(game, data);
	Speak(game, texts[data->option]);
}

static void MenuRight(struct Game* game, struct GamestateResources* data) {
	al_stop_sample_instance(game->data->button);
	al_play_sample_instance(game->data->button);
	data->blink = 0;
	data->option++;

	if (data->option == 4) {
		data->option = 0;
	}
	if (data->option == 10) {
		data->option = 4;
#ifdef ALLEGRO_ANDROID
		data->option++;
#endif
	}
	if (data->option == 16) {
		data->option = 10;
#ifdef ALLEGRO_ANDROID
		data->option++;
#endif
	}

	if (data->option == 2) {
		data->option++;
	}

	AdjustOption(game, data);
	Speak(game, texts[data->option]);
}

static void MenuEscape(struct Game* game, struct GamestateResources* data) {
	if (data->option >= 4) {
		al_stop_sample_instance(game->data->button);
		al_play_sample_instance(game->data->button);
		data->blink = 0;
		data->option = 0;
		Speak(game, texts[data->option]);
	} else {
		UnloadAllGamestates(game);
	}
}

void Gamestate_ProcessEvent(struct Game* game, struct GamestateResources* data, ALLEGRO_EVENT* ev) {
	// Called for each event in Allegro event queue.
	// Here you can handle user input, expiring timers etc.
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
		MenuEscape(game, data);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_BACK)) {
		MenuEscape(game, data);
	}
	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		if (ev->keyboard.keycode == ALLEGRO_KEY_LEFT) {
			MenuLeft(game, data);
		}
		if (ev->keyboard.keycode == ALLEGRO_KEY_RIGHT) {
			MenuRight(game, data);
		}

		if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER) {
			MenuSelect(game, data);
		}
	}

	if (ev->type == ALLEGRO_EVENT_TOUCH_BEGIN) {
		if ((ev->touch.primary) && (data->offset == 0)) {
			int x = (int)(ev->touch.x);
			int y = (int)(ev->touch.y);
			WindowCoordsToViewport(game, &x, &y);

			if ((y >= 158) && (y <= 180)) {
				if ((x >= 0) && (x < 40)) {
					MenuLeft(game, data);
				} else if ((x > 280) && (x <= 320)) {
					MenuRight(game, data);
				} else {
					MenuSelect(game, data);
				}
			}
		}
	}

	AdjustOption(game, data);
}

void* Gamestate_Load(struct Game* game, void (*progress)(struct Game*)) {
	// Called once, when the gamestate library is being loaded.
	// Good place for allocating memory, loading bitmaps etc.
	struct GamestateResources* data = malloc(sizeof(struct GamestateResources));
	int flags = al_get_new_bitmap_flags();
	al_set_new_bitmap_flags(flags ^ ALLEGRO_MAG_LINEAR); // disable linear scaling for pixelarty appearance
	data->font = al_create_builtin_font();
	progress(game); // report that we progressed with the loading, so the engine can draw a progress bar

	data->logo = al_load_bitmap(GetDataFilePath(game, "logo.png"));

	data->menu_sample = al_load_sample(GetDataFilePath(game, "menu.flac"));
	data->menu = al_create_sample_instance(data->menu_sample);
	al_attach_sample_instance_to_mixer(data->menu, game->audio.music);
	al_set_sample_instance_playmode(data->menu, ALLEGRO_PLAYMODE_LOOP);

	al_set_new_bitmap_flags(flags);
	return data;
}

void Gamestate_Unload(struct Game* game, struct GamestateResources* data) {
	// Called when the gamestate library is being unloaded.
	// Good place for freeing all allocated memory and resources.
	al_destroy_font(data->font);
	al_destroy_sample_instance(data->menu);
	free(data);
}

void Gamestate_Start(struct Game* game, struct GamestateResources* data) {
	// Called when this gamestate gets control. Good place for initializing state,
	// playing music etc.
	data->option = 0;
	data->blink = 0;
	data->offset = 30;
	al_play_sample_instance(data->menu);
#ifdef ALLEGRO_ANDROID
	game->data->touch = true;
#endif

	Speak(game, texts[0]);
}

void Gamestate_Stop(struct Game* game, struct GamestateResources* data) {
	// Called when gamestate gets stopped. Stop timers, music etc. here.
}

// Ignore those for now.
// TODO: Check, comment, refine and/or remove:
void Gamestate_Reload(struct Game* game, struct GamestateResources* data) {}
void Gamestate_Pause(struct Game* game, struct GamestateResources* data) {}
void Gamestate_Resume(struct Game* game, struct GamestateResources* data) {}
