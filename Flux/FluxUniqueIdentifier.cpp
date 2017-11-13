////////////////////////////////////////////////////////////////////////////////
// Filename: FluxUniqueIdentifier.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxUniqueIdentifier.h"
#include <iostream>
#include <fstream>

Flux::FluxUniqueIdentifier::FluxUniqueIdentifier()
{
	// Set the initial data
	m_Initialized = false;
}

Flux::FluxUniqueIdentifier::FluxUniqueIdentifier(const Flux::FluxUniqueIdentifier& _other)
{
	// Copy the data
	m_Initialized = _other.m_Initialized;
	m_ProjectName = _other.m_ProjectName;
	m_Identifier = _other.m_Identifier;
	m_Type = _other.m_Type;
	m_ProjectReference = _other.m_ProjectReference;
}

Flux::FluxUniqueIdentifier::~FluxUniqueIdentifier()
{
}

bool Flux::FluxUniqueIdentifier::Initialized()
{
	return m_Initialized;
}

void Flux::FluxUniqueIdentifier::Initialize(std::string _projectName, uint32_t _identifier, Type _type, Flux::FluxProject* _projectReference)
{
	// Set the data
	m_ProjectName = _projectName;
	m_Identifier = _identifier;
	m_Type = _type;
	m_ProjectReference = _projectReference;

	// Set initialized to true
	m_Initialized = true;
}