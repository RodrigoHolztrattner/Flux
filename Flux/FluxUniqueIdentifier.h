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

// The type
enum class Type
{
	Unknow		= 0,
	Class		= 1,
	Structure	= 2,
	Namespace	= 3,
	Variable	= 4,
	Function	= 5,
	Project		= 6
};

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
		int stringNameCompare = m_ProjectName.compare(rhs.m_ProjectName);

		if (stringNameCompare != 0)						// Check project name first
			return stringNameCompare;
		else if (m_Type != rhs.m_Type)					// Ok same project. Compare the type
			return m_Type < rhs.m_Type;
		else
			return m_Identifier < rhs.m_Identifier;		// Ok same project and type, compare the identifier
	}

protected:

	// Initialize this unique identifier
	void Initialize(std::string _projectName, uint32_t _identifier, Type _type, Flux::FluxProject* _projectReference);

///////////////
// VARIABLES //
private: //////

	// If this unique identifier was initialized
	bool m_Initialized;

	// The project name
	std::string m_ProjectName;

	// The identifier
	uint32_t m_Identifier;

	// The type
	Type m_Type;

	// The project reference
	Flux::FluxProject* m_ProjectReference;
};

// SmallPack
FluxNamespaceEnd(Flux)