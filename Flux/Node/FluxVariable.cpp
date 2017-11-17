////////////////////////////////////////////////////////////////////////////////
// Filename: FluxVariable.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxVariable.h"
#include "Dependency\FluxDependencyManager.h"
#include "..\Project\FluxProject.h"

const char* Flux::FluxVariable::NodeTypeName = "Variable";

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
	// Swap the dependency relation with the new one
	SwapDependencyRelation(m_VariableType, _classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Set the variable type
	m_VariableType = _classIdentifier;

	// Notify all dependencies (signature changed)
	NotifyDependencies(FluxDependencyNotifyType::SignatureChanged);

	// Invalidate this node
	Invalidate();
}

void Flux::FluxVariable::Verify()
{
	// Check if our type identifier exist
	if (!NodeFromIdentifierExist(m_VariableType))
	{
		// Invalid identifier
		m_VariableType.Invalidate();

		return;
	}

	// Call the base method
	Flux::FluxNode::Verify();
}

void Flux::FluxVariable::Delete()
{
	// Remove the old type relation if it exist
	RemoveDependencyRelation(m_VariableType, FluxDependencyRelationType::SrcDependsOnDst);

	// Call the base method
	Flux::FluxNode::Delete();
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