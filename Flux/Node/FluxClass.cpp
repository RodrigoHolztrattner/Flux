////////////////////////////////////////////////////////////////////////////////
// Filename: FluxClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxClass.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"
#include "..\Project\FluxProject.h"

const char* Flux::FluxClass::NodeTypeName = "Class";

Flux::FluxClass::FluxClass()
{
}

Flux::FluxClass::FluxClass(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Class))
{
	// Set the initial data
	// ...
}

Flux::FluxClass::~FluxClass()
{
}

uint32_t Flux::FluxClass::AddMemberVariable(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier)
{
	// Create the dependency
	AddDependencyRelation(_identifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the member variable
	FluxMemberVariable memberVariable;
	memberVariable.variableIdentifier = _identifier;
	memberVariable.variableAccessModifier = _accessModifier;
	memberVariable.internalIdentifier = GetUniqueInternalNumber();

	// Set the parent for the new variable
	_identifier->SetParent(*this);

	// Add the member variable
	m_MemberVariables.push_back(memberVariable);

	// Invalidate this node
	NeedVerification();

	return memberVariable.internalIdentifier;
}

bool Flux::FluxClass::RemoveMemberVariable(uint32_t _memberInternalIdentifier)
{
	// Search the member
	for (unsigned int i = 0; i < m_MemberVariables.size(); i++)
	{
		// Check the internal identifier
		if (m_MemberVariables[i].internalIdentifier == _memberInternalIdentifier)
		{
			// Remove the dependency
			RemoveDependencyRelation(m_MemberVariables[i].variableIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

			// Invalidate the member parent
			m_MemberVariables[i].variableIdentifier->InvalidateParent();

			// Remove the member
			m_MemberVariables.erase(m_MemberVariables.begin() + i);

			// Invalidate this node
			NeedVerification();

			return true;
		}
	}

	return false;
}

uint32_t Flux::FluxClass::AddMemberFunction(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier)
{
	// Create the dependency
	AddDependencyRelation(_identifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the member function
	FluxMemberFunction memberFunction;
	memberFunction.functionIdentifier = _identifier;
	memberFunction.functionAccessModifier = _accessModifier;
	memberFunction.internalIdentifier = GetUniqueInternalNumber();

	// Set the parent for the new variable
	_identifier->SetParent(*this);

	// Add the member function
	m_MemberFunctions.push_back(memberFunction);

	// Invalidate this node
	NeedVerification();

	return memberFunction.internalIdentifier;
}

bool Flux::FluxClass::RemoveMemberFunction(uint32_t _memberInternalIdentifier)
{
	// Search the member
	for (unsigned int i = 0; i < m_MemberFunctions.size(); i++)
	{
		// Check the internal identifier
		if (m_MemberFunctions[i].internalIdentifier == _memberInternalIdentifier)
		{
			// Remove the dependency
			RemoveDependencyRelation(m_MemberFunctions[i].functionIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

			// Invalidate the member parent
			m_MemberFunctions[i].functionIdentifier->InvalidateParent();

			// Remove the member
			m_MemberFunctions.erase(m_MemberFunctions.begin() + i);

			// Invalidate this node
			NeedVerification();

			return true;
		}
	}

	return false;
}

bool Flux::FluxClass::Verify()
{
	// Check if we are already ok
	if (m_Verified)
	{
		return true;
	}

	// For each member variable
	for (auto& memberVariable : m_MemberVariables)
	{
		// Check if this member variable exist
		if (!NodeFromIdentifierExist(memberVariable.variableIdentifier))
		{
			// Invalid node
			return false;
		}
	}

	// For each member function
	for (auto& memberFunction : m_MemberFunctions)
	{
		// Check if this member function exist
		if (!NodeFromIdentifierExist(memberFunction.functionIdentifier))
		{
			// Invalid node
			return false;
		}
	}

	// Call the base method
	return Flux::FluxNode::Verify();
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