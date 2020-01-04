/*
    SDL_inputmethod
    Copyright (C) 2004  Kazunori Itoyanagi

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    ITOYANAGI Kazunori
    itkz@users.sourceforge.jp
*/

#ifndef _SDL_ime_H_
#define _SDL_ime_H_


#include <stdio.h>

#include "SDL_version.h"
#include "SDL.h"

#include "begin_code.h"



#define INPUT_METHOD_MAJOR_VERSION	0
#define INPUT_METHOD_MINOR_VERSION	1
#define INPUT_METHOD_PATCHLEVEL		0

/* This macro can be used to fill a version structure with the compile-time
 * version of the SDL_inputmethod library.
 */
#define INPUTMETHOD_VERSION(X)							\
{									\
	(X)->major = INPUT_METHOD_MAJOR_VERSION;					\
	(X)->minor = INPUT_METHOD_MINOR_VERSION;					\
	(X)->patch = INPUT_METHOD_PATCHLEVEL;					\
}


/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif





/* public ... for Applications */

typedef enum
{
	INPUT_METHOD_MESSAGE_ON,
	INPUT_METHOD_MESSAGE_CHANGE,
	INPUT_METHOD_MESSAGE_RESULT,
	INPUT_METHOD_MESSAGE_OFF,
	INPUT_METHOD_MESSAGE_CHAR,
	INPUT_METHOD_MESSAGE_NO_EXIST
} InputMethod_Message;

typedef enum
{
	INPUT_METHOD_SUCCESS = 0,
	INPUT_METHOD_ERROR_ALREADY_INIT,
	INPUT_METHOD_ERROR_ALLOCATED_MEMORY,
	INPUT_METHOD_ERROR_NO_STRING,
	INPUT_METHOD_ERROR_UNKNOWN_MESSAGE,
	INPUT_METHOD_ERROR_SDL_NO_INIT,
	INPUT_METHOD_ERROR_NO_INIT,
	INPUT_METHOD_ERROR_SYSTEM_SPECIFIC,
	INPUT_METHOD_ERROR_ALREADY_VALIDATED,
	INPUT_METHOD_ERROR_ALREADY_INVALIDATED,
	INPUT_METHOD_ERROR_NOT_AVAILABLE,
	INPUT_METHOD_ERROR_INVALID_BOOTSTRAP
} InputMethod_Result;

/*
typedef enum
{
	INPUT_METHOD_STATUS_ON,
	INPUT_METHOD_STATUS_OFF
} InputMethod_Status;
*/

extern DECLSPEC InputMethod_Result SDLCALL InputMethod_Init(void);

extern DECLSPEC int SDLCALL InputMethod_GetEventNumber(void);
extern DECLSPEC void SDLCALL InputMethod_MoveNextEvent(void);
extern DECLSPEC InputMethod_Message SDLCALL InputMethod_GetCurrentMessage(void);
extern DECLSPEC Uint16 * SDLCALL InputMethod_GetCurrentEditingString(void);
extern DECLSPEC Uint16 SDLCALL InputMethod_GetCurrentChar(void);
extern DECLSPEC int SDLCALL InputMethod_GetCurrentCursorPosition(void);
extern DECLSPEC int SDLCALL InputMethod_GetCurrentCompositionPosition(void);
extern DECLSPEC int SDLCALL InputMethod_GetCurrentCompositionLength(void);
extern DECLSPEC void SDLCALL InputMethod_Reset(void);
extern DECLSPEC InputMethod_Result SDLCALL InputMethod_Validate(void);
extern DECLSPEC InputMethod_Result SDLCALL InputMethod_Invalidate(void);
extern DECLSPEC Uint16 * SDLCALL InputMethod_GetInputMethodName(void);
extern DECLSPEC void SDLCALL InputMethod_Quit(void);





/* protected? ... for add other Input Methods */

#define INPUT_METHOD_NAME_STRING_LENGTH 256

typedef struct _SDL_InputMethod
{
	SDL_bool (*available)(void);
	InputMethod_Result (*init)(void);
	void (*quit)(void);
	void (*reset)(void);
	InputMethod_Result (*validate)(void);
	InputMethod_Result (*invalidate)(void);
	
	/*
	  Return value is Input Method name in Unicode.
	  You have to set string to `InputMethodName' and
	  return this in get_name(),
	  because get_name() is a possible
	  to call without init() and quit(),
	  and so even if use malloc() to string, no time to free().
	*/
	Uint16 *(*get_name)(void);
	Uint16 InputMethodName[INPUT_METHOD_NAME_STRING_LENGTH];
/*
	InputMethod_Status (*get_status)(void);
	void (*set_status)(InputMethod_Status status);
*/
} SDL_InputMethod;

extern DECLSPEC InputMethod_Result SDLCALL InputMethod_PostEvent(
	InputMethod_Message message,
	Uint16 *editingString,
	int cursorPosition,
	int compositionPosition,
	int compositionLength);
extern DECLSPEC InputMethod_Result SDLCALL InputMethod_InitFromOther(
	SDL_InputMethod inputMethod);





/* private */

#ifdef ENABLE_WIN32
extern SDL_InputMethod InputMethod_win32;
#endif
#ifdef ENABLE_XIM
extern SDL_InputMethod InputMethod_xim;
#endif





/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#include "close_code.h"



#endif
