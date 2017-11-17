////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependency.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\..\FluxUniqueIdentifier.h"
#include "FluxDependencyInterface.h"
#include <unordered_map>

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

/*
* um nodo deve ter esse item registrado pra cada dependência que acontece
* Preciso pensar no que aconetce quando o nodo é deletado ou modificado ou uma nova dependencia é adicionada
* O manager tem todas as dependências, se acontecer algo com X ele vai procurar no manager todos que dependem de 
X e avisar esses Y Z invalidando-os.
* Precisa do contador?
* Acho que precisa do contador, suponto que uma classe tenha 2 variáveis do mesmo tipo, isso implicaria em 2 dependencias
diferentes, devemos usar o mesmo tipo de dependência mas sim com um contador.

* O manager deve ser global e permitir o registro dessas dependências, assim como propagar os avisos
* Deve ter 3 tipos de dependencia, From->To, To->From, Both (pensar outros nomes)
* A dependency class deve ter funções virtuais de notify e receive notify (pensar nomes que tenham a ver com dependency)
*/


////////////////////////////////////////////////////////////////////////////////
// Class name: FluxUniqueIdentifier
////////////////////////////////////////////////////////////////////////////////
class BFluxUniqueIdentifier
{
public:
	BFluxUniqueIdentifier() {}
	~BFluxUniqueIdentifier() {}

	Flux::BFluxUniqueIdentifier& operator=(Flux::BFluxUniqueIdentifier&& _Right)

	{	// assign from moved pair

		return (*this);
	}

	// Compare operator
	bool operator <(const BFluxUniqueIdentifier& rhs) const
	{
		return true;
	}


};

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxDependency
////////////////////////////////////////////////////////////////////////////////
class FluxDependency
{
	// Json friend functions
	friend void to_json(nlohmann::json& _json, const Flux::FluxDependency& _object);
	friend void from_json(const nlohmann::json& _json, Flux::FluxDependency& _object);

public:

	// The dependency type
	struct DependencyType
	{
		// Json friend functions
		friend void to_json(nlohmann::json& _json, const Flux::FluxDependency::DependencyType& _object);
		friend void from_json(const nlohmann::json& _json, Flux::FluxDependency::DependencyType& _object);

		DependencyType() {}
		DependencyType(FluxUniqueIdentifier _identifier) : uniqueIdentifier(_identifier), totalDependencies(1) {}

		// The unique identifier
		FluxUniqueIdentifier uniqueIdentifier;

		// The number of dependencies of this type
		uint32_t totalDependencies;
	};

public:
	FluxDependency();
	FluxDependency(FluxUniqueIdentifier _ownerIdentifier);
	~FluxDependency();

	// Insert dependency
	void InsertDependency(FluxUniqueIdentifier& _identifier);

	// Remove a dependency
	void RemoveDependency(FluxUniqueIdentifier& _identifier);

	// Notify all dependencies
	void NotifyDependencies(FluxDependencyNotifyType _notifyType);

	// Return the owner unique identifier
	FluxUniqueIdentifier GetOwnerIdentifier();

	// Return the total number of dependencies
	uint32_t GetDependencyCount() { return m_Dependencies.size(); }

private:

///////////////
// VARIABLES //
private: //////

	// The node unique identifier
	FluxUniqueIdentifier m_OwnerIdentifier;

	// All items that depends on this
	std::map<FluxUniqueIdentifier, Flux::FluxDependency::DependencyType> m_Dependencies;
};

// Json methods
void Flux::to_json(nlohmann::json& _json, const Flux::FluxDependency& _object);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxDependency& _object);
//
void Flux::to_json(nlohmann::json& _json, const Flux::FluxDependency::DependencyType& _object);
void Flux::from_json(const nlohmann::json& _json, Flux::FluxDependency::DependencyType& _object);

// SmallPack
FluxNamespaceEnd(Flux)