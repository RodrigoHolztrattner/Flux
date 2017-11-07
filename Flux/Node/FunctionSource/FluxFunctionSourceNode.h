////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionSourceNode.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxFunction.h"

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// SmallPack
FluxNamespaceBegin(Flux)

// We know the FluxFunctionSource class
class FluxFunctionSource;

// The source node type
enum class FluxFunctionSourceNodeType
{
	Variable,
	Function,
	ControlMethod,
	BeginSourceNode,
	EndSourceNode
};

// The internal index identifier
typedef uint32_t FluxFunctionInternalIndexIdentifier;

// The source link
struct FluxFunctionSourceLink
{
	// The source index identifier
	// This index is used to retrieve the node from the FunctionSource class, if there is no node with the given identifier we can consider this link inexistent
	FluxFunctionInternalIndexIdentifier sourceNodeIndexIdentifier;

	// The link index
	// In case the source node is a function this will reference the "internalIdentifier" for the output param
	uint32_t linkIndex;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxFunctionSourceNode
////////////////////////////////////////////////////////////////////////////////
class FluxFunctionSourceNode
{
protected:

	// The FluxFunctionSource is a friend
	friend FluxFunctionSource;

public:
	FluxFunctionSourceNode();
	FluxFunctionSourceNode(const FluxFunctionSourceNode&);
	~FluxFunctionSourceNode();

public:

	// Compare operator
	bool operator <(const FluxFunctionSourceNode& rhs) const
	{
		return m_InternalIndexIdentifier < rhs.m_InternalIndexIdentifier;
	}

protected:

	// Set the internal index identifier
	void SetInternalIdentifier(FluxFunctionInternalIndexIdentifier _identifier);

	// Set the type
	void SetType(FluxFunctionSourceNodeType _type);

	// Set the unique identifier reference
	void SetUniqueIdentifierReference(FluxUniqueIdentifier _uniqueIdentifier);

///////////////
// VARIABLES //
private: //////

	// The source node type
	FluxFunctionSourceNodeType m_NodeType;

	// The unique identifier reference
	FluxUniqueIdentifier m_IdentifierReference;

	// Our internal index identifier 
	FluxFunctionInternalIndexIdentifier m_InternalIndexIdentifier;

	// All exec inputs
	std::vector<FluxFunctionSourceLink> m_ExecInputs;

	// The exec output
	FluxFunctionSourceLink m_ExecOutput;

	// All data inputs
	std::vector<FluxFunctionSourceLink> m_DataInputs;

	// All data outputs
	std::vector<FluxFunctionSourceLink> m_DataOutputs;
};

// SmallPack
FluxNamespaceEnd(Flux)