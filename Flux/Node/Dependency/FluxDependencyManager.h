////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependencyManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\..\FluxUniqueIdentifier.h"
#include "FluxDependency.h"
#include <vector>
#include <map>

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

// We know the FluxProjectArchiver class
class FluxProjectArchiver;

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxDependencyManager
////////////////////////////////////////////////////////////////////////////////
class FluxDependencyManager
{
	// The FluxProjectArchiver is a friend
	friend FluxProjectArchiver;

public:

public:
	FluxDependencyManager();
	FluxDependencyManager(const FluxDependencyManager&);
	~FluxDependencyManager();

	// Add dependency relation
	void AddDependencyRelation(Flux::FluxUniqueIdentifier _sourceIdentifier, Flux::FluxUniqueIdentifier _destinationIdentifier, FluxDependencyRelationType _relation);

	// Remove a dependency 
	void RemoveDependencyRelation(Flux::FluxUniqueIdentifier _sourceIdentifier, Flux::FluxUniqueIdentifier _destinationIdentifier, FluxDependencyRelationType _relation);

	// Notify all dependencies that the given identifier have
	void NotifyDependencies(Flux::FluxUniqueIdentifier _identifier, FluxDependencyNotifyType _notifyType);

	// Check if the given identifier have any dependency
	bool IdentifierHaveDependencies(Flux::FluxUniqueIdentifier _identifier);

protected:

	// Return all dependencies from the given project
	std::vector<Flux::FluxDependency> GetDependenciesFromProject(std::string _projectInternalName);

	// Construct dependencies from the given dependency vector
	void ConstructDependencies(std::vector<Flux::FluxDependency>& _dependencyVector);

private:

	// Check if a identifier has any dependency (and return a ptr to them, else return nullptr
	Flux::FluxDependency* GetIdentifierDependencies(const Flux::FluxUniqueIdentifier& _identifier, bool _create = false);

	// Create a dependency, src depends on dst
	bool CreateDependency(Flux::FluxUniqueIdentifier& _sourceIdentifier, Flux::FluxUniqueIdentifier& _destinationIdentifier);

	// Remove a dependency, src depends on dst
	bool RemoveDependency(Flux::FluxUniqueIdentifier& _sourceIdentifier, Flux::FluxUniqueIdentifier& _destinationIdentifier);

///////////////
// VARIABLES //
private: //////

	// All dependencies
	std::map<Flux::FluxUniqueIdentifier, Flux::FluxDependency*> m_DependencyObjects;
};

// SmallPack
FluxNamespaceEnd(Flux)