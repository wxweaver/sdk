--*****************************************************************************
--*	Author:		RJP Computing <rjpcomputing@gmail.com>
--*	Date:		12/15/2006
--*	Version:	1.00-beta
--* Copyright (C) 2006 RJP Computing
--*
--* This program is free software; you can redistribute it and/or
--* modify it under the terms of the GNU General Public License
--* as published by the Free Software Foundation; either version 2
--* of the License, or (at your option) any later version.
--*
--* This program is distributed in the hope that it will be useful,
--* but WITHOUT ANY WARRANTY; without even the implied warranty of
--* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--* GNU General Public License for more details.
--*
--* You should have received a copy of the GNU General Public License
--* along with this program; if not, write to the Free Software
--* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
--*
--*	NOTES:
--*		- use the '/' slash for all paths.
--*****************************************************************************

-- wxWidgets version
local wx_ver = "28"

--******* Initial Setup ************
--*	Most of the setting are set here.
--**********************************

-- Set the name of your package.
package.name = "plugin-interface"
-- Set this if you want a different name for your target than the package's name.
local targetName = "fbPluginInterface"
-- Set the kind of package you want to create.
--		Options: exe | winexe | lib | dll
package.kind = "lib"
-- Set the files to include.
package.files = { matchrecursive( "*.cpp", "*.h", "*.rc", "*.fbp" ) }
-- Set the include paths.
package.includepaths = { "../tinyxml" }
-- Set the libraries it links to.
package.links = { "TiCPP" }
package.libdir = "../lib"
-- Set the defines.
package.defines = { "TIXML_USE_TICPP" }

-- Hack the dll output to prefix 'lib' to the begining.
package.targetprefix = "lib"

--------------------------- DO NOT EDIT BELOW ----------------------------------

--******* GENAERAL SETUP **********
--*	Settings that are not dependant
--*	on the operating system.
--*********************************
-- Package options
addoption( "unicode", "Use the Unicode character set" )
addoption( "with-wx-shared", "Link against wxWidgets as a shared library" )
if ( not windows ) then
	addoption( "disable-wx-debug", "Compile against a wxWidgets library without debugging" )
end

-- Common setup
package.language = "c++"

-- Set object output directory.
if ( options["unicode"] ) then
	package.config["Debug"].objdir = ".objsud"
	package.config["Release"].objdir = ".objsu"
else
	package.config["Debug"].objdir = ".objsd"
	package.config["Release"].objdir = ".objs"
end

-- Set debug flags
if ( options["disable-wx-debug"] and ( not windows ) ) then
	debug_option = "--debug=no"
	debug_macro = { "NDEBUG", "__wxWEAVER_DEBUG__" }
else
	debug_option = "--debug=yes"
	debug_macro = { "DEBUG", "_DEBUG", "__WXDEBUG__", "__wxWEAVER_DEBUG__"}
end

-- Set the default targetName if none is specified.
if ( string.len( targetName ) == 0 ) then
	targetName = package.name
end

-- Set the targets.
package.config["Release"].target = targetName
package.config["Debug"].target = targetName.."d"

-- Set the build options.
package.buildflags = { "extra-warnings" }
package.config["Release"].buildflags = { "no-symbols", "optimize-speed" }
if ( options["unicode"] ) then
	table.insert( package.buildflags, "unicode" )
end
if ( string.find( target or "", ".*-gcc" ) or target == "gnu" ) then
	table.insert( package.config["Debug"].buildoptions, "-O0" )
	table.insert( package.config["Release"].buildoptions, "-fno-strict-aliasing" )
end

-- Set the defines.
if ( options["with-wx-shared"] ) then
	table.insert( package.defines, "WXUSINGDLL" )
end
if ( options["unicode"] ) then
	table.insert( package.defines, { "UNICODE", "_UNICODE" } )
end
table.insert( package.defines, "__WX__" )
table.insert( package.config["Debug"].defines, debug_macro )
table.insert( package.config["Release"].defines, "NDEBUG" )

