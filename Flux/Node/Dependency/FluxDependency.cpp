////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependency.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxDependency.h"
#include "..\Holder\FluxHolder.h"

Flux::FluxDependency::FluxDependency(FluxUniqueIdentifier _ownerIdentifier)
{
	// Set the initial data
	m_OwnerIdentifier = _ownerIdentifier;
}

Flux::FluxDependency::FluxDependency(const Flux::FluxDependency& other)
{
}

Flux::FluxDependency::~FluxDependency()
{
}

void Flux::FluxDependency::InsertDependency(const FluxUniqueIdentifier& _identifier)
{
	// Check if we already have a dependency for the given identifier
	if (m_Dependencies.find(_identifier) != m_Dependencies.end())
	{
		// Increment the dependency count
		m_Dependencies[_identifier].totalDependencies++;
	}
	else
	{
		// Insert a new dependency
		m_Dependencies.insert(std::pair<FluxUniqueIdentifier, DependencyType>(_identifier, DependencyType(_identifier)));
	}
}

void Flux::FluxDependency::RemoveDependency(const FluxUniqueIdentifier& _identifier)
{
	// TODO
}

void Flux::FluxDependency::NotifyDependencies(FluxDependencyNotifyType _notifyType)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// For each dependency
	for (std::map<Flux::FluxUniqueIdentifier, DependencyType>::iterator it = m_Dependencies.begin(); it != m_Dependencies.end();)
	{
		// Get the node from the current identifier
		Flux::FluxNode* currentNode = fluxHolderInstance->GetNodeWithIdentifier(it->second.uniqueIdentifier);
		
		// Notify the current node
		currentNode->NotificationFromDependency(m_OwnerIdentifier, _notifyType);

		// Check if the notification is the deletion one
		bool incrementIterator = true;
		if (_notifyType == FluxDependencyNotifyType::OriginDeleted)
		{
			// Remove one from the total dependencies
			it->second.totalDependencies--;

			// Check if we should remove the current dependency
			if (!it->second.totalDependencies)
			{
				// Remove the current dependency
				it = m_Dependencies.erase(it);

				// Set the we shouldn't increment the iterator
				incrementIterator = false;
			}
		}

		// If we need to increment the iterator
		if (incrementIterator)
		{
			++it;
		}
	}
}