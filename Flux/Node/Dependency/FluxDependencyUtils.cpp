////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependencyUtils.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxDependencyUtils.h"
#include "..\FluxNode.h"
#include "FluxDependencyManager.h"

Flux::FluxDependencyUtils::FluxDependencyUtils(Flux::FluxNode* _internalPtr)
{
	// Set the initial data
	m_InternalPtr = _internalPtr;
}

Flux::FluxDependencyUtils::~FluxDependencyUtils()
{
}

void Flux::FluxDependencyUtils::AddDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType)
{
	// Correct the internal ptr
	m_InternalPtr = (Flux::FluxNode*)this;

	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the dst is valid
	if (_dst.Initialized())
	{
		// Create the dependency
		dependencyManagerInstance->AddDependencyRelation(*m_InternalPtr, _dst, _relationType);
	}
}

void Flux::FluxDependencyUtils::RemoveDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType)
{
	// Correct the internal ptr
	m_InternalPtr = (Flux::FluxNode*)this;

	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the dst is valid
	if (_dst.Initialized())
	{
		// Remove the dependency
		dependencyManagerInstance->RemoveDependencyRelation(*m_InternalPtr, _dst, _relationType);
	}
}

void Flux::FluxDependencyUtils::SwapDependencyRelation(FluxUniqueIdentifier& _old, FluxUniqueIdentifier& _newDst, FluxDependencyRelationType _relationType)
{
	// Correct the internal ptr
	m_InternalPtr = (Flux::FluxNode*)this;

	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the old identifier is valid
	if (_old.Initialized())
	{
		// Remove the dependency
		dependencyManagerInstance->RemoveDependencyRelation(*m_InternalPtr, _old, _relationType);

		// Invalidate the old identifier
		_old.Invalidate();
	}

	// Check if the dst is valid
	if (_newDst.Initialized())
	{
		// Create the dependency
		dependencyManagerInstance->AddDependencyRelation(*m_InternalPtr, _newDst, _relationType);
	}
}

void Flux::FluxDependencyUtils::NotifyDependencies(Flux::FluxDependencyNotifyType _notifyType)
{
	// Correct the internal ptr
	m_InternalPtr = (Flux::FluxNode*)this;

	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Notify
	dependencyManagerInstance->NotifyDependencies(*m_InternalPtr, _notifyType);
}