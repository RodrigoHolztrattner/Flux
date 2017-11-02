////////////////////////////////////////////////////////////////////////////////
// Filename: FluxUniqueIdentifierGenerator.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "FluxConfig.h"
#include <cstdint>

/////////////
// DEFINES //
/////////////

// If we should save the identifier after altering it
#define FluxUniqueIdentifierAlwaysSave

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// SmallPack
FluxNamespaceBegin(Flux)

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxUniqueIdentifierGenerator
////////////////////////////////////////////////////////////////////////////////
class FluxUniqueIdentifierGenerator
{
public:
	FluxUniqueIdentifierGenerator();
	FluxUniqueIdentifierGenerator(const FluxUniqueIdentifierGenerator&);
	~FluxUniqueIdentifierGenerator();

	// Return a new unique identifier
	uint32_t GetUniqueIdentifier();

private:

	// Load the current identifier from the disk
	void Load();

	// Save the current identifier
	void Save();

///////////////
// VARIABLES //
private: //////

	// The unique identifier
	uint32_t m_UniqueIdentifier;
};

// SmallPack
FluxNamespaceEnd(Flux)