////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxProject.h"
#include "Node\FluxNodeArchiver.h"
#include "Node\Holder\FluxHolder.h"
#include <json.hpp>
#include <iostream>
#include <fstream>

Flux::FluxProject::FluxProject()
{
	// Set the initial data
	m_UniqueIdentifierNumber = 0;
	m_RootNode = nullptr;
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

Flux::FluxRoot* Flux::FluxProject::GetRootNode()
{
	return m_RootNode;
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
	file << json.dump(4);
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

#include "Node\FluxClass.h"
#include "Node\FluxFunction.h"
#include "Node\FluxVariable.h"

void Flux::FluxProject::SaveProjectData()
{
	// Prepare our archive objects
	FluxNodeArchiver<FluxClass> classArchiver("Class");
	FluxNodeArchiver<FluxFunction> functionArchiver("Function");
	FluxNodeArchiver<FluxVariable> variableArchiver("Variable");

	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> holderInstance;

	// Get all node objects from the holder
	typedef std::map<FluxUniqueIdentifier, Flux::FluxNode*> NodeIteratorType;
	NodeIteratorType& nodeObjects = holderInstance->GetNodeObjects();

	// For each node object
	for (NodeIteratorType::iterator it = nodeObjects.begin(); it != nodeObjects.end(); ++it)
	{
		// Get the current node
		Flux::FluxNode& currentNode = *it->second;

		// Get the unique identifier
		Flux::FluxUniqueIdentifier nodeIdentifier = currentNode.GetUniqueIdentifier();

		// Switch the node type
		switch (nodeIdentifier.GetType())
		{
			// Class
			case Flux::Type::Class:
			{
				// Archive this object
				classArchiver.InsertNode(currentNode);

				break;
			}

			// Function
			case Flux::Type::Function:
			{
				// Archive this object
				functionArchiver.InsertNode(currentNode);

				break;
			}

			// Variable
			case Flux::Type::Variable:
			{
				// Archive this object
				variableArchiver.InsertNode(currentNode);

				break;
			}
		}
	}

	nlohmann::json k;
	k["ClassObjects"] = classArchiver;
	k["FunctionObjects"] = functionArchiver;
	k["VariableObjects"] = variableArchiver;

	std::cout << k.dump(4) << std::endl;
}

void Flux::FluxProject::LoadProjectData()
{

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