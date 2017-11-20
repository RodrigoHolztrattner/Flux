////////////////////////////////////////////////////////////////////////////////
// Filename: FluxHolderUtils.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\..\FluxUniqueIdentifier.h"

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

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxHolderUtils
////////////////////////////////////////////////////////////////////////////////
class FluxHolderUtils
{
	// We have some friends
	friend FluxNode;

public:
	FluxHolderUtils(Flux::FluxNode* _internalPtr);
	~FluxHolderUtils();

protected:

	// Check if a node from the given identifier exist
	bool NodeFromIdentifierExist(FluxUniqueIdentifier _identifier);

	// Check if the given identifier was initialized, if it is valid and if it is from the given type
	bool NodeFromIdentifierIsValidAndFromType(FluxUniqueIdentifier _identifier, Type _type);

	// Check if the given identifier is from a valid type (variable/parameter type in this case)
	bool NodeFromIdentifierIsValidAsType(FluxUniqueIdentifier _identifier);

protected:

	// Set the node internal ptr
	void SetInternalPtr(Flux::FluxNode* _ptr) { m_InternalPtr = _ptr; }

///////////////
// VARIABLES //
private: //////

	// Our internal node ptr
	Flux::FluxNode* m_InternalPtr;
};

// SmallPack
FluxNamespaceEnd(Flux)