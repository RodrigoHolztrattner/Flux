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
		Function,
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

	// Return our unique identifier
	FluxUniqueIdentifier GetUniqueIdentifier();

	// Return our type
	Type GetType();

protected:

	// Signal that this node depends on the given one, if the other node should be deleted or modified it 
	// should signal us about that
	bool CreateDependencyFromUsToNodeInfo(NodeInfo _nodeInfo);

	// Check if a node from the given type exist
	bool NodeFromIdentifierOfTypeExist(FluxUniqueIdentifier _identifier, Type _type);

	// Add a child node from the given identifier and type, also set the parent (we) and set the dependencies
	void AddChildAndSetParentForNode(FluxUniqueIdentifier _identifier, Type _type);

private:

	// Set our parent
	void SetParent(NodeInfo _parent);

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