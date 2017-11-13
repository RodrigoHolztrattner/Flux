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
public:

public:
	FluxClass(FluxProject* _project);
	~FluxClass();

public:

	// Add a member variable
	void AddMemberVariable(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier);

	// Add a member function
	void AddMemberFunction(FluxUniqueIdentifier _identifier, FluxAccessModifier _accessModifier);

///////////////
// VARIABLES //
private: //////

	// All member variables
	std::vector<FluxMemberVariable> m_MemberVariables;

	// All member functions
	std::vector<FluxMemberFunction> m_MemberFunctions;
};

// SmallPack
FluxNamespaceEnd(Flux)