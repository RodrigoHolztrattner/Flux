////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionSource.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxFunction.h"
#include "FluxFunctionSourceNode.h"
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
	=> Function data

		- Variable
		- Function Output
		- Control method

*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxFunctionSource
////////////////////////////////////////////////////////////////////////////////
class FluxFunctionSource
{
public:

public:
	FluxFunctionSource();
	FluxFunctionSource(const FluxFunctionSource&);
	~FluxFunctionSource();

public:

	// Create a new source node
	FluxFunctionSourceNode* CreateSourceNode(FluxFunctionSourceNodeType _type, FluxUniqueIdentifier _identifier);

///////////////
// VARIABLES //
private: //////

	// The begin source node
	FluxFunctionSourceNode* m_BeginSourceNode;

	// The End source node
	FluxFunctionSourceNode* m_EndSourceNode;

	// All source nodes
	std::map<uint32_t, FluxFunctionSourceNode*> m_SourceNodes;

private:

	// Our current internal index identifier count
	FluxFunctionInternalIndexIdentifier m_InternalIndexIdentifierCount;
};

/*
	- Todos nodos são salvos em uma lista no arquivo
	- É salvo o nodo inicial e o final (caso existam)
	- A reconstrução dos links é feita passando nodo por nodo e verificando os links de cada um (marcando os que já foram usados)
*/

// SmallPack
FluxNamespaceEnd(Flux)