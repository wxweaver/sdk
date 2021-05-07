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
#ifndef WXFBIPC_H
#define WXFBIPC_H

#include <wx/ipc.h>
#include <memory>
#include <wx/snglinst.h>

/* Only allow one instance of a project to be loaded at a time */

class AppServer;

class wxFBIPC
{
	private:
		std::unique_ptr<wxSingleInstanceChecker> m_checker;
		std::unique_ptr<AppServer> m_server;
		const int m_port;

		bool CreateServer( const wxString& name );

	public:
		wxFBIPC()
		:
		m_port( 4242 )
		{
		}

		bool VerifySingleInstance( const wxString& file, bool switchTo = true );
		void Reset();
};

// Connection class, for use by both communicationg instances
class AppConnection: public wxConnection
{
private:
	wxString m_data;

public:
	AppConnection(){}
};

// Server class, for listening to connection requests
class AppServer: public wxServer
{
public:
	const wxString m_name;

	AppServer( const wxString& name ) : m_name( name ){}
	wxConnectionBase* OnAcceptConnection(const wxString& topic) override;
};

// Client class, to be used by subsequent instances in OnInit
class AppClient: public wxClient
{
public:
	AppClient(){}
	wxConnectionBase* OnMakeConnection() override;
};

#endif //WXFBIPC_H
