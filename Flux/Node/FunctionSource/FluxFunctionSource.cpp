////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionSource.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionSource.h"

Flux::FluxFunctionSource::FluxFunctionSource()
{
	// Set the initial data
	m_InternalIndexIdentifierCount = 0;
}

Flux::FluxFunctionSource::FluxFunctionSource(const Flux::FluxFunctionSource& other)
{
}

Flux::FluxFunctionSource::~FluxFunctionSource()
{
}

Flux::FluxFunctionSourceNode* Flux::FluxFunctionSource::CreateSourceNode(FluxFunctionSourceNodeType _type, FluxUniqueIdentifier _identifier)
{
	// Check if the current identifier (with the given type) is valid and exist
	// ... TODO

	// Create the new source node
	FluxFunctionSourceNode* newSourceNode = new FluxFunctionSourceNode();

	// Set the source node data
	newSourceNode->SetType(_type);
	newSourceNode->SetUniqueIdentifierReference(_identifier);
	newSourceNode->SetInternalIdentifier(m_InternalIndexIdentifierCount);

	// Add a dependency for the unique identifier object
	// ... TODO
	
	// Insert our new source node into our vector
	m_SourceNodes.insert(std::pair<uint32_t, FluxFunctionSourceNode*>(m_InternalIndexIdentifierCount, newSourceNode));

	// Increment out internal index identifier
	m_InternalIndexIdentifierCount++;

	return newSourceNode;
}