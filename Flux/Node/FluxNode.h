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

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxNode
////////////////////////////////////////////////////////////////////////////////
class FluxNode : public FluxDependencyInterface
{
	// We have some friends
	friend FluxRoot;
	friend FluxClass;
	friend FluxFunction;
	friend FluxVariable;

	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxNode& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxNode& _node);

public:
	FluxNode();
	FluxNode(FluxProject* _project, FluxUniqueIdentifier _uniqueIdentifier);
	~FluxNode();

	// Set the external name
	void SetExternalName(std::string _name) { m_ExternalName = _name; }

	// Return our unique identifier
	FluxUniqueIdentifier GetUniqueIdentifier() { return m_UniqueIdentifier; }

	// Delete this node
	virtual void Delete();

	// Conversion to the unique identifier type
	operator FluxUniqueIdentifier() const { return m_UniqueIdentifier; }

public: // Validation

	// Return if this node was verified
	bool IsVerified() { return m_Verified; }

	// Invalidade this node
	void Invalidate() { m_Verified = false; }

	// Verify this node
	virtual void Verify();

protected: // Parent

	// Set/invalidate our parent (never call those functions outside a node class, NEVER!)
	virtual void SetParent(FluxUniqueIdentifier _parent);
	virtual void SetParent(FluxNode* _parent) { SetParent(*_parent); }
	virtual void InvalidateParent();

protected: // Dependency

	// Add/remove/swap a dependency relation (those functions always verify if the src and dst are valid)
	void AddDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType);
	void RemoveDependencyRelation(FluxUniqueIdentifier& _dst, FluxDependencyRelationType _relationType);
	void SwapDependencyRelation(FluxUniqueIdentifier& _old, FluxUniqueIdentifier& _newDst, FluxDependencyRelationType _relationType);
	void NotifyDependencies(Flux::FluxDependencyNotifyType _notifyType);

protected: // Verification

	// Check if a node from the given identifier exist
	bool NodeFromIdentifierExist(FluxUniqueIdentifier _identifier);

	// Check if the given identifier was initialized, if it is valid and if it is from the given type
	bool NodeFromIdentifierIsValidAndFromType(FluxUniqueIdentifier _identifier, Type _type, bool _verifyIfNecessary = false);

	// Return a unique internal index number
	uint32_t GetUniqueInternalNumber(){ return m_InternalIndexNumber++; }

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