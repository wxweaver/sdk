/*
    wxWeaver - A GUI Designer Editor for wxWidgets.
    Copyright (C) 2005 José Antonio Hurtado
    Copyright (C) 2005 Juan Antonio Ortega (as wxFormBuilder)
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
#pragma once

#include "utils/defs.h"
#include <wx/stc/stc.h>
#include <wx/panel.h>

class CodeEditor;
class wxWeaverEvent;
class wxWeaverObjectEvent;
class wxWeaverPropertyEvent;
class wxFindDialogEvent;

class XrcPanel : public wxPanel {
public:
    XrcPanel(wxWindow* parent, int id);
    ~XrcPanel() override;

    void OnPropertyModified(wxWeaverPropertyEvent& event);
    void OnProjectRefresh(wxWeaverEvent& event);
    void OnCodeGeneration(wxWeaverEvent& event);
    void OnObjectChange(wxWeaverObjectEvent& event);
    void OnFind(wxFindDialogEvent& event);

private:
    void InitStyledTextCtrl(wxStyledTextCtrl* stc);

    CodeEditor* m_xrcPanel;
    PTCCodeWriter m_codeWriter;
};
