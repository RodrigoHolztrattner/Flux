////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxNode.h"
#include "..\FluxUniqueIdentifier.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxNode::FluxNode()
{
}

Flux::FluxNode::FluxNode(FluxProject* _project, FluxUniqueIdentifier _uniqueIdentifier)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Set the initial data
	m_UniqueIdentifier = _uniqueIdentifier;
	m_Verified = false;
	m_MemberFromClass = false;
	m_ExternalName = "dummy";
	m_InternalIndexNumber = 0;

	// Add this node
	fluxHolderInstance->InsertNodeWithIdentifier(this, _uniqueIdentifier);
}

Flux::FluxNode::~FluxNode()
{
}

void Flux::FluxNode::SetExternalName(std::string _name)
{
	// Set the external name
	m_ExternalName = _name;
}

Flux::FluxUniqueIdentifier Flux::FluxNode::GetUniqueIdentifier()
{
	return m_UniqueIdentifier;
}

bool Flux::FluxNode::NodeFromIdentifierExist(FluxUniqueIdentifier _identifier)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check
	return fluxHolderInstance->NodeFromIdentifierExist(_identifier);
}

void Flux::FluxNode::SetParent(FluxUniqueIdentifier _parent)
{
	// Get the dependency manager instance
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if we should remove an old relation
	if (m_ParentNode.Initialized())
	{
		// Remove this relation
		dependencyManagerInstance->RemoveDependencyRelation(GetUniqueIdentifier(), m_ParentNode, FluxDependencyRelationType::SrcDependsOnDst);
	}

	// Create the mutual dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _parent, FluxDependencyRelationType::SrcDependsOnDst);

	// Check if the parent is a class
	// If true, set that we are a member TODO
	
	// Set the parent
	m_ParentNode = _parent;

	// Notify all dependencies (signature changed)
	dependencyManagerInstance->NotifyDependencies(GetUniqueIdentifier(), FluxDependencyNotifyType::SignatureChanged);
}

bool Flux::FluxNode::IsVerified()
{
	return m_Verified;
}

void Flux::FluxNode::Invalidate()
{
	m_Verified = false;
}

uint32_t Flux::FluxNode::GetUniqueInternalNumber()
{
	return m_InternalIndexNumber++;
}

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxNode& _node)
{
	_json = nlohmann::json
	{
		{ "UniqueIdentifier", _node.m_UniqueIdentifier },
		{ "ExternalName", _node.m_ExternalName },
		{ "ParentUniqueIdentifier", _node.m_ParentNode },
		{ "Verified", _node.m_Verified },
		{ "IsMember", _node.m_MemberFromClass },
		{ "InternalIndexNumber", _node.m_InternalIndexNumber }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxNode& _node)
{
	_node.m_UniqueIdentifier		= _json.at("UniqueIdentifier").get<Flux::FluxUniqueIdentifier>();
	_node.m_ExternalName			= _json.at("ExternalName").get<std::string>();
	_node.m_ParentNode				= _json.at("ParentUniqueIdentifier").get<Flux::FluxUniqueIdentifier>();
	_node.m_Verified				= _json.at("Verified").get<bool>();
	_node.m_MemberFromClass			= _json.at("IsMember").get<bool>();
	_node.m_InternalIndexNumber		= _json.at("InternalIndexNumber").get<uint32_t>();
}