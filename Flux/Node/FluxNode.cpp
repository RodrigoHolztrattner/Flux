////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxNode.h"
#include "..\FluxUniqueIdentifier.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"
#include <cassert>

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

bool Flux::FluxNode::NodeFromIdentifierExist(FluxUniqueIdentifier _identifier)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check if the identifier is valid
	if (!_identifier.Initialized())
	{
		return false;
	}

	// Check
	return fluxHolderInstance->NodeFromIdentifierExist(_identifier);
}

bool Flux::FluxNode::NodeFromIdentifierIsValidAndFromType(FluxUniqueIdentifier _identifier, Type _type, bool _verifyIfNecessary)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check if the identifier was initialized
	if (!_identifier.Initialized())
	{
		return false;
	}

	// Check if the node is from the given type
	if (_identifier.GetType() != _type)
	{
		return false;
	}

	// Check if the node exist
	Flux::FluxNode* node = fluxHolderInstance->GetNodeWithIdentifier(_identifier);
	if (node == nullptr)
	{
		return false;
	}

	// Check if the node is verified
	if (!node->IsVerified())
	{
		// Check if we should verify
		if (_verifyIfNecessary)
		{
			// Try to verify the node
			node->Verify();

			// Check again
			if (!node->IsVerified())
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Flux::FluxNode::Verify()
{
	// Check if our identifier is valid
	if (!m_UniqueIdentifier.Initialized())
	{
		return;
	}

	// Check if our parent identifier is valid
	if (!m_ParentNode.Initialized())
	{
		return;
	}

	// Set verified to true
	m_Verified = true;
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
	Invalidate();
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

////////////////
// DEPENDENCY //
////////////////

void Flux::FluxNode::AddDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the dst is valid
	if (_dst.Initialized())
	{
		// Create the dependency
		dependencyManagerInstance->AddDependencyRelation(*this, _dst, _relationType);
	}
}

void Flux::FluxNode::RemoveDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the dst is valid
	if (_dst.Initialized())
	{
		// Remove the dependency
		dependencyManagerInstance->RemoveDependencyRelation(*this, _dst, _relationType);
	}
}

void Flux::FluxNode::SwapDependencyRelation(FluxUniqueIdentifier& _old, FluxUniqueIdentifier& _newDst, FluxDependencyRelationType _relationType)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the old identifier is valid
	if (_old.Initialized())
	{
		// Remove the dependency
		dependencyManagerInstance->RemoveDependencyRelation(*this, _old, _relationType);

		// Invalidate the old identifier
		_old.Invalidate();
	}

	// Check if the dst is valid
	if (_newDst.Initialized())
	{
		// Create the dependency
		dependencyManagerInstance->AddDependencyRelation(*this, _newDst, _relationType);
	}
}

void Flux::FluxNode::NotifyDependencies(Flux::FluxDependencyNotifyType _notifyType)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Notify
	dependencyManagerInstance->NotifyDependencies(*this, _notifyType);
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