////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunction.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunction.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxFunction::FluxFunction(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Function))
{
	// Set the initial data
	// ...
}

Flux::FluxFunction::~FluxFunction()
{
}

void Flux::FluxFunction::AddLocalVariable(FluxUniqueIdentifier _variableIdentifier)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_variableIdentifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _variableIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Set the parent for the new variable
	fluxHolderInstance->GetNodeWithIdentifier(_variableIdentifier)->SetParent(GetUniqueIdentifier());

	// Add to the member array
	m_LocalVariables.push_back(_variableIdentifier);
}

void Flux::FluxFunction::AddInputParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_classIdentifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = GetUniqueInternalNumber();

	// Add the input param
	m_InputParams.push_back(param);
}

void Flux::FluxFunction::AddReturnParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_classIdentifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = GetUniqueInternalNumber();

	// Add the return param
	m_ReturnParams.push_back(param);
}