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

#define SPEED 1.4
#define MAZE_WIDGTH 32
#define MAZE_HIGHT 32

enum direction { up,
	down,
	left,
	right };

struct RythmPulse {
	float timer;
	int status;
	struct RythmPulse* next;
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
};

struct Player {
	int x, y;
	char* text;
	float anlge;
	ALLEGRO_BITMAP* player;
	int score;
	struct RythmPulse* rythmPulse;
};

float Abs(float a) {
	if (a >= 0) {
		return a;
	}
	return -a;
}
void IsGoodPressed(struct RythmPulse* pulse, struct Player* player,
	struct GamestateResources* data, enum direction direction) {
	float point = pulse->timer;
	if (point <= 0.25f && point > -0.25f) {
		if (Abs(point) <= 0.25f && pulse->status == -1) {
			pulse->status = 100 - Abs((point)*400);
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
						if (data->map[player->x + (player->y - 1) * MAZE_WIDGTH]!=1) {
							player->y--;
							player->anlge =1.5*3.1415;
						}
					}
					break;
				case down:
					if (player->y <= MAZE_HIGHT ) {
						if (data->map[player->x + (player->y + 1) * MAZE_WIDGTH]!=1) {
							player->y++;
							player->anlge =0.5*3.1415;
						}
					}
					break;
				case left:
					if (player->x > 0) {
						if (data->map[player->x - 1 + player->y * MAZE_WIDGTH]!=1) {
							player->x--;
							player->anlge =3.1415;
						}
					}
					break;
				case right:
					if (player->x <= MAZE_WIDGTH ) {
						if (data->map[player->x + 1 + player->y * MAZE_WIDGTH]!=1) {
							player->x++;
							player->anlge =0;
						}
					}
					break;
			}
			if(player->x==data->xGrass && player ->y == data->yGrass)
			{

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
		IsGoodPressed(pulse->next, player, data, direction);
	}
}

void DrawMap(struct Player* player,
			 struct GamestateResources* data, float x, float y)
{
	int i,j;

	for(i=-3;i<3;i++)
	{
		if(i+player->x<0 || i+player->x>= MAZE_WIDGTH ) continue;
		for(j=-3;j<3;j++)
		{
			if(j+player->y<0 || j+player->y>= MAZE_HIGHT ) continue;
			if(!data->map[i+player->x + (j+player->y)*MAZE_WIDGTH])
				al_draw_bitmap_region(data->tile, 0, 0, 16, 16,
									  x+ i*16,
									  y+ j*16, 0);
			if(j+player->y == data->yGrass && i+player->x == data->xGrass)
				al_draw_bitmap_region(data->grass, 0, 0, 16, 16,
									  x+ i*16,
									  y+ j*16, 0);


		}
	}
}

int Gamestate_ProgressCount =
	1; // number of loading steps as reported by Gamestate_Load

