////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "FluxConfig.h"
#include "FluxUniqueIdentifier.h"
#include <string>

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
// Class name: FluxProject
////////////////////////////////////////////////////////////////////////////////
class FluxProject
{
private:

	// The project file extension we are going to use
	const std::string ProjectFileExtension = ".info";

public:
	FluxProject();
	FluxProject(const FluxProject&);
	~FluxProject();

	// Set the project external name
	void SetExternalProjectName(std::string _projectName);

	// Return the project external name
	std::string GetExternalProjectName();

	// Return the project internal name
	std::string GetInternalProjectName();

public:

	// Save the project info
	void SaveProjectInfo();

	// Load the project info
	void LoadProjectInfo(std::string _projectName);

	// Generate a unique identifier for the given type
	FluxUniqueIdentifier GenerateUniqueIdentifier(Type _identifierType);

private:

///////////////
// VARIABLES //
private: //////

	// The project external name
	std::string m_ProjectExternalName;

	// The project internal name (when set, this will never change)
	std::string m_ProjectInternalName;

	// The project unique identifier number
	uint32_t m_UniqueIdentifierNumber;
};

// SmallPack
FluxNamespaceEnd(Flux)