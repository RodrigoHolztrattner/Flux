////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependency.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxDependency.h"

Flux::FluxDependency::FluxDependency()
{

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