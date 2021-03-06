////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProjectManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "FluxProject.h"
#include <string>
#include <vector>

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// SmallPack
FluxNamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxProjectManager
////////////////////////////////////////////////////////////////////////////////
class FluxProjectManager
{
private:

public:
	FluxProjectManager();
	FluxProjectManager(const FluxProjectManager&);
	~FluxProjectManager();

public:

	// Add a project
	bool AddProject(Flux::FluxProject* _project);

	// Return a project reference by it internal name
	FluxProject* GetProjectWithInternalName(std::string _internalName);

protected:

///////////////
// VARIABLES //
private: //////

	// All loaded projects
	std::vector<Flux::FluxProject*> m_LoadedProjects;
};

// SmallPack
FluxNamespaceEnd(Flux)