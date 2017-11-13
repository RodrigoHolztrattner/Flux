////////////////////////////////////////////////////////////////////////////////
// Filename: FluxClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxClass.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxClass::FluxClass(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Class))
{
	// Set the initial data
	// ...
}

Flux::FluxClass::~FluxClass()
{
}

void Flux::FluxClass::AddMemberVariable(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_identifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _identifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the member variable
	FluxMemberVariable memberVariable;
	memberVariable.variableIdentifier = _identifier;
	memberVariable.variableAccessModifier = _accessModifier;
	memberVariable.internalIdentifier = GetUniqueInternalNumber();

	// Set the parent for the new variable
	fluxHolderInstance->GetNodeWithIdentifier(_identifier)->SetParent(GetUniqueIdentifier());

	// Add the member variable
	m_MemberVariables.push_back(memberVariable);
}

void Flux::FluxClass::AddMemberFunction(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_identifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _identifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the member function
	FluxMemberFunction memberFunction;
	memberFunction.functionIdentifier = _identifier;
	memberFunction.functionAccessModifier = _accessModifier;
	memberFunction.internalIdentifier = GetUniqueInternalNumber();

	// Set the parent for the new variable
	fluxHolderInstance->GetNodeWithIdentifier(_identifier)->SetParent(GetUniqueIdentifier());

	// Add the member function
	m_MemberFunctions.push_back(memberFunction);
}