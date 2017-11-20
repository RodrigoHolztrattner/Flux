////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProjectFile.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\..\FluxUniqueIdentifier.h"
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
// Class name: FluxProjectFile
////////////////////////////////////////////////////////////////////////////////
class FluxProjectFile
{
private:

	// The namespace extension type
	const std::string NamespaceExtensionType	= ".namespace";

	// The class extension type
	const std::string ClassExtensionType		= ".class";

private:

	// The class file
	struct ClassFile
	{
		// The name
		std::string className;

		// The path (with name)
		std::string classPath;
	};

	// The namespace file
	struct NamespaceFile
	{
		// If this namespace is the root project
		bool namespaceIsRootProject;

		// The name
		std::string namespaceName;

		// The path (with name)
		std::string namespacePath;

		// All the sub classes
		std::vector<ClassFile*> namespaceSubClasses;

		// All the sub namespaces
		std::vector<NamespaceFile*> namespaceSubNamespaces;
	};

public:
	FluxProjectFile();
	FluxProjectFile(const FluxProjectFile&);
	~FluxProjectFile();

	bool LoadProject(std::string _projectLocation);

public:

	// Delete this project file
	void Delete();

	// Return if this project file was initialized
	bool Initialized() { return m_Initialized; }

private:

	// Load a project recursively
	bool LoadProjectRecursively(std::string _currentPath, NamespaceFile* _currentNamespace);

	// Delete a project recursively
	void DeleteProjectRecursively(NamespaceFile* _currentNamespace);

	// Create a root namespace for path
	bool CreateRootNamespace(std::string _path);

///////////////
// VARIABLES //
private: //////

	// If this project file was initialized
	bool m_Initialized;

	// The root namespace
	NamespaceFile* m_RootNamespace;
};

// SmallPack
FluxNamespaceEnd(Flux)