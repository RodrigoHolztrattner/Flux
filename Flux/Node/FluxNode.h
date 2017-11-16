////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "..\FluxUniqueIdentifier.h"
#include "..\FluxProject.h"
#include "Dependency\FluxDependencyInterface.h"
#include <vector>
#include <string>
#include <json.hpp>

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
// Class name: FluxNode
////////////////////////////////////////////////////////////////////////////////
class FluxNode : public FluxDependencyInterface
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxNode& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxNode& _node);

public:
	FluxNode();
	FluxNode(FluxProject* _project, FluxUniqueIdentifier _uniqueIdentifier);
	~FluxNode();

	// Set the external name
	void SetExternalName(std::string _name);

	// Return our unique identifier
	FluxUniqueIdentifier GetUniqueIdentifier();

	// Return if this node 
	bool IsVerified();

	// Invalidade this node
	void Invalidate();

	// Set our parent
	virtual void SetParent(FluxUniqueIdentifier _parent);

	// Conversion to the unique identifier type
	operator FluxUniqueIdentifier() const { return m_UniqueIdentifier; }

protected:

	// Check if a node from the given identifier exist
	bool NodeFromIdentifierExist(FluxUniqueIdentifier _identifier);

	// Return a unique internal index number
	uint32_t GetUniqueInternalNumber();

///////////////
// VARIABLES //
private: //////

	// Our unique identifier
	FluxUniqueIdentifier m_UniqueIdentifier;

	// The external name
	std::string m_ExternalName;

	// The parent node
	FluxUniqueIdentifier m_ParentNode;

	// Our generated name
	// std::string m_GeneratedName;

	// If this node is verified
	bool m_Verified;

	// If this is a member node from a class (function, variable, etc)
	bool m_MemberFromClass;

	// Our internal current index number
	uint32_t m_InternalIndexNumber;
};

// Json functions
void Flux::to_json(nlohmann::json& _json, const Flux::FluxNode& _node);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxNode& _node);

// SmallPack
FluxNamespaceEnd(Flux)