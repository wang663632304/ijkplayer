/*****************************************************************************
 * ijksdl_aout_android.c
 *****************************************************************************
 *
 * copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "ijksdl_aout_android.h"

#include "ijksdl_thread.h"
#include "ijksdl_aout_internal.h"

typedef struct SDL_Aout_Opaque {
    JavaVM *jvm;
    SDL_cond *wakeup;

    int abort_request;
    SDL_Thread *audio_thread;
    SDL_Thread _audio_tid;
} SDL_Aout_Opaque;

int aout_thread(void *arg)
{
    SDL_Aout *aout = arg;
    SDL_Aout_Opaque *opaque = aout->opaque;

    return 0;
}

void aout_free_l(SDL_Aout *aout)
{
    if (!aout)
        return;

    SDL_Aout_Opaque *opaque = aout->opaque;
    if (opaque) {
        SDL_DestroyCond(opaque->wakeup);
    }

    SDL_Aout_FreeInternal(aout);
}

int aout_open_audio(SDL_Aout *aout, SDL_AudioSpec *desired, SDL_AudioSpec *obtained)
{
    return -1;
}

void aout_pause_audio(SDL_Aout *aout, int pause_on)
{

}

void aout_close_audio(SDL_Aout *aout)
{

}

void SDL_Init_AoutAndroid(JNIEnv *env)
{

}

SDL_Aout *SDL_AoutAndroid_CreateForAudioTrack(JavaVM* jvm)
{
    SDL_Aout *aout = SDL_Aout_CreateInternal(sizeof(SDL_Aout_Opaque));
    if (!aout)
        return NULL;

    SDL_Aout_Opaque *opaque = aout->opaque;
    opaque->jvm = jvm;
    opaque->wakeup = SDL_CreateCond();

    aout->free_l = aout_free_l;
    aout->open_audio = aout_open_audio;
    aout->pause_audio = aout_pause_audio;
    aout->close_audio = aout_close_audio;

    return aout;
}