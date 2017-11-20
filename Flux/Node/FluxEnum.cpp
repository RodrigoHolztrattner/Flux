////////////////////////////////////////////////////////////////////////////////
// Filename: FluxEnum.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxEnum.h"
#include "Dependency\FluxDependencyManager.h"
#include "..\Project\FluxProject.h"

const char* Flux::FluxEnum::NodeTypeName = "Enum";

Flux::FluxEnum::FluxEnum()
{
}

Flux::FluxEnum::FluxEnum(FluxProject* _project) : FluxNode(_project, _project->GenerateUniqueIdentifier(Type::Enum))
{
	// Set the initial data
	// ...
}

Flux::FluxEnum::~FluxEnum()
{
}

void Flux::FluxEnum::AddParam(std::string _name)
{
	// Add the param
	AddParam(_name, GetValidDefaultValue());
}

void Flux::FluxEnum::AddParam(std::string _name, uint32_t _value)
{
	// Setup the param
	FluxEnumParam param;
	param.name = _name;
	param.useDefaultValues = true;
	param.internalIdentifier = GetUniqueInternalNumber();
	param.value = _value;

	// Add the param
	m_EnumParams.push_back(param);

	// Invalidate this node
	NeedVerification();
}

bool Flux::FluxEnum::RemoveParamWithIdentifier(uint32_t _paramInternalIdentifier)
{
	// Search the param
	for (unsigned int i = 0; i < m_EnumParams.size(); i++)
	{
		// Check the internal identifier
		if (m_EnumParams[i].internalIdentifier == _paramInternalIdentifier)
		{
			// Remove the param
			m_EnumParams.erase(m_EnumParams.begin() + i);

			// Invalidate this node
			NeedVerification();

			return true;
		}
	}

	return false;
}

bool Flux::FluxEnum::RemoveParamAtIndex(uint32_t _index)
{
	// Check if the index is valid
	if (_index < 0 || _index >= m_EnumParams.size())
	{
		return false;
	}

	return RemoveParamWithIdentifier(m_EnumParams[_index].internalIdentifier);
}

bool Flux::FluxEnum::RemoveParamWithName(std::string _name)
{
	// Search the param
	for (unsigned int i = 0; i < m_EnumParams.size(); i++)
	{
		// Check the name
		if (m_EnumParams[i].name.compare(_name) == 0)
		{
			// Remove the param
			m_EnumParams.erase(m_EnumParams.begin() + i);

			// Invalidate this node
			NeedVerification();

			return true;
		}
	}

	return false;
}

bool Flux::FluxEnum::Verify()
{
	// Check if we are already ok
	if (m_Verified)
	{
		return true;
	}

	// Call the base method
	return Flux::FluxNode::Verify();
}

void Flux::FluxEnum::Delete()
{
	// Call the base method
	Flux::FluxNode::Delete();
}

uint32_t Flux::FluxEnum::GetValidDefaultValue()
{
	return 0; // TODO
}

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxEnum& _node)
{
	const Flux::FluxNode& node = _node;

	_json = nlohmann::json
	{
		{ "FluxNode", node},
		{ "EnumParams", _node.m_EnumParams }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxEnum& _node)
{
	Flux::FluxNode& node = _node;

	node = _json.at("FluxNode").get<Flux::FluxNode>();
	_node.m_EnumParams = _json.at("EnumParams").get<std::vector<FluxEnumParam>>();
}

void Flux::to_json(nlohmann::json& _json, const Flux::FluxEnumParam& _object)
{
	_json = nlohmann::json
	{
		{ "ParamName", _object.name },
		{ "ParamUseDefaultValue", _object.useDefaultValues },
		{ "ParamValue", _object.value },
		{ "ParamInternalIdentifier", _object.internalIdentifier }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxEnumParam& _object)
{
	_object.name = _json.at("ParamName").get<std::string>();
	_object.useDefaultValues = _json.at("ParamUseDefaultValue").get<bool>();
	_object.value = _json.at("ParamValue").get<uint32_t>();
	_object.internalIdentifier = _json.at("ParamInternalIdentifier").get<uint32_t>();
	
}