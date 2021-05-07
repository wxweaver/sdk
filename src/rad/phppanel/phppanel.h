#ifndef HEADER_E9827DF45C5479A
#define HEADER_E9827DF45C5479A

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

/**
@file
@author Jefferson González - jgmdev@gmail.com
@note
*/

#ifndef __PHP_PANEL__
#define __PHP_PANEL__

#include "../../utils/wxfbdefs.h"

#include <wx/panel.h>

class CodeEditor;

class wxStyledTextCtrl;

class wxFindDialogEvent;

class wxWeaverEvent;
class wxWeaverPropertyEvent;
class wxWeaverObjectEvent;
class wxWeaverEventHandlerEvent;

class PHPPanel : public wxPanel
{
private:
	CodeEditor* m_phpPanel;
	PTCCodeWriter m_phpCW;

    void InitStyledTextCtrl( wxStyledTextCtrl* stc );

public:
	PHPPanel( wxWindow *parent, int id );
	~PHPPanel() override;

	void OnPropertyModified( wxWeaverPropertyEvent& event );
	void OnProjectRefresh( wxWeaverEvent& event );
	void OnCodeGeneration( wxWeaverEvent& event );
	void OnObjectChange( wxWeaverObjectEvent& event );
	void OnEventHandlerModified( wxWeaverEventHandlerEvent& event );

	void OnFind( wxFindDialogEvent& event );

	DECLARE_EVENT_TABLE()
};

#endif //__PHP_PANEL__

#endif // header guard
