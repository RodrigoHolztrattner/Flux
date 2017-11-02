////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNodeHolder.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxNode.h"
#include <map>

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
// Class name: FluxNodeHolder
////////////////////////////////////////////////////////////////////////////////
class FluxNodeHolder
{
public:

public:
	FluxNodeHolder();
	FluxNodeHolder(const FluxNodeHolder&);
	~FluxNodeHolder();

public:

	// Return a object with the given identifier if it exist
	Flux::FluxNode* GetNodeWithIdentifier(FluxUniqueIdentifier _identifier)
	{
		// Check if the object exist
		if (m_Objects.find(_identifier) == m_Objects.end()) 
		{
			// Return a null ptr
			return nullptr;
		}
		else 
		{
			// Return the object
			return m_Objects[_identifier];
		}
	}

	// Insert a new object
	bool InsertNodeWithIdentifier(Flux::FluxNode* _node, FluxUniqueIdentifier _identifier)
	{
		// Check if the object exist
		if (m_Objects.find(_identifier) != m_Objects.end())
		{
			// Return false because we already have an object with the same identifier
			return false;
		}
		
		// Insert the object
		m_Objects[_identifier] = _node;

		return true;
	}

///////////////
// VARIABLES //
private: //////

	// All objects
	std::map<FluxUniqueIdentifier, Flux::FluxNode*> m_Objects;
};

// SmallPack
FluxNamespaceEnd(Flux)