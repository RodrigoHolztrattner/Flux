////////////////////////////////////////////////////////////////////////////////
// Filename: FluxRoot.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxRoot.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxRoot::FluxRoot(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Function))
{
	// Set the initial data
	// ...
}

Flux::FluxRoot::~FluxRoot()
{
}

void Flux::FluxRoot::ConnectNode(Flux::FluxUniqueIdentifier _node)
{

}

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxRoot& _node)
{
	const Flux::FluxNode& node = _node;

	_json = nlohmann::json
	{
		{ "FluxNode", node },
		{ "ConnectedNodes", _node.m_ConnectedNodes }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxRoot& _node)
{
	Flux::FluxNode& node = _node;

	node = _json.at("FluxNode").get<Flux::FluxNode>();
	_node.m_ConnectedNodes = _json.at("ConnectedNodes").get<std::vector<Flux::FluxUniqueIdentifier>>();
}