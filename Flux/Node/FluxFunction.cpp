////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunction.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunction.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"
#include "..\Project\FluxProject.h"

const char* Flux::FluxFunction::NodeTypeName = "Function";

Flux::FluxFunction::FluxFunction()
{
}

Flux::FluxFunction::FluxFunction(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Function))
{
	// Set the initial data
	// ...
}

Flux::FluxFunction::~FluxFunction()
{
}

void Flux::FluxFunction::AddLocalVariable(FluxUniqueIdentifier _variableIdentifier)
{
	// Create the dependency
	AddDependencyRelation(_variableIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Set the parent for the new variable
	_variableIdentifier->SetParent(this);

	// Add to the member array
	m_LocalVariables.push_back(_variableIdentifier);

	// Invalidate this node
	NeedVerification();
}

bool Flux::FluxFunction::RemoveLocalVariable(FluxUniqueIdentifier _variableIdentifier)
{
	// Search the local variable
	for (unsigned int i=0; i<m_LocalVariables.size(); i++)
	{
		// Compare the identifiers
		if (m_LocalVariables[i] == _variableIdentifier)
		{
			// Remove the dependency
			RemoveDependencyRelation(_variableIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

			// Set the parent for the new variable
			_variableIdentifier->InvalidateParent();

			// Remove the variable
			m_LocalVariables.erase(m_LocalVariables.begin() + i);

			// Invalidate this node
			NeedVerification();

			return true;
		}
	}

	return false;
}

void Flux::FluxFunction::AddInputParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Create the dependency
	AddDependencyRelation(_classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = GetUniqueInternalNumber();

	// Add the input param
	m_InputParams.push_back(param);

	// Invalidate this node
	NeedVerification();
}

bool Flux::FluxFunction::RemoveInputParam(uint32_t _paramInternalIdentifier)
{
	// Search the param
	for (unsigned int i = 0; i < m_InputParams.size(); i++)
	{
		// Check the internal identifier
		if (m_InputParams[i].internalIdentifier == _paramInternalIdentifier)
		{
			// Remove the dependency
			RemoveDependencyRelation(m_InputParams[i].classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

			// Remove the param
			m_InputParams.erase(m_InputParams.begin() + i);

			// Invalidate this node
			NeedVerification();

			return true;
		}
	}

	return false;
}

void Flux::FluxFunction::AddReturnParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Create the dependency
	AddDependencyRelation(_classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = GetUniqueInternalNumber();

	// Add the return param
	m_ReturnParams.push_back(param);

	// Invalidate this node
	NeedVerification();
}

bool Flux::FluxFunction::RemoveReturnParam(uint32_t _paramInternalIdentifier)
{
	// Search the param
	for (unsigned int i = 0; i < m_ReturnParams.size(); i++)
	{
		// Check the internal identifier
		if (m_ReturnParams[i].internalIdentifier == _paramInternalIdentifier)
		{
			// Remove the dependency
			RemoveDependencyRelation(m_ReturnParams[i].classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

			// Remove the param
			m_ReturnParams.erase(m_ReturnParams.begin() + i);

			// Invalidate this node
			NeedVerification();

			return true;
		}
	}

	return false;
}

bool Flux::FluxFunction::Verify()
{
	// Check if we are already ok
	if (m_Verified)
	{
		return true;
	}

	// For each local variable
	for (auto& localVariable : m_LocalVariables)
	{
		// Check if this local variable exist
		if (!NodeFromIdentifierExist(localVariable))
		{
			// Invalid node
			return false;
		}
	}

	// For each input param
	for (auto& inputParam : m_InputParams)
	{
		// Check if this input param exist and if the type is valid
		if (!NodeFromIdentifierExist(inputParam.classIdentifier) || !NodeFromIdentifierIsValidAsType(inputParam.classIdentifier))
		{
			// Invalid node
			return false;
		}
	}

	// For each return param
	for (auto& returnParam : m_ReturnParams)
	{
		// Check if this return param exist and if the type is valid
		if (!NodeFromIdentifierExist(returnParam.classIdentifier) || !NodeFromIdentifierIsValidAsType(returnParam.classIdentifier))
		{
			// Invalid node
			return false;
		}
	}

	// Call the base method
	return Flux::FluxNode::Verify();
}

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxFunctionParam& _funcParam)
{
	_json = nlohmann::json
	{
		{ "ParamClassTypeIdentifier", _funcParam.classIdentifier },
		{ "ParamName", _funcParam.name },
		{ "ParamInternalIdentifier", _funcParam.internalIdentifier }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxFunctionParam& _funcParam)
{
	_funcParam.classIdentifier = _json.at("ParamClassTypeIdentifier").get<Flux::FluxUniqueIdentifier>();
	_funcParam.name = _json.at("ParamName").get<std::string>();
	_funcParam.internalIdentifier = _json.at("ParamInternalIdentifier").get<uint32_t>();
}

void Flux::to_json(nlohmann::json& _json, const Flux::FluxFunction& _node)
{
	const Flux::FluxNode& node = _node;

	_json = nlohmann::json
	{
		{ "FluxNode", node },
		{ "LocalVariables", _node.m_LocalVariables },
		{ "InputParams", _node.m_InputParams },
		{ "ReturnParams", _node.m_ReturnParams }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxFunction& _node)
{
	Flux::FluxNode& node = _node;

	node = _json.at("FluxNode").get<Flux::FluxNode>();
	_node.m_LocalVariables = _json.at("LocalVariables").get<std::vector<Flux::FluxUniqueIdentifier>>();
	_node.m_InputParams = _json.at("InputParams").get<std::vector<Flux::FluxFunctionParam>>();
	_node.m_ReturnParams = _json.at("ReturnParams").get<std::vector<Flux::FluxFunctionParam>>();
}