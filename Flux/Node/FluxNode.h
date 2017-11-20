////////////////////////////////////////////////////////////////////////////////
// Filename: FluxNode.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "..\FluxUniqueIdentifier.h"
#include "..\Project\FluxProject.h"
#include "Dependency\FluxDependencyInterface.h"
#include "Dependency\FluxDependencyUtils.h"
#include "Holder\FluxHolderUtils.h"
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

// We know some classes
class FluxRoot;
class FluxClass;
class FluxFunction;
class FluxVariable;
class FluxEnum;
class FluxStructure;

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxNode
////////////////////////////////////////////////////////////////////////////////
class FluxNode : public FluxDependencyInterface, public FluxDependencyUtils, public FluxHolderUtils
{
	// We have some friends
	friend FluxRoot;
	friend FluxClass;
	friend FluxFunction;
	friend FluxVariable;
	friend FluxEnum;
	friend FluxStructure;

	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxNode& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxNode& _node);

public:
	FluxNode();
	FluxNode(FluxProject* _project, FluxUniqueIdentifier _uniqueIdentifier);
	~FluxNode();

	// Set the external name
	void SetExternalName(std::string _name) { m_ExternalName = _name; }

	// Set that this node need to be verfied
	void NeedVerification() { m_Verified = false; }

	// Return our unique identifier
	FluxUniqueIdentifier GetUniqueIdentifier() { return m_UniqueIdentifier; }

public: // Validation

	// Verify this node
	virtual bool Verify();

	// Delete this node
	virtual void Delete();

protected: // Parent

	// Set/invalidate our parent (never call those functions outside a node class, NEVER!)
	virtual void SetParent(FluxUniqueIdentifier _parent);
	virtual void SetParent(FluxNode* _parent) { SetParent(*_parent); }
	virtual void InvalidateParent();

	// Return a unique internal index number
	uint32_t GetUniqueInternalNumber() { return m_InternalIndexNumber++; }

public:

	// Conversion to the unique identifier type
	operator FluxUniqueIdentifier() const { return m_UniqueIdentifier; }

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