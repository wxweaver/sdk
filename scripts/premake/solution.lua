-----------------------------------------------------------------------------
--  Name:        solution.lua
--  Purpose:     Generic Premake 4 solution defining common configurations
--               for all projects it contains.
--  Author:      Andrea Zanellato
--  Modified by:
--  Created:     19/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--               (c) 2021 wxWeaver Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
solution "wxWeaver-Solution"
    language "C++"
    configurations      {"Debug", "Release"}
    if (startproject ~= nil) then
        startproject    "wxWeaver"
    end

    local scriptDir     = os.getcwd()

    -- The wxWidgets Configuration-Script parses the corresponding command line flags
    -- for the architecture, its configuration function works only for one architecture
    -- hence only one platform can be specified.
    -- Don't specify the platform if none is specified to prevent the creation
    -- of tagged configuration names.
    dofile(scriptDir .. "/wxwidgets.lua")
    if platforms then
        if (wxArchitecture == "x86_64") then
            platforms   {"Win64"}
        elseif (wxArchitecture == "x86") then
            platforms   {"Win32"}
        end
    end

    local wxver         = string.gsub(wxVersion, '%.', '')
    location            ("../../build/" .. wxVersion .. "/" .. _ACTION)
    BuildDir            = solution().location
    CustomPrefix        = "wx_" .. wxTarget .. wxUnicodeSign
    DebugSuffix         = "-" .. wxver

    os.chdir(BuildDir)

    --if wxCompiler == "gcc" and os.is("windows") then
    --    flags           {"NoImportLib"}
    --end

    if wxUseUnicode then
        -- The Unicode flag got removed in Premake 5.x but is still required for Premake 4.x,
        -- use the presence of the workspace function to detect if running under Premake 5.x
        if (workspace == nil) then
            flags       {"Unicode"}
        end
        defines         {"UNICODE", "_UNICODE"}
    end

    configuration "windows"
        defines         {"WIN32", "_WINDOWS"}

    configuration "macosx"
        -- adding symbols so that premake does not include the "Wl,x"
        -- flags, as these flags make clang linking fail
        -- see http://industriousone.com/topic/how-remove-flags-ldflags
        flags           {"Symbols"}
        buildoptions    {"-Wno-overloaded-virtual"}

    configuration "Debug"
        defines         {"DEBUG", "_DEBUG"}
        flags           {"Symbols"}
        if wxCompiler == "gcc" then
            buildoptions{"-O0"}
        end

    configuration "Release"
        --if wxCompiler == "gcc" then
        --    linkoptions {"-s"}
        --end
        defines         {"NDEBUG"}
        flags           {"Optimize", "ExtraWarnings"}

    configuration {"not vs*", "Debug"}
        flags           {"ExtraWarnings"}

    configuration {"vs*", "Debug"}
        -- This produces D9025 because without ExtraWarnings /W3 gets set
        --buildoptions    {"/W4"}

--  dofile(scriptDir .. "/utilities.lua")

    dofile(scriptDir .. "/plugin-interface.lua")
    dofile(scriptDir .. "/ticpp.lua")

    dofile(scriptDir .. "/plugins/additional.lua")
    dofile(scriptDir .. "/plugins/common.lua")
    dofile(scriptDir .. "/plugins/containers.lua")
    dofile(scriptDir .. "/plugins/forms.lua")
    dofile(scriptDir .. "/plugins/layout.lua")

    -- The MacOS postbuild commands require that the plugins are already compiled,
    -- with Premake 4.x it is not possible to define a build order dependency for
    -- libraries without linking to them.
    -- Processing the wxweaver script after the plugin scripts results in a Makefile
    -- that does process wxWeaver after the plugin projects without defining a dependency between them.
    -- This will break when using parallel builds because of the missing dependencies.
    dofile(scriptDir .. "/wxweaver.lua")
