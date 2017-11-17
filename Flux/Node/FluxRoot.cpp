////////////////////////////////////////////////////////////////////////////////
// Filename: FluxRoot.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxRoot.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"
#include "..\Project\FluxProject.h"

const char* Flux::FluxRoot::NodeTypeName = "Root";

Flux::FluxRoot::FluxRoot()
{
	// Set the initial data
	// ...
}

Flux::FluxRoot::FluxRoot(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Root))
{
	// Set the initial data
	// ...
}

Flux::FluxRoot::~FluxRoot()
{
}

void Flux::FluxRoot::ConnectNode(Flux::FluxUniqueIdentifier _node)
{
	/*
	// Check if the type is valid
	if (_node.GetType() != Type::Namespace)
	{
		// Invalid type
		return;
	}
	*/

	// Create the dependency
	AddDependencyRelation(_node, FluxDependencyRelationType::BothDependsOnEachOther);

	// Set the parent for the node
	_node->SetParent(*this);

	// Add the node
	m_ConnectedNodes.push_back(_node);

	// Invalidate this node
	Invalidate();
}

void Flux::FluxRoot::DisconnectNode(FluxUniqueIdentifier _node)
{
	// Search for the node
	for (unsigned int i = 0; i < m_ConnectedNodes.size(); i++)
	{
		// Compare the identifiers
		if (m_ConnectedNodes[i] == _node)
		{
			// Remove the dependency
			RemoveDependencyRelation(_node, FluxDependencyRelationType::BothDependsOnEachOther);

			// Invalidate the parent
			_node->InvalidateParent();

			// Invalidate this node
			Invalidate();

			// Erase from the vector
			m_ConnectedNodes.erase(m_ConnectedNodes.begin() + i);

			return;
		}
	}
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