if ( windows ) then
--******* WINDOWS SETUP ***********
--*	Settings that are Windows specific.
--*********************************
	-- Set wxWidgets include paths
	if ( target == "cb-gcc" ) then
		table.insert( package.includepaths, "$(#WX.include)" )
	else
		table.insert( package.includepaths, "$(WXWIN)/include" )
	end

	-- Set the correct 'setup.h' include path.
	if ( options["with-wx-shared"] ) then
		if ( options["unicode"] ) then
			if ( target == "cb-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswud" )
				table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/mswu" )
			elseif ( target == "gnu" or target == "cl-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswud" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/mswu" )
			else
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswud" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/mswu" )
			end
		else
			if ( target == "cb-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_dll/mswd" )
				table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_dll/msw" )
			elseif ( target == "gnu" or target == "cl-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_dll/mswd" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_dll/msw" )
			else
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_dll/mswd" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_dll/msw" )
			end
		end
	else
		if ( options["unicode"] ) then
			if ( target == "cb-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_lib/mswud" )
				table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_lib/mswu" )
			elseif ( target == "gnu" or target == "cl-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_lib/mswud" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_lib/mswu" )
			else
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_lib/mswud" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_lib/mswu" )
			end
		else
			if ( target == "cb-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(#WX.lib)/gcc_lib/mswd" )
				table.insert( package.config["Release"].includepaths, "$(#WX.lib)/gcc_lib/msw" )
			elseif ( target == "gnu" or target == "cl-gcc" ) then
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/gcc_lib/mswd" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/gcc_lib/msw" )
			else
				table.insert( package.config["Debug"].includepaths, "$(WXWIN)/lib/vc_lib/mswd" )
				table.insert( package.config["Release"].includepaths, "$(WXWIN)/lib/vc_lib/msw" )
			end
		end
	end

	-- Set the linker options.
	if ( options["with-wx-shared"] ) then
		if ( target == "cb-gcc" ) then
			table.insert( package.libpaths, "$(#WX.lib)/gcc_dll" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.libpaths, "$(WXWIN)/lib/gcc_dll" )
		else
			table.insert( package.libpaths, "$(WXWIN)/lib/vc_dll" )
		end
	else
		if ( target == "cb-gcc" ) then
			table.insert( package.libpaths, "$(#WX.lib)/gcc_lib" )
		elseif ( target == "gnu" or target == "cl-gcc" ) then
			table.insert( package.libpaths, "$(WXWIN)/lib/gcc_lib" )
		else
			table.insert( package.libpaths, "$(WXWIN)/lib/vc_lib" )
		end
	end

	-- Set wxWidgets libraries to link.
	if ( options["unicode"] ) then
		table.insert( package.config["Release"].links, "wxmsw"..wx_ver.."u" )
		table.insert( package.config["Debug"].links, "wxmsw"..wx_ver.."ud" )
	else
		table.insert( package.config["Release"].links, "wxmsw"..wx_ver )
		table.insert( package.config["Debug"].links, "wxmsw"..wx_ver.."d" )
	end

	-- Set the Windows defines.
	table.insert( package.defines, { "__WXMSW__", "WIN32", "_WINDOWS" } )
else
--******* LINUX SETUP *************
--*	Settings that are Linux specific.
--*********************************
	-- Ignore resource files in Linux.
	table.insert( package.excludes, matchrecursive( "*.rc" ) )

	table.insert( package.buildoptions, "-fPIC" )

	-- Set wxWidgets build options.
	table.insert( package.config["Debug"].buildoptions, "`wx-config "..debug_option.." --cflags`" )
	table.insert( package.config["Release"].buildoptions, "`wx-config --debug=no --cflags`" )

	-- Set the wxWidgets link options.
	table.insert( package.config["Debug"].linkoptions, "`wx-config "..debug_option.." --libs`" )
	table.insert( package.config["Release"].linkoptions, "`wx-config --libs`" )
end
