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

#include "fontcontainer.h"

#include <wx/wx.h>

#include <vector>
#include <utility>

/** Component type.
*/
enum class ComponentType {
    Abstract,
    Window,
    Sizer
};

namespace ticpp {
class Element;
}

class IComponent;

#if 0
// TODO: Unused, determine if to remove.
/** Sections of the generated source code.
*/
enum {
    CG_DECLARATION,
    CG_CONSTRUCTION,
    CG_POST_CONSTRUCTION,
    CG_SETTINGS
};
// Programming languages for source code generation
enum {
    CG_CPP
};
#endif

/** Plugins interface.

    Provides an interface for accessing the object's properties
    from the plugin itself in a safe way.
*/
class IObject {
public:
    virtual ~IObject() { }

    virtual IObject* GetChildPtr(size_t index) = 0;
    virtual bool IsNull(const wxString& name) const = 0;

    virtual wxBitmap GetPropertyAsBitmap(const wxString& name) const = 0;
    virtual wxColour GetPropertyAsColour(const wxString& name) const = 0;
    virtual wxFontContainer GetPropertyAsFont(const wxString& name) const = 0;
    virtual wxPoint GetPropertyAsPoint(const wxString& name) const = 0;
    virtual wxSize GetPropertyAsSize(const wxString& name) const = 0;
    virtual wxString GetPropertyAsString(const wxString& name) const = 0;
    virtual wxArrayInt GetPropertyAsArrayInt(const wxString& name) const = 0;
    virtual wxArrayString GetPropertyAsArrayString(const wxString& name) const = 0;
    virtual std::vector<std::pair<int, int>> GetPropertyAsVectorIntPair(const wxString& name) = 0;
    virtual double GetPropertyAsFloat(const wxString& name) const = 0;
    virtual int GetPropertyAsInteger(const wxString& name) const = 0;

    virtual wxString GetClassName() const = 0;
    virtual wxString GetChildFromParentProperty(const wxString& parentName,
                                                const wxString& childName) const = 0;
    virtual wxString GetTypeName() const = 0;
    virtual size_t GetChildCount() const = 0;
};

/** Interface which intends to contain all the components for a plugin

    This is an abstract class and it'll be the object that the DLL will export.
*/
class IComponentLibrary {
public:
    // Used by the plugin for registering components and macros
    virtual void RegisterComponent(const wxString& text, IComponent* c) = 0;
    virtual void RegisterMacro(const wxString& text, int value) = 0;
    virtual void RegisterMacroSynonymous(const wxString& text, const wxString& name) = 0;

    // Used by wxWeaver for recovering components and macros
    virtual IComponent* GetComponent(size_t index) = 0;
    virtual wxString GetComponentName(size_t index) const = 0;
    virtual wxString GetMacroName(size_t i) const = 0;
    virtual int GetMacroValue(size_t i) const = 0;
#if 0
    virtual wxString GetMacroSynonymous(size_t i) const = 0;
    virtual wxString GetSynonymousName(size_t i) const = 0;
#endif
    virtual wxString GetSynonymous(const wxString& synonymous) const = 0;

    virtual size_t GetMacroCount() const = 0;
    virtual size_t GetComponentCount() const = 0;
#if 0
    virtual size_t GetSynonymousCount() const = 0;
#endif
    virtual ~IComponentLibrary()
    {
    }
};

/** Component Interface
*/
class IComponent {
public:
    /** Virtual destructor
    */
    virtual ~IComponent() { }

    /** Create an instance of the wxObject and return a pointer
    */
    virtual wxObject* Create(IObject* obj, wxObject* parent) = 0;

    /** Cleanup (do the reverse of Create)
    */
    virtual void Cleanup(wxObject* obj) = 0;

    /** Allows components to do something after they have been created.

        For example, abstract components like `notebookpage` and `sizeritem` can
        add the actual widget to the wxNotebook or wxSizer.
        Fired after the creation of children,
        which will be accessible from this event handler.

        @param wxobject The object which was just created.
        @param wxparent The parent to which the created object was added.
    */
    virtual void OnCreated(wxObject* wxobject, wxWindow* wxparent) = 0;

