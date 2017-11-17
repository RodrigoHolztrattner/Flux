////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunction.h
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

// The function param type
struct FluxFunctionParam // O tipo sempre vai ser classe
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxFunctionParam& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxFunctionParam& _node);

	// The class identifier
	FluxUniqueIdentifier classIdentifier;

	// The name
	std::string name;

	// The param internal identifier
	uint32_t internalIdentifier;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxFunction
////////////////////////////////////////////////////////////////////////////////
class FluxFunction : public FluxNode
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxFunction& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxFunction& _node);

public:

	// The node name
	static const char* NodeTypeName;

public:
	FluxFunction();
	FluxFunction(FluxProject* _project);
	~FluxFunction();

public:

	// Add/remove a local variable
	void AddLocalVariable(FluxUniqueIdentifier _variableIdentifier);
	bool RemoveLocalVariable(FluxUniqueIdentifier _variableIdentifier);

	// Add/remove an input param
	void AddInputParam(FluxUniqueIdentifier _classIdentifier, std::string _name);
	bool RemoveInputParam(uint32_t _paramInternalIdentifier);

	// Add/remove a return param
	void AddReturnParam(FluxUniqueIdentifier _classIdentifier, std::string _name);
	bool RemoveReturnParam(uint32_t _paramInternalIdentifier);

	// Verify this node
	virtual void Verify();

///////////////
// VARIABLES //
private: //////

	// All the local variables
	std::vector<FluxUniqueIdentifier> m_LocalVariables;

	// All input params
	std::vector<FluxFunctionParam> m_InputParams;

	// All return params
	std::vector<FluxFunctionParam> m_ReturnParams;
};

// Json functions
void Flux::to_json(nlohmann::json& _json, const Flux::FluxFunctionParam& _funcParam);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxFunctionParam& _funcParam);

void Flux::to_json(nlohmann::json& _json, const Flux::FluxFunction& _node);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxFunction& _node);

// SmallPack
FluxNamespaceEnd(Flux)