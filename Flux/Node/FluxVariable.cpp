////////////////////////////////////////////////////////////////////////////////
// Filename: FluxVariable.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxVariable.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxVariable::FluxVariable(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Function))
{
	// Set the initial data
	// ...
}

Flux::FluxVariable::~FluxVariable()
{
}

void Flux::FluxVariable::SetVariableType(FluxUniqueIdentifier _classIdentifier)
{
	// Get the dependency manager instance
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_classIdentifier))
	{
		// Invalid identifier
		return;
	}

	// Check if we should remove an old relation
	if (m_VariableType.Initialized())
	{
		// Remove this relation
		dependencyManagerInstance->RemoveDependencyRelation(GetUniqueIdentifier(), m_VariableType, FluxDependencyRelationType::SrcDependsOnDst);
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Set the variable type
	m_VariableType = _classIdentifier;

	// Notify all dependencies (signature changed)
	dependencyManagerInstance->NotifyDependencies(GetUniqueIdentifier(), FluxDependencyNotifyType::SignatureChanged);
}

Flux::FluxUniqueIdentifier Flux::FluxVariable::GetVariableType()
{
	return m_VariableType;
}