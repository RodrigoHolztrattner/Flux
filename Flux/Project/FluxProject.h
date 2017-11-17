////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProject.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "..\FluxUniqueIdentifier.h"
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

	// The project file info extension we are going to use
	const std::string ProjectInfoFileExtension = ".info";

	// The project file data extension we are going to use
	const std::string ProjectDataFileExtension = ".dat";

public:
	FluxProject();
	FluxProject(const FluxProject&);
	~FluxProject();

	// Create a new project
	bool CreateNewProject(std::string _projectName);

	// Load a project
	bool LoadProject(std::string _projectFilePath);

	// Save the current project
	bool SaveProject();

public:

	// Set the project external name
	void SetExternalProjectName(std::string _projectName);

	// Return the project external name
	std::string GetExternalProjectName();

	// Return the project internal name
	std::string GetInternalProjectName();

	// Return a reference to our root node
	FluxRoot* GetRootNode();

public:

	// Generate a unique identifier for the given type
	FluxUniqueIdentifier GenerateUniqueIdentifier(Type _identifierType);

	// Conversion to the unique identifier type
	operator FluxUniqueIdentifier() const;

private:

	// Save the project info
	bool SaveProjectInfo();

	// Load the project info
	bool LoadProjectInfo(std::string _projectFilePath);

	// Save the project data
	bool SaveProjectData();

	// Load the project data
	bool LoadProjectData();

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

	// If this project was initialized
	bool m_Initialized;
};

// SmallPack
FluxNamespaceEnd(Flux)