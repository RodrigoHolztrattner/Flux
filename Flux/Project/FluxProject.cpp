////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxProject.h"
#include "..\Node\Holder\FluxHolder.h"
#include "..\Node\FluxRoot.h"
#include "FluxProjectManager.h"
#include "FluxProjectArchiver.h"

#include <json.hpp>
#include <iostream>
#include <fstream>

Flux::FluxProject::FluxProject()
{
	// Set the initial data
	m_UniqueIdentifierNumber = 0;
	m_RootNode = nullptr;
	m_Initialized = false;
}

Flux::FluxProject::FluxProject(const Flux::FluxProject& other)
{
}

Flux::FluxProject::~FluxProject()
{
}

bool Flux::FluxProject::CreateNewProject(std::string _projectName)
{
	// Get the project manager instance
	Flux::GlobalInstance<Flux::FluxProjectManager> projectManagerInstance;

	// Search for a project with the same name
	if (projectManagerInstance->GetProjectWithInternalName(_projectName) != nullptr)
	{
		// There is a project with the same name, we failed to create a new one
		return false;
	}

	// Set the project internal and external names
	m_ProjectExternalName = _projectName;
	m_ProjectInternalName = _projectName;

	// Create a new root node
	m_RootNode = new Flux::FluxRoot(this);
	// m_RootNode->SetParent(*this);
	m_RootNode->SetExternalName("ProjectRoot");

	// Set initialized to true
	m_Initialized = true;

	// Insert the new project into the manager
	projectManagerInstance->AddProject(this);

	return true;
}

bool Flux::FluxProject::LoadProject(std::string _projectFilePath)
{
	// Get the project manager instance
	Flux::GlobalInstance<Flux::FluxProjectManager> projectManagerInstance;

	// Load the project info
	if (!LoadProjectInfo(_projectFilePath))
	{
		// We cant load this project info
		return false;
	}

	// Search for a project with the same name
	if (projectManagerInstance->GetProjectWithInternalName(m_ProjectExternalName) != nullptr)
	{
		// There is a project with the same name, we failed to add this one
		return false;
	}

	// Load the project data
	if (!LoadProjectData())
	{
		// We cant load this project data
		return false;
	}

	// Set initialized to true
	m_Initialized = true;

	// Insert the project into the manager
	projectManagerInstance->AddProject(this);

	return true;
}

bool Flux::FluxProject::SaveProject()
{
	// Save the project info
	if (!SaveProjectInfo())
	{
		// We cant Save this project info
		return false;
	}

	// Save the project data
	if (!SaveProjectData())
	{
		// We cant Save this project data
		return false;
	}

	return true;
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

Flux::FluxRoot* Flux::FluxProject::GetRootNode()
{
	return m_RootNode;
}

bool Flux::FluxProject::SaveProjectInfo()
{
	// Our json variable
	nlohmann::json json;

	// Set the data
	json["ProjectExternalName"] = m_ProjectExternalName;
	json["ProjectInternalName"] = m_ProjectInternalName;
	json["ProjectUniqueIndexNumber"] = m_UniqueIdentifierNumber;

	// Set the output file
	std::ofstream file;
	file.open(m_ProjectExternalName + ProjectInfoFileExtension);
	file << json.dump(4);
	file.close();

	return true;
}

bool Flux::FluxProject::LoadProjectInfo(std::string _projectFilePath)
{
	std::ifstream file;
	file.open(_projectFilePath + ProjectInfoFileExtension);

	// Check if the file is open
	if (!file.is_open())
	{
		return false;
	}

	// Our json variable
	nlohmann::json json;

	// Read the json data and close the file
	file >> json;
	file.close();

	// Set the project data
	m_ProjectExternalName = json["ProjectExternalName"].get<std::string>();
	m_ProjectInternalName = json["ProjectInternalName"].get<std::string>();
	m_UniqueIdentifierNumber = json["ProjectUniqueIndexNumber"].get<uint32_t>();

	return true;
}

bool Flux::FluxProject::SaveProjectData()
{
	// Setup our project archiver
	Flux::FluxProjectArchiver projectArchiver(this);

	// Our json variable
	nlohmann::json json;

	// Set the data
	json["ProjectData"] = projectArchiver;

	// Set the output file
	std::ofstream file;
	file.open(m_ProjectExternalName + ProjectDataFileExtension);
	file << json.dump(4);
	file.close();

	return true;
}

bool Flux::FluxProject::LoadProjectData()
{
	std::ifstream file;

	// Load our project
	file.open(m_ProjectExternalName + ProjectDataFileExtension);

	// Check if the file is open
	if (!file.is_open())
	{
		return false;
	}

	// Our json variable
	nlohmann::json json;

	// Read the json data and close the file
	file >> json;
	file.close();

	// Setup our project archiver
	Flux::FluxProjectArchiver projectArchiver(this);

	std::cout << json.dump(4) << std::endl;

	// Read the data from the json
	projectArchiver = json.at("ProjectData").get<Flux::FluxProjectArchiver>();

	// Merge(commit) the project data
	if (!projectArchiver.MergeProjectData(&m_RootNode))
	{
		return false;
	}

	return true;
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

Flux::FluxProject::operator Flux::FluxUniqueIdentifier() const
{ 
	return m_RootNode->GetUniqueIdentifier(); 
}