void DeleteDeltaTimeFromPulse(struct RythmPulse* pulse, float deltaTime,
	struct Player* data) {
	float progress = (data->score) / 2000.0f;
	float delatTime = (deltaTime * SPEED) * ((progress + 1));
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
void MoveEnd(struct RythmPulse* pulse, struct RythmPulse* onEnd, float offset) {
	if (pulse->next == NULL) {
		pulse->next = onEnd;
		onEnd->next = 0;
		onEnd->status = -1;
		onEnd->timer = pulse->timer + offset;
	} else {
		MoveEnd(pulse->next, onEnd, offset);
	}
}

void Gamestate_Logic(struct Game* game, struct GamestateResources* data,
	double delta) {
	DeleteDeltaTimeFromPulse(data->player2->rythmPulse, delta, data->player2);
	DeleteDeltaTimeFromPulse(data->player1->rythmPulse, delta, data->player1);
	if (data->player1->rythmPulse->timer < -5.0f) {
		struct RythmPulse* pulse = data->player1->rythmPulse;
		data->player1->rythmPulse = data->player1->rythmPulse->next;
		MoveEnd(data->player1->rythmPulse, pulse, 1);
	}
	if (data->player2->rythmPulse->timer < -5.0f) {
		struct RythmPulse* pulse = data->player2->rythmPulse;
		data->player2->rythmPulse = data->player2->rythmPulse->next;
		MoveEnd(data->player2->rythmPulse, pulse, 1);
	}
}

void Gamestate_Tick(struct Game* game, struct GamestateResources* data) {
	// Called 60 times per second (by default). Here you should do all your game
	// logic.
}

void DrawAllPulse(struct RythmPulse* pulse, struct Game* game,
	struct GamestateResources* data, float x) {
	al_draw_bitmap_region(data->pulseBitmap, 0, 0, 20, 20, x,
		game->viewport.height / 2.0 - 10 + pulse->timer * 40,
		0);

	if (pulse->next) {
		DrawAllPulse(pulse->next, game, data, x);
	}
}

void Gamestate_Draw(struct Game* game, struct GamestateResources* data) {
	// Called as soon as possible, but no sooner than next Gamestate_Logic call.
	// Draw everything to the screen here.

	DrawMap(data->player1,data,80,60);
	DrawMap(data->player2,data,250,60);
	DrawAllPulse(data->player1->rythmPulse, game, data,
		game->viewport.width / 2.0 - 25);
	DrawAllPulse(data->player2->rythmPulse, game, data,
		game->viewport.width / 2.0 + 5);
	al_draw_bitmap_region(data->pointer, 0, 0, 20, 20,
		game->viewport.width / 2.0 - 25,
		game->viewport.height / 2.0f - 10, 0);
	al_draw_bitmap_region(data->pointer, 0, 0, 20, 20,
		game->viewport.width / 2.0 + 5,
		game->viewport.height / 2.0f - 10, 0);

	al_draw_text(data->font, al_map_rgb(255, 255, 255), game->viewport.width / 4,
		game->viewport.height / 1.3f, ALLEGRO_ALIGN_CENTRE,
		data->player1->text);
	al_draw_text(data->font, al_map_rgb(255, 255, 255),
		game->viewport.width * 3 / 4, game->viewport.height / 1.3f,
		ALLEGRO_ALIGN_CENTRE, data->player2->text);


	al_draw_rotated_bitmap(data->player1->player, 8, 8,
						  88,
						  68, data->player1->anlge,0);
	al_draw_rotated_bitmap(data->player2->player, 8, 8,
						   258,
						   68, data->player2->anlge,0);
}

void Gamestate_ProcessEvent(struct Game* game, struct GamestateResources* data,
	ALLEGRO_EVENT* ev) {
	// Called for each event in Allegro event queue.
	// Here you can handle user input, expiring timers etc.
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE)) {
		UnloadCurrentGamestate(
			game); // mark this gamestate to be stopped and unloaded
		// When there are no active gamestates, the engine will quit.
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		ev->keyboard.keycode == ALLEGRO_KEY_A) {
		IsGoodPressed(data->player1->rythmPulse, data->player1, data, left);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_S)) {
		IsGoodPressed(data->player1->rythmPulse, data->player1, data, down);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_W)) {
		IsGoodPressed(data->player1->rythmPulse, data->player1, data, up);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_D)) {
		IsGoodPressed(data->player1->rythmPulse, data->player1, data, right);
	}

	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		ev->keyboard.keycode == ALLEGRO_KEY_LEFT) {
		IsGoodPressed(data->player2->rythmPulse, data->player2, data, left);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_DOWN)) {
		IsGoodPressed(data->player2->rythmPulse, data->player2, data, down);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_UP)) {
		IsGoodPressed(data->player2->rythmPulse, data->player2, data, up);
	}
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) &&
		(ev->keyboard.keycode == ALLEGRO_KEY_RIGHT)) {
		IsGoodPressed(data->player2->rythmPulse, data->player2, data, right);
	}
}

