////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNodeArchiver.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "..\FluxUniqueIdentifier.h"
#include "FluxNode.h"
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
	FluxNodeArchiver(std::string _jsonSaveName) { m_JsonSaveName = _jsonSaveName; }
	FluxNodeArchiver(const FluxNodeArchiver&) {}
	~FluxNodeArchiver() {}

public:

	// Insert a node
	void InsertNode(Flux::FluxNode& _node)
	{
		NodeType& node = (NodeType&)_node;
		m_Nodes.push_back(node);
	}

protected:

///////////////
// VARIABLES //
public: ///////
	
	// All nodes
	std::vector<NodeType> m_Nodes;

	// The json save name
	std::string m_JsonSaveName;
};

// Json functions
template <typename NodeType>
void to_json(nlohmann::json& _json, const Flux::FluxNodeArchiver<NodeType>& _node)
{
	_json = nlohmann::json
	{
		{ _node.m_JsonSaveName, _node.m_Nodes }
	};
}

template <typename NodeType>
void from_json(const nlohmann::json& _json, Flux::FluxNodeArchiver<NodeType>& _node)
{
	_node.m_Nodes = _json.at(_node.m_JsonSaveName).get<std::vector<NodeType>>();
}

// SmallPack
FluxNamespaceEnd(Flux)