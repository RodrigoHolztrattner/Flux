////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionSourceNode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionSourceNode.h"

Flux::FluxFunctionSourceNode::FluxFunctionSourceNode()
{
	// Set the initial data
	// ...
}

Flux::FluxFunctionSourceNode::FluxFunctionSourceNode(const Flux::FluxFunctionSourceNode& other)
{
}

Flux::FluxFunctionSourceNode::~FluxFunctionSourceNode()
{
}

void Flux::FluxFunctionSourceNode::SetInternalIdentifier(FluxFunctionInternalIndexIdentifier _identifier)
{
	m_InternalIndexIdentifier = _identifier;
}

void Flux::FluxFunctionSourceNode::SetType(FluxFunctionSourceNodeType _type)
{
	m_NodeType = _type;
}

void Flux::FluxFunctionSourceNode::SetUniqueIdentifierReference(FluxUniqueIdentifier _uniqueIdentifier)
{
	m_IdentifierReference = _uniqueIdentifier;
}