////////////////////////////////////////////////////////////////////////////////
// Filename: FluxUniqueIdentifierGenerator.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxUniqueIdentifierGenerator.h"
#include <iostream>
#include <fstream>

Flux::FluxUniqueIdentifierGenerator::FluxUniqueIdentifierGenerator()
{
	// Set the initial data
	m_UniqueIdentifier = 0;

	// Try to load the last used identifier
	Load();
}

Flux::FluxUniqueIdentifierGenerator::FluxUniqueIdentifierGenerator(const Flux::FluxUniqueIdentifierGenerator& other)
{
}

Flux::FluxUniqueIdentifierGenerator::~FluxUniqueIdentifierGenerator()
{
	// Save the current identifier
	Save();
}

void Flux::FluxUniqueIdentifierGenerator::Load()
{
	std::ifstream  file;
	file.open("UniqueIdentifier.txt");

	// Check if the file is open
	if(file.is_open())
	{ 
		file >> m_UniqueIdentifier;
		file.close();
	}
}

void Flux::FluxUniqueIdentifierGenerator::Save()
{
	std::ofstream file;
	file.open("UniqueIdentifier.txt");
	file << m_UniqueIdentifier;
	file.close();
}

uint32_t Flux::FluxUniqueIdentifierGenerator::GetUniqueIdentifier()
{
	// Check if we should save our current identifier
	#ifdef FluxUniqueIdentifierAlwaysSave
		m_UniqueIdentifier++;
		Save();
		m_UniqueIdentifier--;
	#endif

	return ++m_UniqueIdentifier;
}