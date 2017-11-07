////////////////////////////////////////////////////////////////////////////////
// Filename: FluxHolder.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxHolder.h"

Flux::FluxHolder::FluxHolder()
{
}

Flux::FluxHolder::FluxHolder(const Flux::FluxHolder& other)
{
}

Flux::FluxHolder::~FluxHolder()
{
}

Flux::FluxNodeHolder* Flux::FluxHolder::GetHolderFromType(Flux::FluxNode::Type _type)
{
	// Check if the object exist
	if (m_Holders.find(_type) == m_Holders.end())
	{
		// Return a null ptr
		return nullptr;
	}
	else
	{
		// Return the object
		return m_Holders[_type];
	}
}

Flux::FluxNode* Flux::FluxHolder::GetNodeFromInfo(Flux::FluxNode::NodeInfo _nodeInfo)
{
	// Get the holder from the info
	Flux::FluxNodeHolder* holder = GetHolderFromType(_nodeInfo.type);
	if (holder == nullptr)
	{
		// Invalid holder
		return nullptr;
	}

	// Return the node object from the holder
	return holder->GetNodeWithIdentifier(_nodeInfo.uniqueIdentifier);
}

bool  Flux::FluxHolder::NodeFromInfoExist(Flux::FluxNode::NodeInfo _nodeInfo)
{
	// Get the holder from the info
	Flux::FluxNodeHolder* holder = GetHolderFromType(_nodeInfo.type);
	if (holder == nullptr)
	{
		// Invalid holder
		return false;
	}

	// Check if the result node is valid
	if (holder->GetNodeWithIdentifier(_nodeInfo.uniqueIdentifier) == nullptr)
	{
		return false;
	}

	return true;
}