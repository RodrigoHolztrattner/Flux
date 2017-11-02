////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "..\FluxUniqueIdentifier.h"
#include <vector>
#include <string>

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

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxNode
////////////////////////////////////////////////////////////////////////////////
class FluxNode
{
public:

	// The node type
	enum class Type
	{
		Unknow,
		Class,
		Structure,
		Namespace,
		Variable,
		Project
	};

	// The node info type
	struct NodeInfo
	{
		// A null constructor
		NodeInfo() : type(Type::Unknow) {}
		NodeInfo(FluxUniqueIdentifier _identifier, Type _type) : uniqueIdentifier(_identifier), type(_type) {}

		// The unique identifier
		FluxUniqueIdentifier uniqueIdentifier;

		// The type
		Type type;
	};

	// The node dependency type
	struct NodeDependencyType
	{
		// The node info
		NodeInfo info;

		// The number of dependencies of this type
		uint32_t totalDependencies;
	};

public:
	FluxNode();
	FluxNode(const FluxNode&);
	~FluxNode();

public:

protected:

	// Signal that this node depends on the given one
	bool CreateDependency(NodeInfo _nodeInfo);

///////////////
// VARIABLES //
private: //////

	// The type
	Type m_Type;

	// Our unique identifier
	FluxUniqueIdentifier m_UniqueIdentifier;

	// Our generated name
	// std::string m_GeneratedName;

	// The parent node info
	NodeInfo m_ParentInfo;

	// All children node info
	std::vector<NodeInfo> m_ChildrenInfo;

	// All nodes that reference this one in some way
	std::vector<NodeDependencyType> m_ReferencedNodeInfo;
};

// SmallPack
FluxNamespaceEnd(Flux)