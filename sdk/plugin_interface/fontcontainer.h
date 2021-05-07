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
#ifndef __WXFONTCONTAINER__
#define __WXFONTCONTAINER__

#include <wx/font.h>

/** @class wxFontContainer
    @brief Because the class wxFont cannot be a container for invalid font data (like default values).
*/
class wxFontContainer : public wxObject
{
public:
    int m_pointSize;		///< Point Size
	wxFontFamily m_family;  ///< Family
	wxFontStyle m_style;    ///< Style
	wxFontWeight m_weight;  ///< Weight
    bool m_underlined;		///< Underlined
    wxString m_faceName;	///< Face Name

    inline void InitDefaults()
    {
		m_pointSize = -1;
		m_family = wxFONTFAMILY_DEFAULT;
		m_style = wxFONTSTYLE_NORMAL;
		m_weight = wxFONTWEIGHT_NORMAL;
		m_underlined = false;
		m_faceName = wxEmptyString;
    }

    wxFontContainer()
    {
    	InitDefaults();
	}

    inline wxFontContainer( const wxFont& font )
    {
        if ( !font.IsOk() )
        {
        	InitDefaults();
        }
        else
        {
        	m_pointSize = font.GetPointSize();
        	m_family = font.GetFamily();
        	m_style = font.GetStyle();
        	m_weight = font.GetWeight();
        	m_underlined = font.GetUnderlined();
        	m_faceName = font.GetFaceName();
        }
    }

	inline wxFontContainer(int pointSize, wxFontFamily family = wxFONTFAMILY_DEFAULT,
	                       wxFontStyle style = wxFONTSTYLE_NORMAL,
	                       wxFontWeight weight = wxFONTWEIGHT_NORMAL, bool underlined = false,
	                       const wxString& faceName = wxEmptyString)
	: m_pointSize(pointSize), m_family(family), m_style(style), m_weight(weight),
	  m_underlined(underlined), m_faceName(faceName) {
	}

	wxFont GetFont() const
	{
		int pointSize = m_pointSize <= 0 ? wxNORMAL_FONT->GetPointSize() : m_pointSize;
		return wxFont( pointSize, m_family, m_style, m_weight, m_underlined, m_faceName );
	}

	// Duplicate wxFont's interface for backward compatiblity
	#define MAKE_GET_AND_SET( NAME, TYPE, VARIABLE ) 	\
		TYPE Get##NAME() const { return VARIABLE; }		\
		void Set##NAME( TYPE value ){ VARIABLE = value; }

	MAKE_GET_AND_SET( PointSize, int, m_pointSize )
	MAKE_GET_AND_SET(Family, wxFontFamily, m_family)
	MAKE_GET_AND_SET(Style, wxFontStyle, m_style)
	MAKE_GET_AND_SET(Weight, wxFontWeight, m_weight)
	MAKE_GET_AND_SET( Underlined, bool, m_underlined )
	MAKE_GET_AND_SET( FaceName, wxString, m_faceName )

	// Allow implicit cast to wxFont
	operator wxFont() const
	{
		return GetFont();
	}
};

#endif //__WXFONTCONTAINER__
