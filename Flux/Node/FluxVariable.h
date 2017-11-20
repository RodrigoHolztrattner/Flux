////////////////////////////////////////////////////////////////////////////////
// Filename: FluxVariable.h
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

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxVariable
////////////////////////////////////////////////////////////////////////////////
class FluxVariable : public FluxNode
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxVariable& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxVariable& _node);

public:

	// The node name
	static const char* NodeTypeName;

public:
	FluxVariable();
	FluxVariable(FluxProject* _project);
	~FluxVariable();

public:

	// Set the variable type
	void SetVariableType(FluxUniqueIdentifier _classIdentifier);

	// Return the variable type
	FluxUniqueIdentifier GetVariableType(){ return m_VariableType; }

	// Verify this node
	virtual bool Verify();

	// Delete this node
	virtual void Delete();

///////////////
// VARIABLES //
private: //////

	// Our variable class type
	FluxUniqueIdentifier m_VariableType;
};

// Json functions
void Flux::to_json(nlohmann::json& _json, const Flux::FluxVariable& _node);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxVariable& _node);

// SmallPack
FluxNamespaceEnd(Flux)