////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunction.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunction.h"
#include "Holder\FluxHolder.h"
#include "Dependency\FluxDependencyManager.h"

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
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_variableIdentifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _variableIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Set the parent for the new variable
	fluxHolderInstance->GetNodeWithIdentifier(_variableIdentifier)->SetParent(GetUniqueIdentifier());

	// Add to the member array
	m_LocalVariables.push_back(_variableIdentifier);
}

void Flux::FluxFunction::AddInputParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_classIdentifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = GetUniqueInternalNumber();

	// Add the input param
	m_InputParams.push_back(param);
}

void Flux::FluxFunction::AddReturnParam(FluxUniqueIdentifier _classIdentifier, std::string _name)
{
	// Get the dependency manager and the holder instances
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Check if the identifier is valid
	if (!NodeFromIdentifierExist(_classIdentifier))
	{
		// Invalid identifier
		return;
	}

	// Create the dependency
	dependencyManagerInstance->AddDependencyRelation(GetUniqueIdentifier(), _classIdentifier, FluxDependencyRelationType::SrcDependsOnDst);

	// Setup the param
	FluxFunctionParam param;
	param.classIdentifier = _classIdentifier;
	param.name = _name;
	param.internalIdentifier = GetUniqueInternalNumber();

	// Add the return param
	m_ReturnParams.push_back(param);
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