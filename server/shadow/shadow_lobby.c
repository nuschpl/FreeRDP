/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 *
 * Copyright 2014 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rdtk/rdtk.h>

#include "shadow.h"

#include "shadow_lobby.h"

int shadow_client_init_lobby(rdpShadowClient* client)
{
	int width;
	int height;
	rdtkEngine* engine;
	rdtkSurface* surface;
	RECTANGLE_16 invalidRect;
	rdpShadowSurface* lobby;
	rdpContext* context = (rdpContext*) client;
	rdpSettings* settings = context->settings;

	width = settings->DesktopWidth;
	height = settings->DesktopHeight;

	lobby = client->lobby = shadow_surface_new(client->server, 0, 0, width, height);

	if (!client->lobby)
		return -1;

	engine = rdtk_engine_new();

	surface = rdtk_surface_new(engine, lobby->data, lobby->width, lobby->height, lobby->scanline);

	rdtk_surface_fill(surface, 0, 0, width, height, 0x3BB9FF);
	//rdtk_label_draw(surface, 16, 16, 128, 32, NULL, "label", 0, 0);
	//rdtk_button_draw(surface, 16, 64, 128, 32, NULL, "button");
	//rdtk_text_field_draw(surface, 16, 128, 128, 32, NULL, "text field");

	rdtk_surface_free(surface);

	rdtk_engine_free(engine);

	invalidRect.left = 0;
	invalidRect.top = 0;
	invalidRect.right = width;
	invalidRect.bottom = height;

	region16_union_rect(&(lobby->invalidRegion), &(lobby->invalidRegion), &invalidRect);

	return 1;
}