////////////////////////////////////////////////////////////////////////////////
// Filename: FluxDependencyInterface.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\FluxConfig.h"
#include "..\..\FluxUniqueIdentifier.h"

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

// The dependency relation types
enum class FluxDependencyRelationType
{
	SrcDependsOnDst,
	DstDependsOnSrc,
	BothDependsOnEachOther
};

// The dependency notify types
enum class FluxDependencyNotifyType
{
	SignatureChanged,
	SuperficialDataChanged,
	OriginDeleted
};

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxDependencyInterface
////////////////////////////////////////////////////////////////////////////////
class FluxDependencyInterface
{
public:

	FluxDependencyInterface();
	FluxDependencyInterface(const FluxDependencyInterface&);
	~FluxDependencyInterface();

	// When we received a notification from a dependency
	virtual void NotificationFromDependency(FluxUniqueIdentifier _identifier, FluxDependencyNotifyType _notifyType);

private:

///////////////
// VARIABLES //
private: //////

};

// SmallPack
FluxNamespaceEnd(Flux)