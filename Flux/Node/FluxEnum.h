////////////////////////////////////////////////////////////////////////////////
// Filename: FluxEnum.h
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

// The enum param type
struct FluxEnumParam // O tipo sempre vai ser classe
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxEnumParam& _object);
	friend void from_json(const nlohmann::json& _json, Flux::FluxEnumParam& _object);

	// The name
	std::string name;

	// True if we use default values for this param
	bool useDefaultValues;

	// The param integer value
	uint32_t value;

	// The internal identifier
	uint32_t internalIdentifier;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxEnum
////////////////////////////////////////////////////////////////////////////////
class FluxEnum : public FluxNode
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxEnum& _node);
	friend void from_json(const nlohmann::json& _json, Flux::FluxEnum& _node);

public:

	// The node name
	static const char* NodeTypeName;

public:
	FluxEnum();
	FluxEnum(FluxProject* _project);
	~FluxEnum();

public:

	// Add/remove an param
	void AddParam(std::string _name);
	void AddParam(std::string _name, uint32_t _value);
	bool RemoveParamWithIdentifier(uint32_t _paramInternalIdentifier);
	bool RemoveParamAtIndex(uint32_t _index);
	bool RemoveParamWithName(std::string _name);

	// Verify this node
	virtual bool Verify();

	// Delete this node
	virtual void Delete();

private:

	// Get a valid default value for a new param
	uint32_t GetValidDefaultValue();

///////////////
// VARIABLES //
private: //////

	// All params
	std::vector<FluxEnumParam> m_EnumParams;
};

// Json functions
void Flux::to_json(nlohmann::json& _json, const Flux::FluxEnum& _node);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxEnum& _node);
//
void Flux::to_json(nlohmann::json& _json, const Flux::FluxEnumParam& _object);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxEnumParam& _object);

// SmallPack
FluxNamespaceEnd(Flux)