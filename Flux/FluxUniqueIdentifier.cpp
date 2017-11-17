////////////////////////////////////////////////////////////////////////////////
// Filename: FluxUniqueIdentifier.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxUniqueIdentifier.h"
#include <iostream>
#include <fstream>
#include "Node\Holder\FluxHolder.h"

Flux::FluxUniqueIdentifier::FluxUniqueIdentifier()
{
	// Set the initial data
	m_Initialized = false;
	m_Identifier = -1;
	m_Type = Type::Unknow;
	// m_ProjectReference = nullptr;
}

Flux::FluxUniqueIdentifier::FluxUniqueIdentifier(const Flux::FluxUniqueIdentifier& _other)
{
	// Copy the data
	m_Initialized = _other.m_Initialized;
	m_ProjectName = _other.m_ProjectName;
	m_Identifier = _other.m_Identifier;
	m_Type = _other.m_Type;
	// m_ProjectReference = _other.m_ProjectReference;
}

Flux::FluxUniqueIdentifier::~FluxUniqueIdentifier()
{
}

void Flux::FluxUniqueIdentifier::Initialize(std::string _projectName, uint32_t _identifier, Type _type, Flux::FluxProject* _projectReference)
{
	// Set the data
	m_ProjectName = _projectName;
	m_Identifier = _identifier;
	m_Type = _type;
	// m_ProjectReference = _projectReference;

	// Set initialized to true
	m_Initialized = true;
}

std::string Flux::FluxUniqueIdentifier::GetInternalName()
{
	return m_ProjectName;
}

Flux::Type Flux::FluxUniqueIdentifier::GetType()
{
	return m_Type;
}

bool Flux::FluxUniqueIdentifier::IsFromProjectWithInternalName(std::string _projectName)
{
	return m_ProjectName.compare(_projectName) == 0;
}

bool Flux::FluxUniqueIdentifier::IsFromType(Flux::Type _type)
{
	return m_Type == _type;
}

bool Flux::FluxUniqueIdentifier::Initialized()
{
	return m_Initialized;
}

void Flux::FluxUniqueIdentifier::Invalidate()
{
	m_Initialized = false;
}

Flux::FluxNode* Flux::FluxUniqueIdentifier::operator ->() const
{
	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// Find the node
	return fluxHolderInstance->GetNodeWithIdentifier(*this);
}

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxUniqueIdentifier& _identifier)
{
	_json = nlohmann::json
	{
		{ "ProjectInternalName", _identifier.m_ProjectName },
		{ "Identifier", _identifier.m_Identifier },
		{ "Type", _identifier.m_Type }
	};
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxUniqueIdentifier& _identifier)
{
	_identifier.m_ProjectName = _json.at("ProjectInternalName").get<std::string>();
	_identifier.m_Identifier = _json.at("Identifier").get<uint32_t>();
	_identifier.m_Type = _json.at("Type").get<Flux::Type>();
	// _identifier.m_ProjectReference = nullptr;

	// Set initialized to true
	_identifier.m_Initialized = true;
}