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
public:

public:
	FluxFunction(FluxProject* _project);
	~FluxFunction();

public:

	// Add a local variable
	void AddLocalVariable(FluxUniqueIdentifier _variableIdentifier);

	// Add an input param
	void AddInputParam(FluxUniqueIdentifier _classIdentifier, std::string _name);

	// Add a return param
	void AddReturnParam(FluxUniqueIdentifier _classIdentifier, std::string _name);

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

// SmallPack
FluxNamespaceEnd(Flux)