    /** Allows components to respond when selected in object tree.

        For example, when a wxNotebook's page is selected,
        it can switch to that page
    */
    virtual void OnSelected(wxObject* wxobject) = 0;

    /** Export the object to an XRC node
    */
    virtual ticpp::Element* ExportToXrc(IObject* obj) = 0;

    /** Converts from an XRC element to a wxWeaver project file XML element
    */
    virtual ticpp::Element* ImportFromXrc(ticpp::Element* xrcObj) = 0;

    /** Returns the component type.
    */
    virtual ComponentType GetComponentType() const = 0;
};

/** Used to identify the wxObject that must be manually deleted.
*/
class wxNoObject : public wxObject {
};

/** Interface to the "Manager" class in the application.

    Essentially a collection of utility functions that take a wxObject pointer
    and do something useful.
*/
class IManager {
public:
    /** Get the count of the children of this object.
    */
    virtual size_t GetChildCount(wxObject* wxobject) const = 0;

    /** Returns the child of the object.

        @param wxobject   The pointer to the wxWidgets parent.
        @param childIndex Index of the child to get.
    */
    virtual wxObject* GetChild(wxObject* wxobject, size_t childIndex) = 0;

    /** Returns the parent of the object.
    */
    virtual wxObject* GetParent(wxObject* wxobject) = 0;

    /** Returns the IObject interface to the parent of the object.
    */
    virtual IObject* GetIParent(wxObject* wxobject) = 0;

    /** Returns the corresponding object interface pointer for the object.

        This allows easy read only access to properties.
    */
    virtual IObject* GetIObject(wxObject* wxobject) = 0;

    /** Edit a property of the object.

        @param property  The name of the property to modify.
        @param value     The new value for the property.
        @param allowUndo If @true, the property change will be placed into
                         the undo stack, if false it will be modified silently.
    */
    virtual void ModifyProperty(wxObject* wxobject, const wxString& property,
                                const wxString& value, bool allowUndo = true)
        = 0;

    /** Used so the wxNoObjects are both created and destroyed in the application.
    */
    virtual wxNoObject* NewNoObject() = 0;

    /** Select the object in the object tree.

        Returns @true if selection changed, @false if already selected.
    */
    virtual bool SelectObject(wxObject* wxobject) const = 0;

    virtual ~IManager() { }
};

#ifdef BUILD_DLL
#define DLL_FUNC extern "C" WXEXPORT
#else
#define DLL_FUNC extern "C"
#endif

// Function that the application calls to get the library
DLL_FUNC IComponentLibrary* GetComponentLibrary(IManager* manager);

// Function that the application calls to free the library
DLL_FUNC void FreeComponentLibrary(IComponentLibrary* lib);

#define BEGIN_LIBRARY()                                                           \
                                                                                  \
    extern "C" WXEXPORT IComponentLibrary* GetComponentLibrary(IManager* manager) \
    {                                                                             \
        IComponentLibrary* lib = new ComponentLibrary();

#define END_LIBRARY()                                                     \
    return lib;                                                           \
    }                                                                     \
    extern "C" WXEXPORT void FreeComponentLibrary(IComponentLibrary* lib) \
    {                                                                     \
        delete lib;                                                       \
    }

#define MACRO(name) \
    lib->RegisterMacro(#name, name);

#define SYNONYMOUS(syn, name) \
    lib->RegisterMacroSynonymous(#syn, #name);

#define _REGISTER_COMPONENT(name, class, type) \
    {                                          \
        ComponentBase* c = new class();        \
        c->RegisterComponentType(type);        \
        c->RegisterManager(manager);           \
        lib->RegisterComponent(name, c);       \
    }

#define WINDOW_COMPONENT(name, class) \
    _REGISTER_COMPONENT(name, class, ComponentType::Window)

#define SIZER_COMPONENT(name, class) \
    _REGISTER_COMPONENT(name, class, ComponentType::Sizer)

#define ABSTRACT_COMPONENT(name, class) \
    _REGISTER_COMPONENT(name, class, ComponentType::Abstract)
