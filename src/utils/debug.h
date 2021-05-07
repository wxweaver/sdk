/*
    wxWeaver - A GUI Designer Editor for wxWidgets.
    Copyright (C) 2005 José Antonio Hurtado (as wxFormBuilder)
    Copyright (C) 2021 Andrea Zanellato <redtid3@gmail.com>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __WXFB_DEBUG__
#include <wx/string.h>
#include <wx/log.h>

#define LogDebug(...) \
	{											\
		wxString LOG_MSG;						\
		LOG_MSG << wxT(__FILE__);				\
		LOG_MSG = LOG_MSG.AfterLast('/');		\
		LOG_MSG << wxT("@");					\
		LOG_MSG << __LINE__;					\
		LOG_MSG << wxT(" ");					\
		LOG_MSG << __FUNCTION__;				\
		LOG_MSG << wxT(": ");					\
		wxString s;								\
		s.Printf(__VA_ARGS__);					\
		LOG_MSG << s;							\
		wxLogDebug(LOG_MSG);					\
	}

#else

#define LogDebug(...)

#endif

#endif //__DEBUG_H__
