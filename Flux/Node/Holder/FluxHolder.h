////////////////////////////////////////////////////////////////////////////////
// Filename: FluxHolder.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "FluxNodeHolder.h"
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
// Class name: FluxHolder
////////////////////////////////////////////////////////////////////////////////
class FluxHolder
{
public:

public:
	FluxHolder();
	FluxHolder(const FluxHolder&);
	~FluxHolder();

public:

	// Return a holder from the given type
	Flux::FluxNodeHolder* GetHolderFromType(Flux::FluxNode::Type _type);

	// Return a node from the given node info
	Flux::FluxNode* GetNodeFromInfo(Flux::FluxNode::NodeInfo _nodeInfo);

///////////////
// VARIABLES //
private: //////

	// All holders
	std::map<Flux::FluxNode::Type, Flux::FluxNodeHolder*> m_Holders;
};

// SmallPack
FluxNamespaceEnd(Flux)