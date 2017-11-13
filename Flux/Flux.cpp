// Flux.cpp : Defines the entry point for the console application.
//

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

struct MyRecord
{
	uint8_t x, y;
	float z;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(x, y, z);
	}
};

struct SomeData
{
	int32_t id;
	std::shared_ptr<std::unordered_map<uint32_t, MyRecord>> data;

	template <class Archive>
	void save(Archive & ar) const
	{
		ar(data);
	}

	template <class Archive>
	void load(Archive & ar)
	{
		static int32_t idGen = 0;
		id = idGen++;
		ar(data);
	}
};

#include "FluxUniqueIdentifier.h"
#include "FluxProject.h"
#include "Node\FluxClass.h"
#include "Node\FluxFunction.h"
#include "Node\FluxVariable.h"

int main()
{
	// PROJECT //

	// Create a new project
	Flux::FluxProject newproject;

	// Try to load an old info
	newproject.LoadProjectInfo("Neverland");

	// Set the project data
	newproject.SetExternalProjectName("Neverland");

	// CLASS //

	// Create a new class
	Flux::FluxClass newClass(&newproject);

	// Set the class data
	newClass.SetExternalName("DummyClass");

	// VARIABLE //

	// Create a new variable
	Flux::FluxVariable newVariable(&newproject);

	// Set the variable data
	newVariable.SetExternalName("DummyVariable");
	newVariable.SetVariableType(newClass);

	// Add a member variable to our class
	newClass.AddMemberVariable(newVariable, Flux::FluxAccessModifier::Private);

	// // //

	// Save the current project
	newproject.SaveProjectInfo();

	/*
	std::ofstream os("out.cereal", std::ios::binary);
	cereal::BinaryOutputArchive archive(os);

	SomeData myData;
	archive(myData);
	*/

	Flux::GlobalInstance<Flux::FluxUniqueIdentifier> identifier;
	// int a = identifier->GetUniqueIdentifier();
	// std::cout << a << std::endl;
	return 0;
}

/*


	Base
	{

	}

	Libraries
	{

	}

		Project
		{
			- Variables
			- Functions

			Class <Node>
			{
				- Variables	(member/not-member)
				- Functions (member/not-member)
			}

			Namespace <Node>
			{
				
			}
		}

		//
		//
		//

		Node
		{
			Type (Class, Structure?, Namespace, Project);
			UniqueIdentifier;
			Name;
			Node parent;
			vector<Node> children;
		}

*/

/*
	=> Vetores de objectos globais com identificadores:

		Class
		Structures
		Variables
		Types



*/