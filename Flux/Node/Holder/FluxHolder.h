////////////////////////////////////////////////////////////////////////////////
// Filename: FluxHolder.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\FluxNode.h"
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
// Class name: FluxHolder
////////////////////////////////////////////////////////////////////////////////
class FluxHolder
{
public:

public:
	FluxHolder();
	FluxHolder(const FluxHolder&);
	~FluxHolder();

public:

	// Insert a new object
	bool InsertNodeWithIdentifier(Flux::FluxNode* _node, FluxUniqueIdentifier _identifier);

	// Remove an object
	bool RemoveNodeWithIdentifier(FluxUniqueIdentifier _identifier);

	// Return a object with the given identifier if it exist
	Flux::FluxNode* GetNodeWithIdentifier(FluxUniqueIdentifier _identifier);

	// Check if a node from the given info exist
	bool NodeFromIdentifierExist(Flux::FluxUniqueIdentifier _identifier);

	// Return a reference to our object array
	std::map<FluxUniqueIdentifier, Flux::FluxNode*>& GetNodeObjects();

///////////////
// VARIABLES //
private: //////

	// All objects
	std::map<FluxUniqueIdentifier, Flux::FluxNode*> m_Objects;
};

// SmallPack
FluxNamespaceEnd(Flux)