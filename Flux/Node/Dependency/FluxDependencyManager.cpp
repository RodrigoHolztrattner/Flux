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
		Flux::FluxDependency* newDependencyObject = new Flux::FluxDependency();

		// Insert it into our map
		m_DependencyObjects.insert(std::pair<FluxUniqueIdentifier, Flux::FluxDependency*>(_identifier, newDependencyObject));

		return newDependencyObject;
	}
	
	return nullptr;
}

bool Flux::FluxDependencyManager::CreateDependency(const Flux::FluxUniqueIdentifier& _sourceIdentifier, const Flux::FluxUniqueIdentifier& _destinationIdentifier)
{
	// Get the dependencies for the destination identifier
	Flux::FluxDependency* dependencies = GetIdentifierDependencies(_destinationIdentifier);
	if (dependencies == nullptr)
	{
		return false;
	}

	// Insert the dependency
	dependencies->InsertDependency(_sourceIdentifier);

	return true;
}