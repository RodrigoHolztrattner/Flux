////////////////////////////////////////////////////////////////////////////////
// Filename: FluxUniqueIdentifier.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "FluxConfig.h"
#include "FluxProject.h"
#include <cstdint>
#include <string>
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
// Class name: FluxUniqueIdentifier
////////////////////////////////////////////////////////////////////////////////
class FluxUniqueIdentifier
{
public:
	FluxUniqueIdentifier();
	FluxUniqueIdentifier(const FluxUniqueIdentifier&);
	~FluxUniqueIdentifier();

	// If this unique identifier was initialized
	bool Initialized();

	// Compare operator
	bool operator <(const FluxUniqueIdentifier& rhs) const
	{
		return m_Identifier < rhs.m_Identifier; // Error!
	}

protected:

	// Initialize this unique identifier
	void Initialize(std::string _projectName, uint32_t _identifier, Flux::FluxProject* _projectReference);

///////////////
// VARIABLES //
private: //////

	// If this unique identifier was initialized
	bool m_Initialized;

	// The project name
	std::string m_ProjectName;

	// The identifier
	uint32_t m_Identifier;

	// The project reference
	Flux::FluxProject* m_ProjectReference;
};

// SmallPack
FluxNamespaceEnd(Flux)