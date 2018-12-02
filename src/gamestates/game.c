/*! \file empty.c
 *  \brief Empty gamestate.
 */
/*
 * Copyright (c) Sebastian Krzyszkowiak <dos@dosowisko.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../common.h"
#include <libsuperderpy.h>

#define SPEED 1.1
#define MAZE_WIDTH 6
#define MAZE_HEIGHT 4

enum direction {
	up,
	down,
	left,
	right
};

struct RhythmPulse {
	float timer;
	int status;
	struct RhythmPulse* next;
	int id;
};

struct GamestateResources {
	// This struct is for every resource allocated and used by your gamestate.
	// It gets created on load and then gets passed around to all other function
	// calls.
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* pulseBitmap;
	ALLEGRO_BITMAP* pointer;
	ALLEGRO_BITMAP* grass;
	ALLEGRO_BITMAP* tile;

	struct Player* player1;
	struct Player* player2;
	char* map;
	int xGrass;
	int yGrass;

	unsigned int pos1, pos2;

	ALLEGRO_SAMPLE *music_sample, *ding_sample, *tada_sample, *no_sample;

	bool ended;
	struct Player* winner;
	struct Tween endtween;
};

struct Player {
	int x, y;
	char* text;
	float angle;
	ALLEGRO_BITMAP* player;
	int score;
	struct RhythmPulse* rhythmPulse;
	ALLEGRO_SAMPLE_INSTANCE *music, *ding, *tada, *no;
};

int Gamestate_ProgressCount = 29; // number of loading steps as reported by Gamestate_Load

static float Abs(float a) {
	if (a >= 0) {
		return a;
	}
	return -a;
}

static void IsGoodPressed(struct Game* game, struct RhythmPulse* pulse, struct Player* player,
	struct GamestateResources* data, enum direction direction) {
	float point = pulse->timer;
	if (point <= 0.25f && point > -0.25f) {
		if (Abs(point) <= 0.25f && pulse->status == -1) {
			pulse->status = (int)(100 - Abs((point)*400));
			player->text = "Good!";
			player->score += pulse->status;
			if (Abs(point) <= 0.15f) {
				player->text = "Excellent!";
			}
			if (Abs(point) <= 0.05f) {
				player->text = "Perfect!";
			}

			switch (direction) {
				case up:
					if (player->y > 0) {
						if (data->map[player->x + (player->y - 1) * MAZE_WIDTH] != 1) {
							player->y--;
							player->angle = 1.5 * ALLEGRO_PI;
						}
					}
					break;
				case down:
					if (player->y < MAZE_HEIGHT - 1) {
						if (data->map[player->x + (player->y + 1) * MAZE_WIDTH] != 1) {
							player->y++;
							player->angle = 0.5 * ALLEGRO_PI;
						}
					}
					break;
				case left:
					if (player->x > 0) {
						if (data->map[player->x - 1 + player->y * MAZE_WIDTH] != 1) {
							player->x--;
							player->angle = ALLEGRO_PI;
						}
					}
					break;
				case right:
					if (player->x < MAZE_WIDTH - 1) {
						if (data->map[player->x + 1 + player->y * MAZE_WIDTH] != 1) {
							player->x++;
							player->angle = 0;
						}
					}
					break;
			}
			al_stop_sample_instance(player->ding);
			al_set_sample_instance_speed(player->ding, 1.0 - Abs(point));
			al_play_sample_instance(player->ding);
			if (player->x == data->xGrass && player->y == data->yGrass) {
				// winning condition
				data->ended = true;
				data->winner = player;
				data->endtween = Tween(game, 100.0, 0.0, TWEEN_STYLE_BOUNCE_OUT, 1.5);
				al_stop_sample_instance(data->player1->music);
				al_stop_sample_instance(data->player2->music);
				al_play_sample_instance(player->tada);
				if (player == data->player1) {
					al_play_sample_instance(data->player2->no);
				} else {
					al_play_sample_instance(data->player1->no);
				}
			}

		} else {
			player->text = "Bad!";
			pulse->status = 0;

			if (player->score >= 50) {
				player->score -= 50;
			}
			if (player->score < 50) {
				player->score = 0;
			}
		}
	}
	if (point <= -0.25f) {
		IsGoodPressed(game, pulse->next, player, data, direction);
	}
}

static void DrawMap(struct Player* player, struct Player* otherPlayer,
	struct GamestateResources* data, float x, float y) {
	int i, j;

	for (i = -3; i < 3; i++) {
		if (i + player->x < 0 || i + player->x >= MAZE_WIDTH) { continue; }
		for (j = -3; j < 3; j++) {
			if (j + player->y < 0 || j + player->y >= MAZE_HEIGHT) { continue; }
			int id = i + player->x + (j + player->y) * MAZE_WIDTH;
			if (!data->map[id]) {
				al_draw_bitmap_region(data->tile, 0, 0, 16, 16,
					x + i * 16,
					y + j * 16, 0);
			}
			if (j + player->y == data->yGrass && i + player->x == data->xGrass) {
				al_draw_bitmap_region(data->grass, 0, 0, 16, 16,
					x + i * 16,
					y + j * 16, 0);
			}

			if (id == (otherPlayer->x + otherPlayer->y * MAZE_WIDTH)) {
				al_draw_tinted_rotated_bitmap(otherPlayer->player, al_map_rgb(96, 96, 96), 8, 8, x + i * 16 - 8 + 16, y + j * 16 - 8 + 16, otherPlayer->angle, 0);
			}
			if (id == (player->x + player->y * MAZE_WIDTH)) {
				al_draw_rotated_bitmap(player->player, 8, 8, x + i * 16 - 8 + 16, y + j * 16 - 8 + 16, player->angle, 0);
			}
		}
	}
}

static void DeleteDeltaTimeFromPulse(struct RhythmPulse* pulse, float deltaTime,
	struct Player* data) {
	float progress = (data->score) / 20000.0f;
	float delatTime = (deltaTime * SPEED) * ((progress + 1));
	al_set_sample_instance_speed(data->music, delatTime / deltaTime);
	if (pulse->timer > -0.25f && pulse->timer - delatTime < -0.25f &&
		pulse->status == -1) {
		pulse->status = 0;
		data->text = "Too Late!";
		if (data->score >= 50) {
			data->score -= 50;
		}
		if (data->score < 50) {
			data->score = 0;
		}
	}
	pulse->timer -= delatTime;

	if (pulse->next) {
		DeleteDeltaTimeFromPulse(pulse->next, deltaTime, data);
	}
}

static void MoveEnd(struct RhythmPulse* pulse, struct RhythmPulse* onEnd, float offset) {
	if (pulse->next == NULL) {
		pulse->next = onEnd;
		onEnd->next = NULL;
		onEnd->status = -1;
		onEnd->id = pulse->id + 1;
		if (onEnd->id % 3 == 2) {
			offset += 1.0;
		}
		onEnd->timer = pulse->timer + offset;
	} else {
		MoveEnd(pulse->next, onEnd, offset);
	}
}

void Gamestate_Logic(struct Game* game, struct GamestateResources* data,
	double delta) {
	if (data->ended) {
		UpdateTween(&data->endtween, delta);
		return;
	}

	DeleteDeltaTimeFromPulse(data->player2->rhythmPulse, delta, data->player2);
	DeleteDeltaTimeFromPulse(data->player1->rhythmPulse, delta, data->player1);
	if (data->player1->rhythmPulse->timer < -5.0f) {
		struct RhythmPulse* pulse = data->player1->rhythmPulse;
		data->player1->rhythmPulse = data->player1->rhythmPulse->next;
		MoveEnd(data->player1->rhythmPulse, pulse, 1);
	}
	if (data->player2->rhythmPulse->timer < -5.0f) {
		struct RhythmPulse* pulse = data->player2->rhythmPulse;
		data->player2->rhythmPulse = data->player2->rhythmPulse->next;
		MoveEnd(data->player2->rhythmPulse, pulse, 1);
	}
}

void Gamestate_Tick(struct Game* game, struct GamestateResources* data) {
	// Called 60 times per second (by default). Here you should do all your game
	// logic.
}

static void DrawAllPulse(struct RhythmPulse* pulse, struct Game* game,
	struct GamestateResources* data, float x) {
	al_draw_bitmap_region(data->pulseBitmap, 0, 0, 20, 20, x,
		game->viewport.height / 2.0 - 10 + pulse->timer * 40,
		0);
	//al_draw_textf(data->font, al_map_rgb(0, 0, 0), x + 3, game->viewport.height / 2.0 - 10 + pulse->timer * 40 + 3, ALLEGRO_ALIGN_LEFT, "%d", pulse->id);

	if (pulse->next) {
		DrawAllPulse(pulse->next, game, data, x);
	}
}

void Gamestate_Draw(struct Game* game, struct GamestateResources* data) {
	// Called as soon as possible, but no sooner than next Gamestate_Logic call.
	// Draw everything to the screen here.

	DrawMap(data->player1, data->player2, data, 80, 60);
	DrawMap(data->player2, data->player1, data, 250, 60);

	DrawAllPulse(data->player1->rhythmPulse, game, data,
		game->viewport.width / 2.0 - 25);
	DrawAllPulse(data->player2->rhythmPulse, game, data,
		game->viewport.width / 2.0 + 5);
	al_draw_bitmap_region(data->pointer, 0, 0, 20, 20,
		game->viewport.width / 2.0 - 25,
		game->viewport.height / 2.0f - 10, 0);
	al_draw_bitmap_region(data->pointer, 0, 0, 20, 20,
		game->viewport.width / 2.0 + 5,
		game->viewport.height / 2.0f - 10, 0);

	al_draw_text(data->font, al_map_rgb(255, 255, 255), game->viewport.width / 4.0,
		game->viewport.height / 1.3f, ALLEGRO_ALIGN_CENTRE,
		data->player1->text);
	al_draw_text(data->font, al_map_rgb(255, 255, 255),
		game->viewport.width * 3 / 4.0, game->viewport.height / 1.3f,
		ALLEGRO_ALIGN_CENTRE, data->player2->text);

	if (data->ended) {
		double offset = GetTweenValue(&data->endtween);

		al_draw_filled_rectangle(0, 0, game->viewport.width, game->viewport.height, al_map_rgba(0, 0, 0, 222));

		al_draw_bitmap(data->winner->player, game->viewport.width / 2.0 - al_get_bitmap_width(data->winner->player) / 2.0, game->viewport.height / 2.0 - 20 - offset, 0);
		al_draw_textf(data->font, al_map_rgb(255, 255, 255), game->viewport.width / 2.0, game->viewport.height / 2.0 - offset, ALLEGRO_ALIGN_CENTER, "%s player wins!", data->winner == data->player1 ? "Left" : "Right");

		if (fmod(game->time, 1.0) > 0.2) {
			al_draw_text(data->font, al_map_rgb(255, 255, 255), game->viewport.width / 2.0, 140, ALLEGRO_ALIGN_CENTER, "<ESCAPE>");
		}
	}
}

void Gamestate_ProcessEvent(struct Game* game, struct GamestateResources* data,
	ALLEGRO_EVENT* ev) {
	// Called for each event in Allegro event queue.
	// Here you can handle user input, expiring timers etc.
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
		SwitchCurrentGamestate(game, "menu");
	}
	if (data->ended) {
		return;
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		ev->keyboard.keycode == ALLEGRO_KEY_A) {
		IsGoodPressed(game, data->player1->rhythmPulse, data->player1, data, left);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_S)) {
		IsGoodPressed(game, data->player1->rhythmPulse, data->player1, data, down);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_W)) {
		IsGoodPressed(game, data->player1->rhythmPulse, data->player1, data, up);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_D)) {
		IsGoodPressed(game, data->player1->rhythmPulse, data->player1, data, right);
	}

	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		ev->keyboard.keycode == ALLEGRO_KEY_LEFT) {
		IsGoodPressed(game, data->player2->rhythmPulse, data->player2, data, left);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_DOWN)) {
		IsGoodPressed(game, data->player2->rhythmPulse, data->player2, data, down);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_UP)) {
		IsGoodPressed(game, data->player2->rhythmPulse, data->player2, data, up);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_RIGHT)) {
		IsGoodPressed(game, data->player2->rhythmPulse, data->player2, data, right);
	}
}

static void CarveMaze(char* maze, int width, int height, int x, int y) {
	int x1, y1;
	int x2, y2;
	int dx, dy;
	int dir, count;

	dir = rand() % 4;
	count = 0;
	while (count < 4) {
		dx = 0;
		dy = 0;
		switch (dir) {
			case 0:
				dx = 1;
				break;
			case 1:
				dy = 1;
				break;
			case 2:
				dx = -1;
				break;
			default:
				dy = -1;
				break;
		}
		x1 = x + dx;
		y1 = y + dy;
		x2 = x1 + dx;
		y2 = y1 + dy;
		if (x2 > 0 && x2 < width && y2 > 0 && y2 < height &&
			maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
			maze[y1 * width + x1] = 0;
			maze[y2 * width + x2] = 0;
			x = x2;
			y = y2;
			dir = rand() % 4;
			count = 0;
		} else {
			dir = (dir + 1) % 4;
			count += 1;
		}
	}
}

/* Generate maze in matrix maze with size width, height. */
static void GenerateMaze(char* maze, int width, int height) {
	int x, y;

	/* Initialize the maze. */
	for (x = 0; x < width * height; x++) {
		maze[x] = 1;
	}
	maze[1 * width + 1] = 0;

	/* Carve the maze. */
	for (y = 1; y < height; y += 2) {
		for (x = 1; x < width; x += 2) {
			CarveMaze(maze, width, height, x, y);
		}
	}

	/* Set up the entry and exit. */
	maze[0 * width + 1] = 0;
	maze[(height - 1) * width + (width - 2)] = 0;
}

