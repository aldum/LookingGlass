/*
Looking Glass - KVM FrameRelay (KVMFR) Client
Copyright (C) 2017-2019 Geoffrey McRae <geoff@hostfission.com>
https://looking-glass.hostfission.com

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#pragma once
#include <stdint.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "app.h"
#include "KVMFR.h"

#define IS_LG_RENDERER_VALID(x) \
  ((x)->get_name       && \
   (x)->create         && \
   (x)->initialize     && \
   (x)->deinitialize   && \
   (x)->on_resize      && \
   (x)->on_mouse_shape && \
   (x)->on_mouse_event && \
   (x)->on_alert       && \
   (x)->render_startup && \
   (x)->render         && \
   (x)->update_fps)

#define LGR_OPTION_COUNT(x) (sizeof(x) / sizeof(LG_RendererOpt))

typedef bool(* LG_RendererOptValidator)(const char * value);
typedef void(* LG_RendererOptHandler  )(void * opaque, const char * value);

typedef struct LG_RendererOpt
{
  const char              * name;
  const char              * desc;
  LG_RendererOptValidator   validator;
  LG_RendererOptHandler     handler;
}
LG_RendererOpt;

typedef struct LG_RendererOptValue
{
  const LG_RendererOpt * opt;
  char                 * value;
} LG_RendererOptValue;

typedef LG_RendererOpt * LG_RendererOptions;

typedef struct LG_RendererParams
{
//  TTF_Font * font;
//  TTF_Font * alertFont;
  bool       showFPS;
}
LG_RendererParams;

typedef struct LG_RendererFormat
{
  FrameType    type;    // frame type
  unsigned int width;   // image width
  unsigned int height;  // image height
  unsigned int stride;  // scanline width (zero if compresed)
  unsigned int pitch;   // scanline bytes (or compressed size)
  unsigned int bpp;     // bits per pixel (zero if compressed)
}
LG_RendererFormat;

typedef struct LG_RendererRect
{
  bool         valid;
  int          x;
  int          y;
  unsigned int w;
  unsigned int h;
}
LG_RendererRect;

typedef enum LG_RendererCursor
{
  LG_CURSOR_COLOR       ,
  LG_CURSOR_MONOCHROME  ,
  LG_CURSOR_MASKED_COLOR
}
LG_RendererCursor;

typedef const char * (* LG_RendererGetName     )();
typedef bool         (* LG_RendererCreate      )(void ** opaque, const LG_RendererParams params);
typedef bool         (* LG_RendererInitialize  )(void * opaque, Uint32 * sdlFlags);
typedef void         (* LG_RendererDeInitialize)(void * opaque);
typedef void         (* LG_RendererOnResize    )(void * opaque, const int width, const int height, const LG_RendererRect destRect);
typedef bool         (* LG_RendererOnMouseShape)(void * opaque, const LG_RendererCursor cursor, const int width, const int height, const int pitch, const uint8_t * data);
typedef bool         (* LG_RendererOnMouseEvent)(void * opaque, const bool visible , const int x, const int y);
typedef bool         (* LG_RendererOnFrameEvent)(void * opaque, const LG_RendererFormat format, const uint8_t * data);
typedef void         (* LG_RendererOnAlert     )(void * opaque, const LG_MsgAlert alert, const char * message, bool ** closeFlag);
typedef bool         (* LG_RendererRender      )(void * opaque, SDL_Window *window);
typedef void         (* LG_RendererUpdateFPS   )(void * opaque, const float avgUPS, const float avgFPS);

typedef struct LG_Renderer
{
  LG_RendererCreate       create;
  LG_RendererGetName      get_name;
  LG_RendererOptions      options;
  unsigned int            option_count;
  LG_RendererInitialize   initialize;
  LG_RendererDeInitialize deinitialize;
  LG_RendererOnResize     on_resize;
  LG_RendererOnMouseShape on_mouse_shape;
  LG_RendererOnMouseEvent on_mouse_event;
  LG_RendererOnFrameEvent on_frame_event;
  LG_RendererOnAlert      on_alert;
  LG_RendererRender       render_startup;
  LG_RendererRender       render;
  LG_RendererUpdateFPS    update_fps;
}
LG_Renderer;

// generic option helpers
bool LG_RendererValidatorBool(const char * value);
bool LG_RendererValueToBool  (const char * value);