////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxProject.h"
#include <json.hpp>
#include <iostream>
#include <fstream>

Flux::FluxProject::FluxProject()
{
	// Set the initial data
	m_UniqueIdentifierNumber = 0;
}

Flux::FluxProject::FluxProject(const Flux::FluxProject& other)
{
}

Flux::FluxProject::~FluxProject()
{
}

void Flux::FluxProject::SetExternalProjectName(std::string _projectName)
{
	// Set the external name
	m_ProjectExternalName = _projectName;

	// Check if the internal name was set
	if (m_ProjectInternalName.empty())
	{
		// Set the internal name too
		m_ProjectInternalName = _projectName;
	}
}

std::string Flux::FluxProject::GetExternalProjectName()
{
	return m_ProjectExternalName;
}

std::string Flux::FluxProject::GetInternalProjectName()
{
	return m_ProjectInternalName;
}

void Flux::FluxProject::SaveProjectInfo()
{
	// Our json variable
	nlohmann::json json;

	// Set the data
	json["ProjectExternalName"]				= m_ProjectExternalName;
	json["ProjectInternalName"]				= m_ProjectInternalName;
	json["ProjectUniqueIndexNumber"]		= m_UniqueIdentifierNumber;

	// Set the output file
	std::ofstream file;
	file.open(m_ProjectExternalName + ProjectFileExtension);
	file << json;
	file.close();
}

void Flux::FluxProject::LoadProjectInfo(std::string _projectName)
{
	std::ifstream file;
	file.open(_projectName + ProjectFileExtension);

	// Check if the file is open
	if (!file.is_open())
	{
		return;
	}

	// Our json variable
	nlohmann::json json;

	// Read the json data and close the file
	file >> json;
	file.close();

	// Set the project data
	m_ProjectExternalName				= json["ProjectExternalName"].get<std::string>();
	m_ProjectInternalName				= json["ProjectInternalName"].get<std::string>();
	m_UniqueIdentifierNumber			= json["ProjectUniqueIndexNumber"].get<uint32_t>();
}

Flux::FluxUniqueIdentifier Flux::FluxProject::GenerateUniqueIdentifier(Type _identifierType)
{
	// Our new unique identifier
	FluxUniqueIdentifier uniqueIdentifier;

	// Set the identifier data
	uniqueIdentifier.Initialize(GetInternalProjectName(), m_UniqueIdentifierNumber, _identifierType, this);

	// Increment the identifier index
	m_UniqueIdentifierNumber++;

	// Request to save the project info
	// SaveProjectInfo();

	return uniqueIdentifier;
}