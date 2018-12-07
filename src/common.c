/*! \file common.c
 *  \brief Common stuff that can be used by all gamestates.
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

#include "common.h"
#include <libsuperderpy.h>

void Speak(struct Game* game, char* text) {
	if (!game->config.voice) {
		return;
	}
#ifndef ALLEGRO_UNIX
	return;
#else
	char* buffer = malloc(255 * sizeof(char));
	snprintf(buffer, 255, "espeak \"%s\"&", text);
	system(buffer);
	free(buffer);
#endif
}

bool GlobalEventHandler(struct Game* game, ALLEGRO_EVENT* ev) {
	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_M)) {
		game->config.mute = !game->config.mute;
		al_set_mixer_gain(game->audio.mixer, game->config.mute ? 0.0 : 1.0);
		SetConfigOption(game, "SuperDerpy", "mute", game->config.mute ? "1" : "0");
		PrintConsole(game, "Mute: %d", game->config.mute);
	}

	if ((ev->type == ALLEGRO_EVENT_KEY_DOWN) && (ev->keyboard.keycode == ALLEGRO_KEY_F)) {
		game->config.fullscreen = !game->config.fullscreen;
		if (game->config.fullscreen) {
			SetConfigOption(game, "SuperDerpy", "fullscreen", "1");
			al_hide_mouse_cursor(game->display);
		} else {
			SetConfigOption(game, "SuperDerpy", "fullscreen", "0");
			al_show_mouse_cursor(game->display);
		}
#ifdef ALLEGRO_ANDROID
		al_set_display_flag(game->display, ALLEGRO_FRAMELESS, game->config.fullscreen);
#endif
		al_set_display_flag(game->display, ALLEGRO_FULLSCREEN_WINDOW, game->config.fullscreen);
		SetupViewport(game, game->viewport_config);
		PrintConsole(game, "Fullscreen toggled");
	}
	if (ev->type == ALLEGRO_EVENT_TOUCH_BEGIN) {
		game->data->touch = true;
	}
#ifndef ALLEGRO_ANDROID
	if (ev->type == ALLEGRO_EVENT_KEY_DOWN) {
		game->data->touch = false;
	}
#endif

	return false;
}

struct CommonResources* CreateGameData(struct Game* game) {
	struct CommonResources* data = calloc(1, sizeof(struct CommonResources));

	int samplerate = strtol(GetConfigOptionDefault(game, "SuperDerpy", "samplerate", "44100"), NULL, 10);
	ALLEGRO_AUDIO_DEPTH depth = ALLEGRO_AUDIO_DEPTH_FLOAT32;
#ifdef ALLEGRO_ANDROID
	depth = ALLEGRO_AUDIO_DEPTH_INT16;
#endif
	data->audio.v = al_create_voice(samplerate, depth, ALLEGRO_CHANNEL_CONF_2);
	if (!data->audio.v) {
		// fallback
		depth = (depth == ALLEGRO_AUDIO_DEPTH_FLOAT32) ? ALLEGRO_AUDIO_DEPTH_INT16 : ALLEGRO_AUDIO_DEPTH_FLOAT32;
		data->audio.v = al_create_voice(samplerate, depth, ALLEGRO_CHANNEL_CONF_2);
	}
	ALLEGRO_VOICE* voice = data->audio.v ? data->audio.v : game->audio.v;
	data->audio.mixer = al_create_mixer(samplerate, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	data->audio.fx = al_create_mixer(samplerate, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	data->audio.music = al_create_mixer(samplerate, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	data->audio.voice = al_create_mixer(samplerate, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	al_attach_mixer_to_voice(data->audio.mixer, voice);
	al_attach_mixer_to_mixer(data->audio.fx, data->audio.mixer);
	al_attach_mixer_to_mixer(data->audio.music, data->audio.mixer);
	al_attach_mixer_to_mixer(data->audio.voice, data->audio.mixer);
	al_set_mixer_gain(data->audio.fx, game->config.fx / 10.0);
	al_set_mixer_gain(data->audio.music, game->config.music / 10.0);
	al_set_mixer_gain(data->audio.voice, game->config.voice / 10.0);
	al_set_mixer_gain(data->audio.mixer, game->config.mute ? 0.0 : 1.0);

	data->button_sample = al_load_sample(GetDataFilePath(game, "button.flac"));
	data->button = al_create_sample_instance(data->button_sample);
	al_attach_sample_instance_to_mixer(data->button, game->audio.fx);

	data->pan = strtol(GetConfigOptionDefault(game, "ZjedzTrawke2", "pan", "1"), NULL, 10);

	return data;
}

void DestroyGameData(struct Game* game) {
	al_destroy_sample_instance(game->data->button);
	al_destroy_sample(game->data->button_sample);
	al_destroy_mixer(game->data->audio.fx);
	al_destroy_mixer(game->data->audio.music);
	al_destroy_mixer(game->data->audio.voice);
	al_destroy_mixer(game->data->audio.mixer);
	al_destroy_voice(game->data->audio.v);
	free(game->data);
}
