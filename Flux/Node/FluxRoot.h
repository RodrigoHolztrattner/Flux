////////////////////////////////////////////////////////////////////////////////
// Filename: FluxRoot.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "FluxNode.h"
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
// Class name: FluxRoot
////////////////////////////////////////////////////////////////////////////////
class FluxRoot : public FluxNode
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxRoot& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxRoot& _node);

public:
	FluxRoot(FluxProject* _project);
	~FluxRoot();

public:

	// Connect a node
	void ConnectNode(FluxUniqueIdentifier _node);

///////////////
// VARIABLES //
private: //////

	// All connected nodes
	std::vector<FluxUniqueIdentifier> m_ConnectedNodes;
};

void Flux::to_json(nlohmann::json& _json, const Flux::FluxRoot& _node);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxRoot& _node);

// SmallPack
FluxNamespaceEnd(Flux)