////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependency.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxDependency.h"
#include "..\FluxNode.h"
#include "..\Holder\FluxHolder.h"

Flux::FluxDependency::FluxDependency()
{
}

Flux::FluxDependency::FluxDependency(FluxUniqueIdentifier _ownerIdentifier)
{
	// Set the initial data
	m_OwnerIdentifier = _ownerIdentifier;
}

Flux::FluxDependency::~FluxDependency()
{
}

void Flux::FluxDependency::InsertDependency(FluxUniqueIdentifier& _identifier)
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

void Flux::FluxDependency::RemoveDependency(FluxUniqueIdentifier& _identifier)
{
	// Check if we already have a dependency for the given identifier
	auto it = m_Dependencies.find(_identifier);
	if (it != m_Dependencies.end())
	{
		// Increment the dependency count
		m_Dependencies[_identifier].totalDependencies--;

		// Check if we should delete the current dependency
		if (m_Dependencies[_identifier].totalDependencies == 0)
		{
			// Remove the current dependency set
			m_Dependencies.erase(it);
		}
	}
}

void Flux::FluxDependency::NotifyDependencies(FluxDependencyNotifyType _notifyType)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;
	
	// For each dependency
	for (std::map<Flux::FluxUniqueIdentifier, Flux::FluxDependency::DependencyType>::iterator it = m_Dependencies.begin(); it != m_Dependencies.end();)
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

Flux::FluxUniqueIdentifier Flux::FluxDependency::GetOwnerIdentifier()
{
	return m_OwnerIdentifier;
}

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxDependency& _object)
{
	// Insert each dependency from the map into our vector
	std::vector<Flux::FluxDependency::DependencyType> dependencies;
	for (std::map<Flux::FluxUniqueIdentifier, Flux::FluxDependency::DependencyType>::iterator it = const_cast<Flux::FluxDependency&>(_object).m_Dependencies.begin(); it != _object.m_Dependencies.end(); ++it)
	{
		// Insert it
		dependencies.push_back(it->second);
	}

	// Set the json
	_json = nlohmann::json
	{
		{ "OwnerIdentifier", _object.m_OwnerIdentifier },
		{ "Dependencies", dependencies }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxDependency& _object)
{
	std::vector<Flux::FluxDependency::DependencyType> dependencies;

	// Get the data from the json
	_object.m_OwnerIdentifier = _json.at("OwnerIdentifier").get<Flux::FluxUniqueIdentifier>();
	dependencies = _json.at("Dependencies").get<std::vector<Flux::FluxDependency::DependencyType>>();

	// Insert each dependency into the map
	for (auto& dependency : dependencies)
	{
		// Insert it
		_object.m_Dependencies.insert(std::pair<FluxUniqueIdentifier, Flux::FluxDependency::DependencyType>(dependency.uniqueIdentifier, dependency));
	}
}

void Flux::to_json(nlohmann::json& _json, const Flux::FluxDependency::DependencyType& _object)
{
	_json = nlohmann::json
	{
		{ "UniqueIdentifier", _object.uniqueIdentifier },
		{ "TotalDependencies", _object.totalDependencies }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxDependency::DependencyType& _object)
{
	_object.uniqueIdentifier = _json.at("UniqueIdentifier").get<Flux::FluxUniqueIdentifier>();
	_object.totalDependencies = _json.at("TotalDependencies").get<uint32_t>();
}