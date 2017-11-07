////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunction.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunction.h"

Flux::FluxFunction::FluxFunction()
{
	// Set the initial data
	// ...
}

Flux::FluxFunction::FluxFunction(const Flux::FluxFunction& other)
{
}

Flux::FluxFunction::~FluxFunction()
{
}

void Flux::FluxFunction::SetName(std::string _name)
{
	// Set the function name
	m_FunctionName = _name;
}

void Flux::FluxFunction::AddInputParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Check if the identifier is valid
	if (!NodeFromIdentifierOfTypeExist(_classIdentifier, Type::Class))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	if (!CreateDependencyFromUsToNodeInfo(Flux::FluxNode::NodeInfo(_classIdentifier, Flux::FluxNode::Type::Class)))
	{
		// We failed at creating the dependency
		return;
	}

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = 0; // TODO

	// Add the input param
	m_InputParams.push_back(param);
}

void Flux::FluxFunction::AddReturnParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Check if the identifier is valid
	if (!NodeFromIdentifierOfTypeExist(_classIdentifier, Type::Class))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	if (!CreateDependencyFromUsToNodeInfo(Flux::FluxNode::NodeInfo(_classIdentifier, Flux::FluxNode::Type::Class)))
	{
		// We failed at creating the dependency
		return;
	}

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = 0; // TODO

	// Add the return param
	m_ReturnParams.push_back(param);
}