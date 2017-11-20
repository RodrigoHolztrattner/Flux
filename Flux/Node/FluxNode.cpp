////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxNode.h"
#include "..\FluxUniqueIdentifier.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"
#include <cassert>

Flux::FluxNode::FluxNode() : Flux::FluxDependencyUtils(this), Flux::FluxHolderUtils(this)
{
	FluxDependencyUtils::SetInternalPtr(this);
	FluxHolderUtils::SetInternalPtr(this);
}

Flux::FluxNode::FluxNode(FluxProject* _project, FluxUniqueIdentifier _uniqueIdentifier) : Flux::FluxDependencyUtils(this), Flux::FluxHolderUtils(this)
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

void Flux::FluxNode::Delete()
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Notify all dependencies of this
	// dependencyManagerInstance->NotifyDependencies(GetUniqueIdentifier(), FluxDependencyNotifyType::OriginDeleted);

	// Remove this current node from the holder
	fluxHolderInstance->RemoveNodeWithIdentifier(GetUniqueIdentifier());

	// Check if we can safely delete this node
	assert(!dependencyManagerInstance->IdentifierHaveDependencies(GetUniqueIdentifier()));
	assert(!m_ParentNode.Initialized());
}

bool Flux::FluxNode::Verify()
{
	// Check if our identifier is valid
	if (!m_UniqueIdentifier.Initialized())
	{
		return false;
	}

	// Check if our parent identifier is valid
	if (!m_ParentNode.Initialized())
	{
		return false;
	}

	// Set verified to true
	m_Verified = true;

	return true;
}

////////////
// PARENT //
////////////

void Flux::FluxNode::SetParent(FluxUniqueIdentifier _parent)
{
	// Get the dependency manager instance
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if we should remove an old relation
	if (m_ParentNode.Initialized())
	{
		// Reset the member status
		m_MemberFromClass = false;

		// Remove this relation
		dependencyManagerInstance->RemoveDependencyRelation(GetUniqueIdentifier(), m_ParentNode, FluxDependencyRelationType::SrcDependsOnDst);
	}

	// Create the mutual dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _parent, FluxDependencyRelationType::SrcDependsOnDst);

	// Check if the parent is a class
	if (_parent.GetType() == Type::Class)
	{
		// Set that we are a member node
		m_MemberFromClass = true;
	}
	
	// Set the parent
	m_ParentNode = _parent;

	// Notify all dependencies (signature changed)
	dependencyManagerInstance->NotifyDependencies(GetUniqueIdentifier(), FluxDependencyNotifyType::SignatureChanged);

	// Invalidate us
	NeedVerification();
}

void Flux::FluxNode::InvalidateParent()
{
	// Get the dependency manager instance
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if we should remove an old relation
	if (m_ParentNode.Initialized())
	{
		// Remove this relation
		dependencyManagerInstance->RemoveDependencyRelation(GetUniqueIdentifier(), m_ParentNode, FluxDependencyRelationType::SrcDependsOnDst);
	}

	// Reset the member status
	m_MemberFromClass = false;
	
	// Invalidate the parent identifier
	m_ParentNode.Invalidate();
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

	_node.FluxDependencyUtils::SetInternalPtr(&_node);
	_node.FluxHolderUtils::SetInternalPtr(&_node);
}