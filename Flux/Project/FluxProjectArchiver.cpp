////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProjectArchiver.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxProjectArchiver.h"
#include "..\Node\Archiver\FluxNodeArchiver.h"
#include "..\Node\Dependency\FluxDependencyManager.h"
#include "..\Node\Holder\FluxHolder.h"
#include <json.hpp>
#include <iostream>
#include <fstream>

#include "..\Node\FluxRoot.h"
#include "..\Node\FluxClass.h"
#include "..\Node\FluxFunction.h"
#include "..\Node\FluxVariable.h"

Flux::FluxProjectArchiver::FluxProjectArchiver()
{
	// Set the initial data
	m_CurrentProject = nullptr;
}

Flux::FluxProjectArchiver::FluxProjectArchiver(Flux::FluxProject* _projectPtr)
{
	// Set the initial data
	m_CurrentProject = _projectPtr;
}

Flux::FluxProjectArchiver::FluxProjectArchiver(const Flux::FluxProjectArchiver& other)
{
	m_CurrentProject = other.m_CurrentProject;
	m_RootVector = other.m_RootVector;
	m_ClassVector = other.m_ClassVector;
	m_FunctionVector = other.m_FunctionVector;
	m_VariableVector = other.m_VariableVector;
}

Flux::FluxProjectArchiver::~FluxProjectArchiver()
{
}

const void Flux::FluxProjectArchiver::SaveProjectData(nlohmann::json& _json)
{
	// Prepare our archive objects
	FluxNodeArchiver<FluxRoot> rootArchiver;
	FluxNodeArchiver<FluxClass> classArchiver;
	FluxNodeArchiver<FluxFunction> functionArchiver;
	FluxNodeArchiver<FluxVariable> variableArchiver;

	// Check if our project ptr is valid
	if (m_CurrentProject == nullptr)
	{
		return;
	}

	// Get the holder dependency manager instances
	Flux::GlobalInstance<Flux::FluxHolder> holderInstance;
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

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

		// Check if the unique identifier is from the current project
		if (m_CurrentProject->GetInternalProjectName().compare(nodeIdentifier.GetInternalName()) != 0)
		{
			// Ignore this node
			continue;
		}

		// Switch the node type
		switch (nodeIdentifier.GetType())
		{
			// Root
			case Flux::Type::Root:
			{
				// Archive this object
				rootArchiver.InsertNode(currentNode);

				break;
			}

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

	// Get all dependencies from the current project
	std::vector<Flux::FluxDependency> dependencies = dependencyManagerInstance->GetDependenciesFromProject(m_CurrentProject->GetInternalProjectName());

	// Set the json
	_json = nlohmann::json
	{
		{ "RootObject", rootArchiver },
		{ "ClassObjects", classArchiver },
		{ "FunctionObjects", functionArchiver },
		{ "VariableObjects", variableArchiver },
		{ "DependencyObjects", dependencies }
	};

	// Log
	std::cout << "LOG: " << rootArchiver.size() << " root node was saved" << std::endl;
	std::cout << "LOG: " << classArchiver.size() << " class nodes were saved" << std::endl;
	std::cout << "LOG: " << functionArchiver.size() << " function nodes were saved" << std::endl;
	std::cout << "LOG: " << variableArchiver.size() << " variable nodes were saved" << std::endl;
	std::cout << "LOG: " << dependencies.size() << " dependencies were saved" << std::endl;
}

void Flux::FluxProjectArchiver::LoadProjectData(const nlohmann::json& _json)
{
	std::vector<Flux::FluxDependency> dependencies;

	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> holderInstance;
	Flux::GlobalInstance<Flux::FluxDependencyManager> dependencyManagerInstance;

	// Prepare our archive objects
	FluxNodeArchiver<FluxRoot> rootArchiver;
	FluxNodeArchiver<FluxClass> classArchiver;
	FluxNodeArchiver<FluxFunction> functionArchiver;
	FluxNodeArchiver<FluxVariable> variableArchiver;

	// Load from the json
	rootArchiver = _json.at("RootObject").get<FluxNodeArchiver<FluxRoot>>();
	classArchiver = _json.at("ClassObjects").get<FluxNodeArchiver<FluxClass>>();
	functionArchiver = _json.at("FunctionObjects").get<FluxNodeArchiver<FluxFunction>>();
	variableArchiver = _json.at("VariableObjects").get<FluxNodeArchiver<FluxVariable>>();

	// Load from the json
	dependencies = _json.at("DependencyObjects").get<std::vector<Flux::FluxDependency>>();

	// Get our node vectors
	rootArchiver.GetNodeVectorReference(&m_RootVector);
	classArchiver.GetNodeVectorReference(&m_ClassVector);
	functionArchiver.GetNodeVectorReference(&m_FunctionVector);
	variableArchiver.GetNodeVectorReference(&m_VariableVector);

	// Construct the dependencies
	dependencyManagerInstance->ConstructDependencies(dependencies);

	// Log
	std::cout << "LOG: " << rootArchiver.size() << " root node was loaded" << std::endl;
	std::cout << "LOG: " << classArchiver.size() << " class nodes were loaded" << std::endl;
	std::cout << "LOG: " << functionArchiver.size() << " function nodes were loaded" << std::endl;
	std::cout << "LOG: " << variableArchiver.size() << " variable nodes were loaded" << std::endl;
	std::cout << "LOG: " << dependencies.size() << " dependencies were loaded and constructed" << std::endl;
}

bool Flux::FluxProjectArchiver::MergeProjectData(FluxRoot** _root)
{
	// Check if we only have one root
	if (m_RootVector.size() != 1)
	{
		return false;
	}

	// Set the project root
	*_root = m_RootVector[0];

	// Get the holder instance
	Flux::GlobalInstance<Flux::FluxHolder> fluxHolderInstance;

	// For each node vector
	for (auto* nodePtr : m_RootVector) fluxHolderInstance->InsertNodeWithIdentifier(nodePtr, nodePtr->GetUniqueIdentifier());
	for (auto* nodePtr : m_ClassVector) fluxHolderInstance->InsertNodeWithIdentifier(nodePtr, nodePtr->GetUniqueIdentifier());
	for (auto* nodePtr : m_FunctionVector) fluxHolderInstance->InsertNodeWithIdentifier(nodePtr, nodePtr->GetUniqueIdentifier());
	for (auto* nodePtr : m_VariableVector) fluxHolderInstance->InsertNodeWithIdentifier(nodePtr, nodePtr->GetUniqueIdentifier());

	// Log
	std::cout << "LOG: " << m_RootVector.size() << " root node was constructed" << std::endl;
	std::cout << "LOG: " << m_ClassVector.size() << " class nodes were constructed" << std::endl;
	std::cout << "LOG: " << m_FunctionVector.size() << " function nodes were constructed" << std::endl;
	std::cout << "LOG: " << m_VariableVector.size() << " variable nodes were constructed" << std::endl;

	return true;
}

//////////
// JSON //
//////////

void Flux::to_json(nlohmann::json& _json, const Flux::FluxProjectArchiver& _object)
{
	// Remove the const and save the project
	const_cast<Flux::FluxProjectArchiver&>(_object).SaveProjectData(_json); // TODO nao estamos passando o nome do project
}

void Flux::from_json(const nlohmann::json& _json, Flux::FluxProjectArchiver& _object)
{
	// Load the project
	_object.LoadProjectData(_json);
}