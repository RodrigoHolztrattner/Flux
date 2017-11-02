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

bool Flux::FluxNode::CreateDependency(NodeInfo _nodeInfo)
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