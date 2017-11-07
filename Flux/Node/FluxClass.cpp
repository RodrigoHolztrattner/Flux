////////////////////////////////////////////////////////////////////////////////
// Filename: FluxClass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxClass.h"

Flux::FluxClass::FluxClass()
{
	// Set the initial data
	// ...
}

Flux::FluxClass::FluxClass(const Flux::FluxClass& other)
{
}

Flux::FluxClass::~FluxClass()
{
}

void Flux::FluxClass::SetName(std::string _name)
{
	// Set the class name
	m_ClassName = _name;
}

// Add a member variable
void Flux::FluxClass::AddMemberVariable(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier)
{
	// Check if the identifier is valid
	if (!NodeFromIdentifierOfTypeExist(_identifier, Type::Variable))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	if (!CreateDependency(Flux::FluxNode::NodeInfo(_identifier, Type::Variable)))
	{
		// We failed at creating the dependency
		return;
	}

	// Setup the member variable
	FluxMemberVariable memberVariable;
	memberVariable.variableIdentifier = _identifier;
	memberVariable.variableAccessModifier = _accessModifier;
	memberVariable.internalIdentifier = 0; // TODO

	// Add the member variable
	m_MemberVariables.push_back(memberVariable);
}

void Flux::FluxClass::AddMemberFunction(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier)
{
	// Check if the identifier is valid
	if (!NodeFromIdentifierOfTypeExist(_identifier, Type::Function))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	if (!CreateDependency(Flux::FluxNode::NodeInfo(_identifier, Type::Function)))
	{
		// We failed at creating the dependency
		return;
	}

	// Setup the member function
	FluxMemberFunction memberFunction;
	memberFunction.functionIdentifier = _identifier;
	memberFunction.functionAccessModifier = _accessModifier;
	memberFunction.internalIdentifier = 0; // TODO

	// Add the member function
	m_MemberFunctions.push_back(memberFunction);
}