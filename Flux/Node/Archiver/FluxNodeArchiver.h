////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNodeArchiver.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\..\FluxUniqueIdentifier.h"
#include "..\FluxNode.h"
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
// Class name: FluxNodeArchiver
////////////////////////////////////////////////////////////////////////////////
template <typename NodeType>
class FluxNodeArchiver
{
	// Json friend functions
	// friend void to_json(nlohmann::json& _json, const Flux::FluxNodeArchiver<NodeType>& _node);
	// friend void from_json(const nlohmann::json& _json, Flux::FluxNodeArchiver<NodeType>& _node);

public:
	FluxNodeArchiver() {}
	~FluxNodeArchiver() {}

public:

	// Insert a node
	void InsertNode(Flux::FluxNode& _node)
	{
		NodeType& node = (NodeType&)_node;
		m_Nodes.push_back(node);
	}

	// Return a reference to all nodes
	void GetNodeVectorReference(std::vector<NodeType*>* _vectorPtr)
	{
		for (auto& node : m_Nodes)
		{
			NodeType* newNode = new NodeType();
			*newNode = node;
			_vectorPtr->push_back(newNode);
		}
	}

	// Return the size
	uint32_t size() { return m_Nodes.size(); }

protected:

///////////////
// VARIABLES //
public: ///////
	
	// All nodes
	std::vector<NodeType> m_Nodes;
};

// Json functions
template <typename NodeType>
void to_json(nlohmann::json& _json, const Flux::FluxNodeArchiver<NodeType>& _node)
{
	_json = nlohmann::json
	{
		{ NodeType::NodeTypeName, _node.m_Nodes }
	};
}

template <typename NodeType>
void from_json(const nlohmann::json& _json, Flux::FluxNodeArchiver<NodeType>& _node)
{
	_node.m_Nodes = _json.at(NodeType::NodeTypeName).get<std::vector<NodeType>>();
}

// SmallPack
FluxNamespaceEnd(Flux)