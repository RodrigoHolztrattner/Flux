////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependencyUtils.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\..\FluxUniqueIdentifier.h"
#include "FluxDependencyInterface.h"

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
// Class name: FluxDependencyUtils
////////////////////////////////////////////////////////////////////////////////
class FluxDependencyUtils
{
	// We have some friends
	friend FluxNode;

public:
	FluxDependencyUtils(Flux::FluxNode* _internalPtr);
	~FluxDependencyUtils();

protected:

	// Add/remove/swap a dependency relation (those functions always verify if the src and dst are valid)
	void AddDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType);
	void RemoveDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType);
	void SwapDependencyRelation(FluxUniqueIdentifier& _old, FluxUniqueIdentifier& _newDst, FluxDependencyRelationType _relationType);
	void NotifyDependencies(Flux::FluxDependencyNotifyType _notifyType);

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