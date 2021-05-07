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

#ifndef _XRC_CODE_GEN_
#define _XRC_CODE_GEN_

#include "codegen.h"

namespace ticpp
{
	class Element;
}

/// XRC code generator.

class XrcCodeGenerator : public CodeGenerator
{
private:
	PCodeWriter m_cw;
	std::vector<ticpp::Element*> m_contextMenus;

	ticpp::Element* GetElement( PObjectBase obj, ticpp::Element* parent = NULL );

public:
	/// Configures the code writer for the XML file.
	void SetWriter( PCodeWriter cw );

	/// Generates the XRC code for the project.
	bool GenerateCode(PObjectBase project) override;
};


#endif //_XRC_CODE_GEN_
