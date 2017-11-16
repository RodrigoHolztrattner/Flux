////////////////////////////////////////////////////////////////////////////////
// Filename: FluxVariable.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxVariable.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxVariable::FluxVariable()
{
}

Flux::FluxVariable::FluxVariable(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Variable))
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

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxVariable& _node)
{
	const Flux::FluxNode& node = _node;

	_json = nlohmann::json
	{
		{ "FluxNode", node},
		{ "VariableTypeUniqueIdentifier", _node.m_VariableType}
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxVariable& _node)
{
	Flux::FluxNode& node = _node;

	node = _json.at("FluxNode").get<Flux::FluxNode>();
	_node.m_VariableType = _json.at("VariableTypeUniqueIdentifier").get<Flux::FluxUniqueIdentifier>();
}