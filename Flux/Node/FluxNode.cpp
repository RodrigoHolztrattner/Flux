////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxNode.h"
#include "..\FluxUniqueIdentifier.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxNode::FluxNode(FluxProject* _project, FluxUniqueIdentifier _uniqueIdentifier)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Set the initial data
	m_UniqueIdentifier = _uniqueIdentifier;
	m_Verified = false;
	m_MemberFromClass = false;
	m_ExternalName = "dummy";
	m_InternalIndexNumber = 0;

	// Add this node
	fluxHolderInstance->InsertNodeWithIdentifier(this, _uniqueIdentifier);
}

Flux::FluxNode::FluxNode(const Flux::FluxNode& other)
{
}

Flux::FluxNode::~FluxNode()
{
}

void Flux::FluxNode::SetExternalName(std::string _name)
{
	// Set the external name
	m_ExternalName = _name;
}

Flux::FluxUniqueIdentifier Flux::FluxNode::GetUniqueIdentifier()
{
	return m_UniqueIdentifier;
}

bool Flux::FluxNode::NodeFromIdentifierExist(FluxUniqueIdentifier _identifier)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check
	return fluxHolderInstance->NodeFromIdentifierExist(_identifier);
}

void Flux::FluxNode::SetParent(FluxUniqueIdentifier _parent)
{
	// Get the dependency manager instance
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if we should remove an old relation
	if (m_ParentNode.Initialized())
	{
		// Remove this relation
		dependencyManagerInstance->RemoveDependencyRelation(GetUniqueIdentifier(), m_ParentNode, FluxDependencyRelationType::SrcDependsOnDst);
	}

	// Create the mutual dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _parent, FluxDependencyRelationType::SrcDependsOnDst);

	// Check if the parent is a class
	// If true, set that we are a member TODO
	
	// Set the parent
	m_ParentNode = _parent;

	// Notify all dependencies (signature changed)
	dependencyManagerInstance->NotifyDependencies(GetUniqueIdentifier(), FluxDependencyNotifyType::SignatureChanged);
}

bool Flux::FluxNode::IsVerified()
{
	return m_Verified;
}

void Flux::FluxNode::Invalidate()
{
	m_Verified = false;
}

uint32_t Flux::FluxNode::GetUniqueInternalNumber()
{
	return m_InternalIndexNumber++;
}