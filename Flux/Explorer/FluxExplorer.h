////////////////////////////////////////////////////////////////////////////////
// Filename: FluxExplorer.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\FluxConfig.h"
#include "..\FluxUniqueIdentifier.h"
#include <string>

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

/*
	* Wonderland

		- Projects
			- Pode ser transformado em addons (quando isso ocorre todos os identificadores s�o marcados como addons).

		- Addons (novos tipos bases e fun��es)
			- S�o representados por um unico arquivo contendo toda a funcionalidade.
			- Podem ser transformados de um pseudo C++.
			- Os nodos desses addons s�o adicionados ao iniciar a engine ou ao carregar um novo addon.
			- Caso um nodo do projeto atual esteja usando alguma funcionalidade daqui e essa mesma esteja desatualizada, em vez
			de tentarmos recompilar (que obviamente n�o � poss�vel nesse caso) emitimos um aviso dizendo que a vers�o deste addon
			est� desatualizada e possivelmente � incompat�vel, perguntando ao usu�rio se ele deseja retroceder � vers�o antiga por
			sua propria conta e risco.

	* Um projeto � representado numa s�rie de diret�rios sendo que a raiz tem o nome do projeto e cada diret�rio � um namespace.
		- Cada namespace possui um arquivo de configura��o esse arquivo diz respeito a quais outros arquivos no mesmo diret�rio est�o inclusos no
		projeto, basicamente � com essa informa��o que procuraremos quais outros arquivos/diret�rios abrir.
		- Dentro de um namespace n�s temos sempre um arquivo que representa o namespace (al�m daquele das configura��es), este arquivo contem
		declara��es de vari�veis e fun��es globais dentro do escopo do namespace, al�m de enums e structs. Temos tamb�m em v�rios outros arquivos
		as classes existentes dentro desse namespace.
		- Cada classe pode conter vari�veis e fun��es membros, da mesma forma que uma representa��o em C++ teria.

	* Um addon � representado por um arquivo de configura��o do addon e o arquivo principal (e �nico) em si que contem toda a estrutura desse addon.

	* Um identificador deve dizer se o item identificado faz parte de um projeto ou addon.

	* Cada depend�ncia possui um campo de data e cada nodo tamb�m possui um campo de data, al�m de conter uma lista de todas as dependencias do
	mesmo, sempre que vamos compilar ou usar um nodo ele verificar� para cada item da sua lista de depend�ncias se as datas dessas depend�ncias
	est�o iguais a ultima modifica��o dos nodos, caso n�o estejam ent�o tentaremos recompilar esses nodos (sempre setando uma flag de compila��o
	para que caso exista uma recurs�o de dependencia ela suma).
		
		
**/

// SmallPack
FluxNamespaceBegin(Flux)

// We know the FluxProjectFile class
class FluxProjectFile;

// We know the FluxAddonFile class
class FluxAddonFile;

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxExplorer
////////////////////////////////////////////////////////////////////////////////
class FluxExplorer
{
private:

public:
	FluxExplorer();
	FluxExplorer(const FluxExplorer&);
	~FluxExplorer();

	// Save a project
	bool SaveProject(FluxProject* _project);

	// Load a project
	FluxProjectFile* LoadProject(std::string _projectName);

	// Load an addon
	FluxAddonFile* LoadAddon(std::string _addonName);

public:

///////////////
// VARIABLES //
private: //////

};

// SmallPack
FluxNamespaceEnd(Flux)