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

#include "component.h"

#include <vector>
#include <map>
/*
    Library implementation. This module must be implemented inside the library,
    instead of linking it as an object for doing the plugin.
    We will make a template so that the preprocessor implements the library inside
    the module itself.
*/
class ComponentLibrary : public IComponentLibrary {
public:
    ~ComponentLibrary() override
    {
        std::vector<AComponent>::reverse_iterator component;
        for (component = m_components.rbegin();
             component != m_components.rend(); ++component) {
            delete component->component;
        }
    }

    void RegisterComponent(const wxString& text, IComponent* c) override
    {
        AComponent comp;
        comp.component = c;
        comp.name = text;

        m_components.push_back(comp);
    }

    void RegisterMacro(const wxString& text, const int value) override
    {
        AMacro macro;
        macro.name = text;
        macro.value = value;

        m_macros.push_back(macro);
    }

    void RegisterMacroSynonymous(const wxString& syn, const wxString& name) override
    {
#if 0
        ASynonymous asyn;
        asyn.name = name;
        asyn.syn = syn;

        m_synonymous.push_back(asyn);
#endif
        m_synMap.insert(SynMap::value_type(syn, name));
    }

    IComponent* GetComponent(size_t idx) override
    {
        if (idx < m_components.size())
            return m_components[idx].component;

        return nullptr;
    }

    wxString GetComponentName(size_t idx) const override
    {
        if (idx < m_components.size())
            return m_components[idx].name;

        return wxString();
    }

    wxString GetMacroName(size_t idx) const override
    {
        if (idx < m_macros.size())
            return m_macros[idx].name;

        return wxString();
    }

    int GetMacroValue(size_t idx) const override
    {
        if (idx < m_macros.size())
            return m_macros[idx].value;

        return 0;
    }
#if 0
    wxString GetMacroSynonymous(size_t idx) const override
    {
        if (idx < m_synonymous.size())
            return m_synonymous[idx].syn;

        return wxString();
    }

    wxString GetSynonymousName(size_t idx) const override
    {
        if (idx < m_synonymous.size())
            return m_synonymous[idx].name;

        return wxString();
    }
#endif
    wxString GetSynonymous(const wxString& synonymous) const override
    {
        SynMap::const_iterator it = m_synMap.find(synonymous);
        if (it != m_synMap.end())
            return it->second;

        return wxEmptyString;
    }

    size_t GetMacroCount() const override { return m_macros.size(); }

    size_t GetComponentCount() const override { return m_components.size(); }
#if 0
    size_t GetSynonymousCount() const override { return m_synonymous.size(); }
#endif

private:
    struct AComponent {
        wxString name;
        IComponent* component;
    };

    struct AMacro {
        wxString name;
        int value;
    };

    struct ASynonymous {
        wxString name, syn;
    };

    std::vector<AComponent> m_components;
    std::vector<AMacro> m_macros;
    typedef std::map<wxString, wxString> SynMap;
    SynMap m_synMap;
};

/** Base class for components
 */
class ComponentBase : public IComponent {
public:
    ComponentBase()
        : m_type(ComponentType::Abstract)
        , m_manager(nullptr)
    {
    }

    void RegisterComponentType(ComponentType type)
    {
        m_type = (type >= ComponentType::Abstract && type <= ComponentType::Sizer
                      ? type
                      : ComponentType::Abstract);
    }

    void RegisterManager(IManager* manager) { m_manager = manager; }

    IManager* GetManager() { return m_manager; }

    wxObject* Create(IObject* /*obj*/, wxObject* /*parent*/) override
    {
        // Even components which are not visible must be unique in the map
        return m_manager->NewNoObject();
    }

    void Cleanup(wxObject* /*obj*/) override { }

    void OnCreated(wxObject* /*wxobject*/, wxWindow* /*wxparent*/) override { }

    void OnSelected(wxObject* /*wxobject*/) override { }

    ticpp::Element* ExportToXrc(IObject* /*obj*/) override { return nullptr; }

    ticpp::Element* ImportFromXrc(ticpp::Element* /*xrcObj*/) override { return nullptr; }

    ComponentType GetComponentType() const override { return m_type; }

private:
    ComponentType m_type;
    IManager* m_manager;
};
