////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependencyManager.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxDependencyManager.h"

Flux::FluxDependencyManager::FluxDependencyManager()
{

}

Flux::FluxDependencyManager::FluxDependencyManager(const Flux::FluxDependencyManager& other)
{
}

Flux::FluxDependencyManager::~FluxDependencyManager()
{
}

void Flux::FluxDependencyManager::AddDependencyRelation(Flux::FluxUniqueIdentifier _sourceIdentifier, Flux::FluxUniqueIdentifier _destinationIdentifier, FluxDependencyRelationType _relation)
{
	// Check the relation type
	switch (_relation)
	{
		// SrcDependsOnDst
		case FluxDependencyRelationType::SrcDependsOnDst:
		{
			// Create the dependency
			CreateDependency(_sourceIdentifier, _destinationIdentifier);

			break;
		}

		// DstDependsOnSrc
		case FluxDependencyRelationType::DstDependsOnSrc:
		{
			// Create the dependency
			CreateDependency(_destinationIdentifier, _sourceIdentifier);

			break;
		}

		// BothDependsOnEachOther
		case FluxDependencyRelationType::BothDependsOnEachOther:
		{
			// Create the dependencies
			CreateDependency(_sourceIdentifier, _destinationIdentifier);
			CreateDependency(_destinationIdentifier, _sourceIdentifier);

			break;
		}
	}
}

void Flux::FluxDependencyManager::RemoveDependencyRelation(Flux::FluxUniqueIdentifier _sourceIdentifier, Flux::FluxUniqueIdentifier _destinationIdentifier, FluxDependencyRelationType _relation)
{
	// Check the relation type
	switch (_relation)
	{
		// SrcDependsOnDst
		case FluxDependencyRelationType::SrcDependsOnDst:
		{
			// Remove the dependency
			RemoveDependency(_sourceIdentifier, _destinationIdentifier);

			break;
		}

		// DstDependsOnSrc
		case FluxDependencyRelationType::DstDependsOnSrc:
		{
			// Remove the dependency
			RemoveDependency(_destinationIdentifier, _sourceIdentifier);

			break;
		}

		// BothDependsOnEachOther
		case FluxDependencyRelationType::BothDependsOnEachOther:
		{
			// Remove the dependencies
			RemoveDependency(_sourceIdentifier, _destinationIdentifier);
			RemoveDependency(_destinationIdentifier, _sourceIdentifier);

			break;
		}
	}
}

Flux::FluxDependency* Flux::FluxDependencyManager::GetIdentifierDependencies(const Flux::FluxUniqueIdentifier& _identifier, bool _create)
{
	// Check if we have a dependency object for the given identifier
	if (m_DependencyObjects.find(_identifier) != m_DependencyObjects.end())
	{
		// Return the dependency object
		return m_DependencyObjects[_identifier];
	}

	// Verify if we should create a dependency object
	if (_create)
	{
		// Create the new dependency object
		Flux::FluxDependency* newDependencyObject = new Flux::FluxDependency(_identifier);

		// Insert it into our map
		m_DependencyObjects.insert(std::pair<FluxUniqueIdentifier, Flux::FluxDependency*>(_identifier, newDependencyObject));

		return newDependencyObject;
	}
	
	return nullptr;
}

bool Flux::FluxDependencyManager::CreateDependency(Flux::FluxUniqueIdentifier& _sourceIdentifier, Flux::FluxUniqueIdentifier& _destinationIdentifier)
{
	// Get the dependencies for the destination identifier
	Flux::FluxDependency* dependencies = GetIdentifierDependencies(_destinationIdentifier, true);
	if (dependencies == nullptr)
	{
		return false;
	}

	// Insert the dependency
	dependencies->InsertDependency(_sourceIdentifier);

	return true;
}

bool Flux::FluxDependencyManager::RemoveDependency(Flux::FluxUniqueIdentifier& _sourceIdentifier, Flux::FluxUniqueIdentifier& _destinationIdentifier)
{
	// Get the dependencies for the destination identifier
	Flux::FluxDependency* dependencies = GetIdentifierDependencies(_destinationIdentifier);
	if (dependencies == nullptr)
	{
		return false;
	}

	// Insert the dependency
	dependencies->RemoveDependency(_sourceIdentifier);

	// Check if we have at last one dependency
	if (!dependencies->GetDependencyCount())
	{
		// Delete the dependency object
		delete dependencies;

		// Remove it from the map
		m_DependencyObjects.erase(m_DependencyObjects.find(_destinationIdentifier));
	}

	return true;
}

void Flux::FluxDependencyManager::NotifyDependencies(Flux::FluxUniqueIdentifier _identifier, FluxDependencyNotifyType _notifyType)
{
	// Get the dependencies for the identifier
	Flux::FluxDependency* dependencies = GetIdentifierDependencies(_identifier);
	if (dependencies == nullptr)
	{
		return;
	}

	// Notify the dependencies
	dependencies->NotifyDependencies(_notifyType);
}

bool Flux::FluxDependencyManager::IdentifierHaveDependencies(Flux::FluxUniqueIdentifier _identifier)
{
	Flux::FluxDependency* dependencies = GetIdentifierDependencies(_identifier);
	if (dependencies == nullptr)
	{
		return false;
	}

	return (dependencies->GetDependencyCount() > 0);
}

std::vector<Flux::FluxDependency> Flux::FluxDependencyManager::GetDependenciesFromProject(std::string _projectInternalName)
{
	std::vector<Flux::FluxDependency> outVector;

	// For each dependency object
	for (std::map<Flux::FluxUniqueIdentifier, Flux::FluxDependency*>::iterator it = m_DependencyObjects.begin(); it != m_DependencyObjects.end(); ++it)
	{
		// Get the dependency owner identifier
		Flux::FluxUniqueIdentifier dependencyIdentifier = it->second->GetOwnerIdentifier();

		// Compare the project names
		if (_projectInternalName.compare(dependencyIdentifier.GetInternalName()) == 0)
		{
			// Insert this dependency object
			outVector.push_back(*(it->second));
		}
	}

	return outVector;
}

void Flux::FluxDependencyManager::ConstructDependencies(std::vector<Flux::FluxDependency>& _dependencyVector)
{
	// For each dependency inside the vector
	for (auto& dependencyObject : _dependencyVector)
	{
		// Create the new dependency object
		Flux::FluxDependency* newDependencyObject = new Flux::FluxDependency();

		// Copy the data
		*newDependencyObject = dependencyObject;
		
		// Insert it into our map
		m_DependencyObjects.insert(std::pair<FluxUniqueIdentifier, Flux::FluxDependency*>(newDependencyObject->GetOwnerIdentifier(), newDependencyObject));
	}
}