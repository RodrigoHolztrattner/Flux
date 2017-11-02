////////////////////////////////////////////////////////////////////////////////
// Filename: FluxProject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxProject.h"

Flux::FluxProject::FluxProject()
{
	// Set the initial data
	// ...
}

Flux::FluxProject::FluxProject(const Flux::FluxProject& other)
{
}

Flux::FluxProject::~FluxProject()
{
}

std::string Flux::FluxProject::GetProjectName()
{
	return m_ProjectName;
}