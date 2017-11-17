////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProjectArchiver.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "..\FluxUniqueIdentifier.h"
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

// We know some classes
class FluxNode;
class FluxRoot;
class FluxClass;
class FluxFunction;
class FluxVariable;

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxProjectArchiver
////////////////////////////////////////////////////////////////////////////////
class FluxProjectArchiver
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxProjectArchiver& _object);
	friend void from_json(const nlohmann::json& _json, Flux::FluxProjectArchiver& _object);

private:

	// The FluxNode is a friend class
	friend FluxNode;

public:
	FluxProjectArchiver();
	FluxProjectArchiver(Flux::FluxProject* _projectPtr);
	FluxProjectArchiver(const FluxProjectArchiver&);
	~FluxProjectArchiver();

public:

	// Save the project data
	const void SaveProjectData(nlohmann::json& _json);

	// Load the project data
	void LoadProjectData(const nlohmann::json& _json);

	// Merge the current project data into our engine instance
	bool MergeProjectData(FluxRoot** _root);

protected:

///////////////
// VARIABLES //
private: //////

	// The project ptr
	FluxProject* m_CurrentProject;

	// Our node vectors
	std::vector<FluxRoot*> m_RootVector;
	std::vector<FluxClass*> m_ClassVector;
	std::vector<FluxFunction*> m_FunctionVector;
	std::vector<FluxVariable*> m_VariableVector;
};

// Json methods
void Flux::to_json(nlohmann::json& _json, const Flux::FluxProjectArchiver& _object);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxProjectArchiver& _object);

// SmallPack
FluxNamespaceEnd(Flux)