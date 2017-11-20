////////////////////////////////////////////////////////////////////////////////
// Filename: FluxClass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "FluxNode.h"
#include <vector>
#include <string>

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

// All the access modifiers
enum class FluxAccessModifier
{
	Public,
	Protected,
	Private
};

// The member variable type
struct FluxMemberVariable
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxMemberVariable& _object);
	friend void from_json(const nlohmann::json& _json, Flux::FluxMemberVariable& _object);

	// The variable identifier
	FluxUniqueIdentifier variableIdentifier;

	// The access modifier
	FluxAccessModifier variableAccessModifier;

	// The internal identifier
	uint32_t internalIdentifier;
};

// The member function type
struct FluxMemberFunction
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxMemberFunction& _object);
	friend void from_json(const nlohmann::json& _json, Flux::FluxMemberFunction& _object);

	// The function identifier
	FluxUniqueIdentifier functionIdentifier;

	// The access modifier
	FluxAccessModifier functionAccessModifier;

	// The internal identifier
	uint32_t internalIdentifier;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxClass
////////////////////////////////////////////////////////////////////////////////
class FluxClass : public FluxNode
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxClass& _object);
	friend void from_json(const nlohmann::json& _json, Flux::FluxClass& _object);

public:

	// The node name
	static const char* NodeTypeName;

public:
	FluxClass();
	FluxClass(FluxProject* _project);
	~FluxClass();

public:

	// Add/remove a member variable
	uint32_t AddMemberVariable(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier);
	bool RemoveMemberVariable(uint32_t _memberInternalIdentifier);

	// Add/remove a member function
	uint32_t AddMemberFunction(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier);
	bool RemoveMemberFunction(uint32_t _memberInternalIdentifier);

	// Verify this node
	virtual bool Verify();

///////////////
// VARIABLES //
private: //////

	// All member variables
	std::vector<FluxMemberVariable> m_MemberVariables;

	// All member functions
	std::vector<FluxMemberFunction> m_MemberFunctions;
};

// Json functions
void Flux::to_json(nlohmann::json& _json, const Flux::FluxMemberVariable& _object);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxMemberVariable& _object);

void Flux::to_json(nlohmann::json& _json, const Flux::FluxMemberFunction& _object);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxMemberFunction& _object);

void Flux::to_json(nlohmann::json& _json, const Flux::FluxClass& _object);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxClass& _object);

// SmallPack
FluxNamespaceEnd(Flux)