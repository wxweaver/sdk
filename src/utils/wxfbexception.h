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
#ifndef WXFBEXCEPTION
#define WXFBEXCEPTION

#include <wx/string.h>

/**
Exception class for wxFormBuilder
*/
class wxFBException
{
public:
	explicit wxFBException( const wxString& what )
	:
	m_what(what)
	{}

	virtual ~wxFBException() = default;

	virtual const wxChar* what() const throw()
	{
		return m_what.c_str();
	}

private:
   wxString m_what;
};

/**
This allows you to stream your exceptions in.
It will take care of the conversion	and throwing the exception.
*/
#define THROW_WXFBEX( message )																								\
	{																														\
	wxString hopefullyThisNameWontConflictWithOtherVariables;																\
	wxString hopefullyUniqueFile(__FILE__, wxConvUTF8);																		\
	hopefullyUniqueFile = hopefullyUniqueFile.substr(hopefullyUniqueFile.find_last_of(wxT("\\/")) + 1);						\
	hopefullyThisNameWontConflictWithOtherVariables << message << wxT(" <") << hopefullyUniqueFile << wxT("@");				\
	hopefullyThisNameWontConflictWithOtherVariables << wxString::Format( wxT("%i"), __LINE__ ) << wxT(">");					\
	throw wxFBException( hopefullyThisNameWontConflictWithOtherVariables );													\
	}

#endif //WXFBEXCEPTION