void CarveMaze(char* maze, int width, int height, int x, int y) {
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
void GenerateMaze(char* maze, int width, int height) {
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
void ShowMaze(const char* maze, int width, int height) {
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

	struct GamestateResources* data =
		calloc(1, sizeof(struct GamestateResources));
	al_set_new_bitmap_flags(
		al_get_new_bitmap_flags() ^
		ALLEGRO_MAG_LINEAR); // disable linear scaling for pixelarty appearance
	data->font = al_create_builtin_font();
	data->pulseBitmap =
		al_load_bitmap(GetDataFilePath(game, "Sprites/rythmPulse.png"));
	data->pointer = al_load_bitmap(GetDataFilePath(game, "Sprites/line.png"));
	data->tile = al_load_bitmap(GetDataFilePath(game, "Sprites/tile.png"));
	data->grass = al_load_bitmap(GetDataFilePath(game, "Sprites/grass.png"));
	progress(game); // report that we progressed with the loading, so the engine
	// can move a progress bar
	data->player1 = malloc(sizeof(struct Player));
	data->player2 = malloc(sizeof(struct Player));
	data->player1->text = "";
	data->player1->rythmPulse = malloc(sizeof(struct RythmPulse));
	data->player1->rythmPulse->timer = 0;
	data->player1->score = 0;

	data->player1->player = al_load_bitmap(GetDataFilePath(game, "Sprites/swinka_kolor.png"));
	data->player2->player = al_load_bitmap(GetDataFilePath(game, "Sprites/swinka_czb.png"));
	data->player2->text = "";
	data->player2->rythmPulse = malloc(sizeof(struct RythmPulse));
	data->player2->rythmPulse->timer = 0;
	data->player2->score = 0;
	data->map = malloc(MAZE_WIDGTH * MAZE_HIGHT * sizeof(char));
	GenerateMaze(data->map, MAZE_WIDGTH, MAZE_HIGHT);
	ShowMaze(data->map, MAZE_WIDGTH, MAZE_HIGHT);
	struct RythmPulse* pulse = data->player1->rythmPulse;
	pulse->status = -1;
	pulse->timer = 0;
	int i;
	for (i = 0; i < 10; i++) {
		pulse->next = malloc(sizeof(struct RythmPulse));
		pulse = pulse->next;
		pulse->timer = (float)i - 1;
		pulse->status = -1;
	}
	pulse->next = NULL;

	struct RythmPulse* pulse2 = data->player2->rythmPulse;
	pulse2->status = -1;
	pulse2->timer = 0;
	for (i = 0; i < 10; i++) {
		pulse2->next = malloc(sizeof(struct RythmPulse));
		pulse2 = pulse2->next;
		pulse2->timer = (float)i - 1;
		pulse2->status = -1;
	}
	pulse2->next = NULL;
	data->player1->x =1;
	data->player1->y =0;
	data->player2->x =1;
	data->player2->y =0;
	int j;
	char flag=0;
	for(i=MAZE_WIDGTH-1;i>=0;i--) {
		for (j = MAZE_HIGHT - 1; j >= 0; j--)
			if (data->map[i + (j) * MAZE_WIDGTH] != 1) {
				data->xGrass = i;
				data->yGrass = j;
				flag=1;
				break;
			}
		if(flag)
			break;
	}

	return data;
}

void FreePulse(struct RythmPulse* pulse) {
	if (pulse->next != NULL) {
		FreePulse(pulse->next);
	}
	free(pulse);
}

void Gamestate_Unload(struct Game* game, struct GamestateResources* data) {
	// Called when the gamestate library is being unloaded.
	// Good place for freeing all allocated memory and resources.

	al_destroy_font(data->font);
	FreePulse(data->player1->rythmPulse);
	FreePulse(data->player2->rythmPulse);
	free(data->player1);
	free(data->player2);
	free(data->map);
	free(data);
}

void Gamestate_Start(struct Game* game, struct GamestateResources* data) {
	// Called when this gamestate gets control. Good place for initializing state,
	// playing music etc.
}

void Gamestate_Stop(struct Game* game, struct GamestateResources* data) {
	// Called when gamestate gets stopped. Stop timers, music etc. here.
}

void Gamestate_Pause(struct Game* game, struct GamestateResources* data) {
	// Called when gamestate gets paused (so only Draw is being called, no Logic
	// nor ProcessEvent)
	// Pause your timers and/or sounds here.
}

void Gamestate_Resume(struct Game* game, struct GamestateResources* data) {
	// Called when gamestate gets resumed. Resume your timers and/or sounds here.
}

void Gamestate_Reload(struct Game* game, struct GamestateResources* data) {
	// Called when the display gets lost and not preserved bitmaps need to be
	// recreated.
	// Unless you want to support mobile platforms, you should be able to ignore
	// it.
}