/* Display the maze. */
static void ShowMaze(const char* maze, int width, int height) {
	int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			switch (maze[y * width + x]) {
				case 1:
					printf("[]");
					break;
				case 2:
					printf("<>");
					break;
				default:
					printf("  ");
					break;
			}
		}
		printf("\n");
	}
}

void* Gamestate_Load(struct Game* game, void (*progress)(struct Game*)) {
	// Called once, when the gamestate library is being loaded.
	// Good place for allocating memory, loading bitmaps etc.
	//
	// NOTE: Depending on engine configuration, this may be called from a separate
	// thread.
	// Unless you're sure what you're doing, avoid using drawing calls and other
	// things that
	// require main OpenGL context.

	struct GamestateResources* data = calloc(1, sizeof(struct GamestateResources));
	int flags = al_get_new_bitmap_flags();
	al_set_new_bitmap_flags(flags ^ ALLEGRO_MAG_LINEAR); // disable linear scaling for pixelarty appearance
	data->font = al_create_builtin_font();
	data->pulseBitmap = al_load_bitmap(GetDataFilePath(game, "Sprites/rythmPulse.png"));
	data->pointer = al_load_bitmap(GetDataFilePath(game, "Sprites/line.png"));
	data->tile = al_load_bitmap(GetDataFilePath(game, "Sprites/tile.png"));
	data->grass = al_load_bitmap(GetDataFilePath(game, "Sprites/grass.png"));
	progress(game); // report that we progressed with the loading, so the engine
	// can move a progress bar
	data->player1 = malloc(sizeof(struct Player));
	data->player2 = malloc(sizeof(struct Player));
	data->player1->text = "";
	data->player1->rhythmPulse = malloc(sizeof(struct RhythmPulse));
	data->player1->rhythmPulse->timer = 0;
	data->player1->rhythmPulse->id = 0;
	data->player1->score = 0;
	data->player1->angle = 0.5 * ALLEGRO_PI;
	(*progress)(game);

	data->player1->player = al_load_bitmap(GetDataFilePath(game, "Sprites/swinka_kolor.png"));
	(*progress)(game);
	data->player2->player = al_load_bitmap(GetDataFilePath(game, "Sprites/swinka_czb.png"));
	(*progress)(game);

	data->player2->text = "";
	data->player2->rhythmPulse = malloc(sizeof(struct RhythmPulse));
	data->player2->rhythmPulse->timer = 0;
	data->player2->rhythmPulse->id = 0;
	data->player2->score = 0;
	data->player2->angle = 0.5 * ALLEGRO_PI;
	(*progress)(game);

	data->map = malloc(MAZE_WIDTH * MAZE_HEIGHT * sizeof(char));
	GenerateMaze(data->map, MAZE_WIDTH, MAZE_HEIGHT);
	ShowMaze(data->map, MAZE_WIDTH, MAZE_HEIGHT);
	struct RhythmPulse* pulse = data->player1->rhythmPulse;
	pulse->status = -1;
	pulse->timer = 0;
	int i;
	for (i = 1; i <= 10; i++) {
		if (i % 4 == 3) {
			continue;
		}
		pulse->next = malloc(sizeof(struct RhythmPulse));
		pulse = pulse->next;
		pulse->timer = (float)i;
		pulse->status = -1;
		pulse->id = i;
		(*progress)(game);
	}
	pulse->next = NULL;

	struct RhythmPulse* pulse2 = data->player2->rhythmPulse;
	pulse2->status = -1;
	pulse2->timer = 0;
	for (i = 1; i <= 10; i++) {
		if (i % 4 == 3) {
			continue;
		}
		pulse2->next = malloc(sizeof(struct RhythmPulse));
		pulse2 = pulse2->next;
		pulse2->timer = (float)i;
		pulse2->status = -1;
		pulse2->id = i;
		(*progress)(game);
	}
	pulse2->next = NULL;
	data->player1->x = 1;
	data->player1->y = 0;
	data->player2->x = 1;
	data->player2->y = 0;
	int j;
	char flag = 0;
	for (i = MAZE_WIDTH - 1; i >= 0; i--) {
		for (j = MAZE_HEIGHT - 1; j >= 0; j--) {
			if (data->map[i + (j)*MAZE_WIDTH] != 1) {
				data->xGrass = i;
				data->yGrass = j;
				flag = 1;
				break;
			}
		}
		if (flag) {
			break;
		}
	}

	data->music_sample = al_load_sample(GetDataFilePath(game, "music.flac"));
	data->player1->music = al_create_sample_instance(data->music_sample);
	al_attach_sample_instance_to_mixer(data->player1->music, game->audio.music);
	al_set_sample_instance_playmode(data->player1->music, ALLEGRO_PLAYMODE_LOOP);
	(*progress)(game);

	data->player2->music = al_create_sample_instance(data->music_sample);
	al_attach_sample_instance_to_mixer(data->player2->music, game->data->audio.music);
	al_set_sample_instance_playmode(data->player2->music, ALLEGRO_PLAYMODE_LOOP);
	(*progress)(game);

	data->ding_sample = al_load_sample(GetDataFilePath(game, "ding.flac"));
	data->player1->ding = al_create_sample_instance(data->ding_sample);
	al_attach_sample_instance_to_mixer(data->player1->ding, game->audio.fx);
	al_set_sample_instance_playmode(data->player1->ding, ALLEGRO_PLAYMODE_ONCE);
	(*progress)(game);

	data->player2->ding = al_create_sample_instance(data->ding_sample);
	al_attach_sample_instance_to_mixer(data->player2->ding, game->data->audio.fx);
	al_set_sample_instance_playmode(data->player2->ding, ALLEGRO_PLAYMODE_ONCE);
	(*progress)(game);

	data->no_sample = al_load_sample(GetDataFilePath(game, "no.flac"));
	data->player1->no = al_create_sample_instance(data->no_sample);
	al_attach_sample_instance_to_mixer(data->player1->no, game->audio.fx);
	al_set_sample_instance_playmode(data->player1->no, ALLEGRO_PLAYMODE_ONCE);
	(*progress)(game);

	data->player2->no = al_create_sample_instance(data->no_sample);
	al_attach_sample_instance_to_mixer(data->player2->no, game->data->audio.fx);
	al_set_sample_instance_playmode(data->player2->no, ALLEGRO_PLAYMODE_ONCE);
	(*progress)(game);

	data->tada_sample = al_load_sample(GetDataFilePath(game, "tada.flac"));
	data->player1->tada = al_create_sample_instance(data->tada_sample);
	al_attach_sample_instance_to_mixer(data->player1->tada, game->audio.fx);
	al_set_sample_instance_playmode(data->player1->tada, ALLEGRO_PLAYMODE_ONCE);
	(*progress)(game);

	data->player2->tada = al_create_sample_instance(data->tada_sample);
	al_attach_sample_instance_to_mixer(data->player2->tada, game->data->audio.fx);
	al_set_sample_instance_playmode(data->player2->tada, ALLEGRO_PLAYMODE_ONCE);
	(*progress)(game);

	al_set_new_bitmap_flags(flags);

	return data;
}

