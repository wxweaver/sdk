-----------------------------------------------------------------------------
--  Name:        plugin_interface.lua
--  Purpose:     Plugin Interface library project script.
--  Author:      Andrea Zanellato zanellato.andrea@gmail.com
--  Modified by:
--  Created:     20/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--               (c) 2021 wxWeaver Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
project "plugin-interface"
    kind "StaticLib"
    files
    {
        "../../sdk/plugin_interface/**.h",
        "../../sdk/plugin_interface/**.cpp",
        "../../sdk/plugin_interface/**.fbp"
    }
    includedirs         {"../../subprojects/ticpp"}
    targetdir           "../../sdk/lib"
    defines             {"TIXML_USE_TICPP"}
    targetsuffix        ("-" .. wxVersion)

    configuration "not vs*"
        buildoptions    "-std=c++17"

    configuration "vs*"
        defines         {"_CRT_SECURE_NO_DEPRECATE", "_CRT_SECURE_NO_WARNINGS"}
        buildoptions    "/std:c++17"

    configuration "not windows"
        buildoptions    {"-fPIC"}

    configuration "Debug"
        wx_config       {Debug="yes", WithoutLibs="yes"}
        targetname      (CustomPrefix .. wxDebugSuffix .. "_plugin-interface")

    configuration "Release"
        wx_config       {WithoutLibs="yes"}
        targetname      (CustomPrefix .. "_plugin-interface")

    configuration {"not vs*", "Release"}
        buildoptions    {"-fno-strict-aliasing"}
