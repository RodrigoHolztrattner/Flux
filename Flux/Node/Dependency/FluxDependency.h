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
#include "..\FluxNode.h"
#include <map>

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
// Class name: FluxDependency
////////////////////////////////////////////////////////////////////////////////
class FluxDependency
{
public:

	// The dependency type
	struct DependencyType
	{
		DependencyType() {}
		DependencyType(FluxUniqueIdentifier _identifier) : uniqueIdentifier(_identifier) {}

		// The unique identifier
		FluxUniqueIdentifier uniqueIdentifier;

		// The number of dependencies of this type
		uint32_t totalDependencies;
	};

public:
	FluxDependency(FluxUniqueIdentifier _ownerIdentifier);
	FluxDependency(const FluxDependency&);
	~FluxDependency();

	// Insert dependency
	void InsertDependency(const FluxUniqueIdentifier& _identifier);

	// Remove a dependency
	void RemoveDependency(const FluxUniqueIdentifier& _identifier);

	// Notify all dependencies
	void NotifyDependencies(FluxDependencyNotifyType _notifyType);

private:

///////////////
// VARIABLES //
private: //////

	// The node unique identifier
	FluxUniqueIdentifier m_OwnerIdentifier;

	// All items that depends on this
	std::map<Flux::FluxUniqueIdentifier, DependencyType> m_Dependencies;
};

// SmallPack
FluxNamespaceEnd(Flux)