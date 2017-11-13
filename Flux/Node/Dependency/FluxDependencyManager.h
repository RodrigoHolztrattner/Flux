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
	
////////////////////////////////////////////////////////////////////////////////
// Class name: FluxDependencyManager
////////////////////////////////////////////////////////////////////////////////
class FluxDependencyManager
{
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

	// 

private:

	// Check if a identifier has any dependency (and return a ptr to them, else return nullptr
	Flux::FluxDependency* GetIdentifierDependencies(const Flux::FluxUniqueIdentifier& _identifier, bool _create = false);

	// Create a dependency, src depends on dst
	bool CreateDependency(const Flux::FluxUniqueIdentifier& _sourceIdentifier, const Flux::FluxUniqueIdentifier& _destinationIdentifier);

///////////////
// VARIABLES //
private: //////

	// All dependencies
	std::map<Flux::FluxUniqueIdentifier, Flux::FluxDependency*> m_DependencyObjects;
};

// SmallPack
FluxNamespaceEnd(Flux)