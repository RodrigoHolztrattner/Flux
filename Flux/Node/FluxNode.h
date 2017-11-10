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

	// The node info type
	struct NodeInfo
	{
		// A null constructor
		NodeInfo() {}
		NodeInfo(FluxUniqueIdentifier _identifier) : uniqueIdentifier(_identifier) {}

		// The unique identifier
		FluxUniqueIdentifier uniqueIdentifier;
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

protected:

	// Check if a node from the given type exist
	bool NodeFromIdentifierOfTypeExist(FluxUniqueIdentifier _identifier);

	// Add a child node from the given identifier and type, also set the parent (we) and set the dependencies
	void AddChildAndSetParentForNode(FluxUniqueIdentifier _identifier);

private:

	// Set our parent
	void SetParent(NodeInfo _parent);

///////////////
// VARIABLES //
private: //////

	// Our unique identifier
	FluxUniqueIdentifier m_UniqueIdentifier;

	// Our generated name
	// std::string m_GeneratedName;

	// The parent node info
	NodeInfo m_ParentInfo;

	// All children node info
	std::vector<NodeInfo> m_ChildrenInfo;
};

// SmallPack
FluxNamespaceEnd(Flux)