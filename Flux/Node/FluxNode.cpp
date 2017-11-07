////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxNode.h"
#include "..\FluxUniqueIdentifier.h"
#include "Holder\FluxHolder.h"

Flux::FluxNode::FluxNode()
{
	// Get the unique identifier object instance
	// Flux::GlobalInstance<Flux::FluxUniqueIdentifier> g_UniqueIdentifierInstance;

	// Get a unique identifier
	// m_UniqueIdentifier = g_UniqueIdentifierInstance->GetUniqueIdentifier();

	// Set the initial data
	m_Type = Type::Unknow;
}

Flux::FluxNode::FluxNode(const Flux::FluxNode& other)
{
}

Flux::FluxNode::~FluxNode()
{
}

Flux::FluxUniqueIdentifier Flux::FluxNode::GetUniqueIdentifier()
{
	return m_UniqueIdentifier;
}

Flux::FluxNode::Type Flux::FluxNode::GetType()
{
	return m_Type;
}

bool Flux::FluxNode::CreateDependencyFromUsToNodeInfo(NodeInfo _nodeInfo)
{
	// Get the global holder instance
	Flux::GlobalInstance<Flux::FluxHolder> holderInstance;

	// Get the node
	Flux::FluxNode* otherNode = holderInstance->GetNodeFromInfo(_nodeInfo);
	if (otherNode == nullptr)
	{
		// Invalid node
		return false;
	}

	// Check if we already have this dependency (and just increment the counter)

	// Create the new node info
	NodeInfo nodeInfo;
	nodeInfo.type = m_Type;
	nodeInfo.uniqueIdentifier = m_UniqueIdentifier;

	// Create 

	// Add the dependency
	// otherNode->m_ReferencedNodeInfo.push_back(nodeInfo);

	return true;
}

bool Flux::FluxNode::NodeFromIdentifierOfTypeExist(FluxUniqueIdentifier _identifier, Type _type)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Set the node info
	NodeInfo nodeInfo;
	nodeInfo.uniqueIdentifier = _identifier;
	nodeInfo.type = _type;

	// Check
	return fluxHolderInstance->NodeFromInfoExist(nodeInfo);
}

void Flux::FluxNode::AddChildAndSetParentForNode(FluxUniqueIdentifier _identifier, Type _type)
{
	// Get the global holder instance
	Flux::GlobalInstance<Flux::FluxHolder> holderInstance;

	// Get the node
	Flux::FluxNode* childNode = holderInstance->GetNodeFromInfo(NodeInfo(_identifier, _type));
	if (childNode == nullptr)
	{
		// Invalid node
		return;
	}
	
	// Create the dependency
	if (!CreateDependencyFromUsToNodeInfo(Flux::FluxNode::NodeInfo(_identifier, _type)))
	{
		// We failed at creating the dependency
		return;
	}

	// Prepare the child info
	NodeInfo childInfo;
	childInfo.uniqueIdentifier = _identifier;
	childInfo.type = _type;

	// Add the child
	m_ChildrenInfo.push_back(childInfo);

	// Prepare the parent info
	NodeInfo parentInfo;
	parentInfo.uniqueIdentifier = GetUniqueIdentifier();
	parentInfo.type = GetType();

	// Set the parent for the child node
	childNode->SetParent(parentInfo);
}

void Flux::FluxNode::SetParent(NodeInfo _parent)
{
	// Create the dependency
	if (!CreateDependencyFromUsToNodeInfo(Flux::FluxNode::NodeInfo(_parent.uniqueIdentifier, _parent.type)))
	{
		// We failed at creating the dependency
		return;
	}

	// Set the parent
	m_ParentInfo = _parent;
}