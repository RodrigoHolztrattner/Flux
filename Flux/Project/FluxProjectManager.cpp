////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProjectManager.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxProjectManager.h"
#include <json.hpp>
#include <iostream>
#include <fstream>

Flux::FluxProjectManager::FluxProjectManager()
{
	// Set the initial data
	// ...
}

Flux::FluxProjectManager::FluxProjectManager(const Flux::FluxProjectManager& other)
{
}

Flux::FluxProjectManager::~FluxProjectManager()
{
}

bool Flux::FluxProjectManager::AddProject(Flux::FluxProject* _project)
{
	// Check if there is a project with the same name
	if (GetProjectWithInternalName(_project->GetInternalProjectName()) != nullptr)
	{
		// We cant add this project
		return false;
	}

	// Add the new project
	m_LoadedProjects.push_back(_project);

	return true;
}

Flux::FluxProject* Flux::FluxProjectManager::GetProjectWithInternalName(std::string _internalName)
{
	// For each loaded project
	for (unsigned int i=0; i<m_LoadedProjects.size(); i++)
	{
		// Compare the internal name
		if (m_LoadedProjects[i]->GetInternalProjectName().compare(_internalName) == 0)
		{
			return m_LoadedProjects[i];
		}
	}

	return nullptr;
}