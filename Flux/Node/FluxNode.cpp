////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxNode.h"
#include "..\FluxUniqueIdentifier.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"

Flux::FluxNode::FluxNode()
{
	// Get the unique identifier object instance
	// Flux::GlobalInstance<Flux::FluxUniqueIdentifier> g_UniqueIdentifierInstance;

	// Get a unique identifier
	// m_UniqueIdentifier = g_UniqueIdentifierInstance->GetUniqueIdentifier();

	// Set the initial data
	// ...
}

Flux::FluxNode::FluxNode(const Flux::FluxNode& other)
{
}

Flux::FluxNode::~FluxNode()
{
}

Flux::FluxUniqueIdentifier Flux::FluxNode::GetUniqueIdentifier()
{
	return m_UniqueIdentifier;
}

bool Flux::FluxNode::NodeFromIdentifierOfTypeExist(FluxUniqueIdentifier _identifier)
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Set the node info
	NodeInfo nodeInfo;
	nodeInfo.uniqueIdentifier = _identifier;

	// Check
	return fluxHolderInstance->NodeFromInfoExist(nodeInfo);
}

void Flux::FluxNode::AddChildAndSetParentForNode(FluxUniqueIdentifier _identifier)
{
	// Get the global holder instance and the dependency manager one
	Flux::GlobalInstance<Flux::FluxHolder> holderInstance;
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Get the node
	Flux::FluxNode* childNode = holderInstance->GetNodeWithIdentifier(_identifier);
	if (childNode == nullptr)
	{
		// Invalid node
		return;
	}

	// Create the mutual dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _identifier, FluxDependencyRelationType::BothDependsOnEachOther);

	isso de parent e filho precisa ver se esta certo
		tem que ver o que um nodo pode ter como filho
		e SE ele deve ter filho ou deve buscar na array global

		preciso ver como funciona a parte de notify nas dependencies e quando devemos deletar uma

	// Prepare the child info
	NodeInfo childInfo;
	childInfo.uniqueIdentifier = _identifier;

	// Add the child
	m_ChildrenInfo.push_back(childInfo);

	// Prepare the parent info
	NodeInfo parentInfo;
	parentInfo.uniqueIdentifier = GetUniqueIdentifier();

	// Set the parent for the child node
	childNode->SetParent(parentInfo);
}

void Flux::FluxNode::SetParent(NodeInfo _parent)
{
	// Set the parent
	m_ParentInfo = _parent;
}