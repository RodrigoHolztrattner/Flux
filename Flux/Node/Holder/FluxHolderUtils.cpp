////////////////////////////////////////////////////////////////////////////////
// Filename: FluxHolderUtils.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxHolderUtils.h"
#include "..\..\FluxUniqueIdentifier.h"
#include "FluxHolder.h"

Flux::FluxHolderUtils::FluxHolderUtils(Flux::FluxNode* _internalPtr)
{
	// Set the initial data
	m_InternalPtr = _internalPtr;
}

Flux::FluxHolderUtils::~FluxHolderUtils()
{
}

bool Flux::FluxHolderUtils::NodeFromIdentifierExist(FluxUniqueIdentifier _identifier)
{
	// Correct the internal ptr
	m_InternalPtr = (Flux::FluxNode*)this;

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

bool Flux::FluxHolderUtils::NodeFromIdentifierIsValidAndFromType(FluxUniqueIdentifier _identifier, Type _type)
{
	// Correct the internal ptr
	m_InternalPtr = (Flux::FluxNode*)this;

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
	if (!node->Verify())
	{
		return false;
	}

	return true;
}

bool Flux::FluxHolderUtils::NodeFromIdentifierIsValidAsType(Flux::FluxUniqueIdentifier _identifier)
{
	// Correct the internal ptr
	m_InternalPtr = (Flux::FluxNode*)this;

	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check if the node exist
	Flux::FluxNode* node = fluxHolderInstance->GetNodeWithIdentifier(_identifier);
	if (node == nullptr)
	{
		return false;
	}

	// Get the type
	Flux::Type nodeType = _identifier.GetType();

	// Check the types
	if (nodeType == Type::Class || nodeType == Type::Enum || nodeType == Type::Structure)
	{
		return true;
	}

	return false;
}