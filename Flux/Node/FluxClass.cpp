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

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxMemberVariable& _object)
{
	_json = nlohmann::json
	{
		{ "VariableUniqueIdentifier", _object.variableIdentifier },
		{ "VariableAccessModifier", _object.variableAccessModifier },
		{ "InternalIdentifierNumber", _object.internalIdentifier }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxMemberVariable& _object)
{
	_object.variableIdentifier = _json.at("VariableUniqueIdentifier").get<Flux::FluxUniqueIdentifier>();
	_object.variableAccessModifier = _json.at("VariableAccessModifier").get<FluxAccessModifier>();
	_object.internalIdentifier = _json.at("InternalIdentifierNumber").get<uint32_t>();
}

void Flux::to_json(nlohmann::json& _json, const Flux::FluxMemberFunction& _object)
{
	_json = nlohmann::json
	{
		{ "FunctionUniqueIdentifier", _object.functionIdentifier },
		{ "FunctionAccessModifier", _object.functionAccessModifier },
		{ "InternalIdentifierNumber", _object.internalIdentifier }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxMemberFunction& _object)
{
	_object.functionIdentifier = _json.at("FunctionUniqueIdentifier").get<Flux::FluxUniqueIdentifier>();
	_object.functionAccessModifier = _json.at("FunctionAccessModifier").get<FluxAccessModifier>();
	_object.internalIdentifier = _json.at("InternalIdentifierNumber").get<uint32_t>();
}

void Flux::to_json(nlohmann::json& _json, const Flux::FluxClass& _node)
{
	const Flux::FluxNode& node = _node;

	_json = nlohmann::json
	{
		{ "FluxNode", node },
		{ "MemberVariables", _node.m_MemberVariables },
		{ "MemberFunctions", _node.m_MemberFunctions }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxClass& _node)
{
	Flux::FluxNode& node = _node;

	node = _json.at("FluxNode").get<Flux::FluxNode>();
	_node.m_MemberVariables = _json.at("MemberVariables").get<std::vector<Flux::FluxMemberVariable>>();
	_node.m_MemberFunctions = _json.at("MemberFunctions").get<std::vector<Flux::FluxMemberFunction>>();
}