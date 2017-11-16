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

// We know the FluxNode class
class FluxNode;

// We know the FluxRoot class
class FluxRoot;

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxProject
////////////////////////////////////////////////////////////////////////////////
class FluxProject
{
private:

	// The FluxNode is a friend class
	friend FluxNode;

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

	// Return a reference to our root node
	FluxRoot* GetRootNode();

public:

	// Save the project info
	void SaveProjectInfo();

	// Load the project info
	void LoadProjectInfo(std::string _projectName);

	// Save the project data
	void SaveProjectData();

	// Load the project data
	void LoadProjectData();

	// Generate a unique identifier for the given type
	FluxUniqueIdentifier GenerateUniqueIdentifier(Type _identifierType);

protected:

///////////////
// VARIABLES //
private: //////

	// The project external name
	std::string m_ProjectExternalName;

	// The project internal name (when set, this will never change)
	std::string m_ProjectInternalName;

	// The project unique identifier number
	uint32_t m_UniqueIdentifierNumber;

	// Our root node
	FluxRoot* m_RootNode;
};

// SmallPack
FluxNamespaceEnd(Flux)