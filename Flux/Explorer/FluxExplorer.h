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
			- Pode ser transformado em addons (quando isso ocorre todos os identificadores são marcados como addons).

		- Addons (novos tipos bases e funções)
			- São representados por um unico arquivo contendo toda a funcionalidade.
			- Podem ser transformados de um pseudo C++.
			- Os nodos desses addons são adicionados ao iniciar a engine ou ao carregar um novo addon.
			- Caso um nodo do projeto atual esteja usando alguma funcionalidade daqui e essa mesma esteja desatualizada, em vez
			de tentarmos recompilar (que obviamente não é possível nesse caso) emitimos um aviso dizendo que a versão deste addon
			está desatualizada e possivelmente é incompatível, perguntando ao usuário se ele deseja retroceder à versão antiga por
			sua propria conta e risco.

	* Um projeto é representado numa série de diretórios sendo que a raiz tem o nome do projeto e cada diretório é um namespace.
		- Cada namespace possui um arquivo de configuração esse arquivo diz respeito a quais outros arquivos no mesmo diretório estão inclusos no
		projeto, basicamente é com essa informação que procuraremos quais outros arquivos/diretórios abrir.
		- Dentro de um namespace nós temos sempre um arquivo que representa o namespace (além daquele das configurações), este arquivo contem
		declarações de variáveis e funções globais dentro do escopo do namespace, além de enums e structs. Temos também em vários outros arquivos
		as classes existentes dentro desse namespace.
		- Cada classe pode conter variáveis e funções membros, da mesma forma que uma representação em C++ teria.

	* Um addon é representado por um arquivo de configuração do addon e o arquivo principal (e único) em si que contem toda a estrutura desse addon.

	* Um identificador deve dizer se o item identificado faz parte de um projeto ou addon.

	* Cada dependência possui um campo de data e cada nodo também possui um campo de data, além de conter uma lista de todas as dependencias do
	mesmo, sempre que vamos compilar ou usar um nodo ele verificará para cada item da sua lista de dependências se as datas dessas dependências
	estão iguais a ultima modificação dos nodos, caso não estejam então tentaremos recompilar esses nodos (sempre setando uma flag de compilação
	para que caso exista uma recursão de dependencia ela suma).
		
		
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