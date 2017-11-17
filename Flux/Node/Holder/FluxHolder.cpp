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

Flux::FluxNode* Flux::FluxHolder::GetNodeWithIdentifier(FluxUniqueIdentifier _identifier)
{
	// Check if the object exist
	if (m_Objects.find(_identifier) == m_Objects.end())
	{
		// Return a null ptr
		return nullptr;
	}
	else
	{
		// Return the object
		return m_Objects[_identifier];
	}
}

bool Flux::FluxHolder::InsertNodeWithIdentifier(Flux::FluxNode* _node, FluxUniqueIdentifier _identifier)
{
	// Check if the object exist
	if (m_Objects.find(_identifier) != m_Objects.end())
	{
		// Return false because we already have an object with the same identifier
		return false;
	}

	// Insert the object
	m_Objects[_identifier] = _node;

	return true;
}

bool Flux::FluxHolder::RemoveNodeWithIdentifier(FluxUniqueIdentifier _identifier)
{
	// Check if the object exist
	auto it = m_Objects.find(_identifier);
	if (it == m_Objects.end())
	{
		// Return false because we dont have an object with the same identifier
		return false;
	}

	// Remove the object
	m_Objects.erase(it);

	return true;
}

bool Flux::FluxHolder::NodeFromIdentifierExist(Flux::FluxUniqueIdentifier _identifier)
{
	// Check if the result node is valid
	if (GetNodeWithIdentifier(_identifier) == nullptr)
	{
		return false;
	}

	return true;
}

std::map<Flux::FluxUniqueIdentifier, Flux::FluxNode*>& Flux::FluxHolder::GetNodeObjects()
{
	return m_Objects;
}