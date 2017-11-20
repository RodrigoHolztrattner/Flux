////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProjectFile.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxProjectFile.h"

#include <json.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>

Flux::FluxProjectFile::FluxProjectFile()
{
	// Set the initial data
	m_RootNamespace = nullptr;
}

Flux::FluxProjectFile::FluxProjectFile(const Flux::FluxProjectFile& other)
{
}

Flux::FluxProjectFile::~FluxProjectFile()
{
}

bool Flux::FluxProjectFile::LoadProject(std::string _projectLocation)
{
	// Check if the directory exist
	bool result = std::experimental::filesystem::exists(_projectLocation);
	if (!result)
	{
		// Create the root namespace
		result = CreateRootNamespace(_projectLocation);
		if (!result)
		{
			return false;
		}
	}

	// Create the root namespace object
	m_RootNamespace = new NamespaceFile();

	// Load the project recursively
	result = LoadProjectRecursively(_projectLocation, m_RootNamespace);

	for (auto & p : std::experimental::filesystem::directory_iterator(_projectLocation))
		std::cout << p << std::endl;
	std::experimental::filesystem::exists(_projectLocation);

	return true;
}

bool Flux::FluxProjectFile::LoadProjectRecursively(std::string _currentPath, NamespaceFile* _currentNamespace)
{
	// Get the namespace file data
	// ...

	// Set the namespace base info
	// ...

	// For each class
		// Load the class (if error, delete everything -> return false)
		// Insert it

	// For each namespace
		// Load the namespace (if error, delete everything -> return false)
		// Insert it

	return true;
}

void Flux::FluxProjectFile::Delete()
{
	// Try to delete the root project entirelly
	DeleteProjectRecursively(m_RootNamespace);
}

void Flux::FluxProjectFile::DeleteProjectRecursively(NamespaceFile* _currentNamespace)
{
	// Check if the current namespace is valid
	if (_currentNamespace == nullptr)
	{
		return;
	}
}