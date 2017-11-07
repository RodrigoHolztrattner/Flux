////////////////////////////////////////////////////////////////////////////////
// Filename: FluxVariable.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxVariable.h"

Flux::FluxVariable::FluxVariable()
{
	// Set the initial data
	// ...
}

Flux::FluxVariable::FluxVariable(const Flux::FluxVariable& other)
{
}

Flux::FluxVariable::~FluxVariable()
{
}

void Flux::FluxVariable::SetName(std::string _name)
{
	// Set the variable name
	m_VariableName = _name;
}

void Flux::FluxVariable::SetClassIdentifier(FluxUniqueIdentifier _classIdentifier)
{
	// Check if the identifier is valid
	if (!NodeFromIdentifierOfTypeExist(_classIdentifier, Type::Class))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	if (!CreateDependency(Flux::FluxNode::NodeInfo(_classIdentifier, Flux::FluxNode::Type::Class)))
	{
		// We failed at creating the dependency
		return;
	}

	// Set the class identifier
	m_VariableClassIdentifier = _classIdentifier;
}