static void FreePulse(struct RhythmPulse* pulse) {
	if (pulse->next != NULL) {
		FreePulse(pulse->next);
	}
	free(pulse);
}

void Gamestate_Unload(struct Game* game, struct GamestateResources* data) {
	// Called when the gamestate library is being unloaded.
	// Good place for freeing all allocated memory and resources.

	al_destroy_sample_instance(data->player1->music);
	al_destroy_sample_instance(data->player2->music);
	al_destroy_sample(data->music_sample);

	al_destroy_font(data->font);
	FreePulse(data->player1->rhythmPulse);
	FreePulse(data->player2->rhythmPulse);
	free(data->player1);
	free(data->player2);
	free(data->map);
	free(data);
}

void Gamestate_Start(struct Game* game, struct GamestateResources* data) {
	// Called when this gamestate gets control. Good place for initializing state,
	// playing music etc.
	al_play_sample_instance(data->player1->music);
	al_play_sample_instance(data->player2->music);

	al_set_sample_instance_pan(data->player1->music, -1.0);
	al_set_sample_instance_pan(data->player2->music, 1.0);

	al_set_sample_instance_pan(data->player1->ding, -1.0);
	al_set_sample_instance_pan(data->player2->ding, 1.0);

	al_set_sample_instance_pan(data->player1->no, -1.0);
	al_set_sample_instance_pan(data->player2->no, 1.0);

	al_set_sample_instance_pan(data->player1->tada, -1.0);
	al_set_sample_instance_pan(data->player2->tada, 1.0);
}

