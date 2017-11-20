////////////////////////////////////////////////////////////////////////////////
// Filename: FluxUniqueIdentifier.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "FluxConfig.h"
#include <json.hpp>
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

// We know the FluxProject and FluxNode classes
class FluxProject;
class FluxNode;

// The type
enum class Type
{
	Unknow		= 0,
	Class		= 1,
	Structure	= 2,
	Namespace	= 3,
	Variable	= 4,
	Function	= 5,
	Project		= 6,
	Root		= 7,
	Enum		= 8
};

//////////////////////
// JSON DECLARATION //
//////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxUniqueIdentifier
////////////////////////////////////////////////////////////////////////////////
class FluxUniqueIdentifier
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxUniqueIdentifier& _identifier);
	friend void from_json(const nlohmann::json& _json, Flux::FluxUniqueIdentifier& _identifier);

private:

	// The FluxProject and FluxNode are friend classes
	friend FluxProject;
	friend FluxNode;

public:
	FluxUniqueIdentifier();
	FluxUniqueIdentifier(const FluxUniqueIdentifier&);
	~FluxUniqueIdentifier();

	// If this unique identifier was initialized
	bool Initialized();

	// Invalidate this identifier
	void Invalidate();

	// Return the project internal name
	std::string GetInternalName();

	// Return the type
	Flux::Type GetType();

	// Check if this unique identifier is from the given project
	bool IsFromProjectWithInternalName(std::string _projectName);

	// Check if this unique identifier if from the given type
	bool IsFromType(Flux::Type _type);

	// Access as a flux node
	FluxNode* operator->() const;

	// Less operator
	bool operator <(const FluxUniqueIdentifier& rhs) const
	{
		// Compare the project names
		int stringNameCompare = m_ProjectName.compare(rhs.m_ProjectName);

		// Check project name first
		if (stringNameCompare != 0) return stringNameCompare != 0;
		// Ok same project. Compare the type
		else if (m_Type != rhs.m_Type) return m_Type < rhs.m_Type;
		// Ok same project and type, compare the identifier
		else return m_Identifier < rhs.m_Identifier;
	}

	// Compare operator
	bool operator ==(const FluxUniqueIdentifier& rhs) const
	{
		// Compare the project names
		int stringNameCompare = m_ProjectName.compare(rhs.m_ProjectName);

		// Check project name first
		if ((stringNameCompare == 0) && (m_Type == rhs.m_Type) && (m_Identifier == rhs.m_Identifier))
		{
			return true;
		}

		return false;
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

	// colocar aqui se é uma referencia raiz (nodo raiz) e pertence ao projeto, devemos ter como verificar caso seja do projeto e retornar ele (pegar ele atraves do manager)
};

// Json functions
void Flux::to_json(nlohmann::json& _json, const Flux::FluxUniqueIdentifier& _identifier);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxUniqueIdentifier& _identifier);

// SmallPack
FluxNamespaceEnd(Flux)