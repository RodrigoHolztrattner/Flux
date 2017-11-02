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

Flux::FluxUniqueIdentifier::FluxUniqueIdentifier(const Flux::FluxUniqueIdentifier& other)
{
}

Flux::FluxUniqueIdentifier::~FluxUniqueIdentifier()
{
}

bool Flux::FluxUniqueIdentifier::Initialized()
{
	return m_Initialized;
}

void Flux::FluxUniqueIdentifier::Initialize(std::string _projectName, uint32_t _identifier, Flux::FluxProject* _projectReference)
{
	// Set the data
	m_ProjectName = _projectName;
	m_Identifier = _identifier;
	m_ProjectReference = _projectReference;

	// Set initialized to true
	m_Initialized = true;
}