void Gamestate_Stop(struct Game* game, struct GamestateResources* data) {
	// Called when gamestate gets stopped. Stop timers, music etc. here.
}

void Gamestate_Pause(struct Game* game, struct GamestateResources* data) {
	// Called when gamestate gets paused (so only Draw is being called, no Logic
	// nor ProcessEvent)
	// Pause your timers and/or sounds here.
	data->pos1 = al_get_sample_instance_position(data->player1->music);
	data->pos2 = al_get_sample_instance_position(data->player2->music);
	al_set_sample_instance_playing(data->player1->music, false);
	al_set_sample_instance_playing(data->player2->music, false);
}

void Gamestate_Resume(struct Game* game, struct GamestateResources* data) {
	// Called when gamestate gets resumed. Resume your timers and/or sounds here.
	al_set_sample_instance_playing(data->player1->music, true);
	al_set_sample_instance_playing(data->player2->music, true);
	al_set_sample_instance_position(data->player1->music, data->pos1);
	al_set_sample_instance_position(data->player2->music, data->pos2);
}

void Gamestate_Reload(struct Game* game, struct GamestateResources* data) {
	// Called when the display gets lost and not preserved bitmaps need to be
	// recreated.
	// Unless you want to support mobile platforms, you should be able to ignore
	// it.
}
