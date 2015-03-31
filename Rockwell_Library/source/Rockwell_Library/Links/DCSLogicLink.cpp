#include "stdafx.h"
#include "Rockwell_Library/Links/DCSLogicLink.h"
#include "Ports.h"

using namespace System;
using namespace DCS::Links;

#pragma region IPS_NAMESPACE
namespace Rockwell_Library {
	
	#pragma region IPS_LINK
	#pragma region IPS_CONSTRUCTORS
	
	DCSLogicLink::DCSLogicLink() : Bool_BoolLink()
	{
	}
	
	#pragma endregion IPS_CONSTRUCTORS
	
	#pragma region IPS_PROPERTIES
	
	#pragma endregion IPS_PROPERTIES
	
	#pragma region IPS_METHODS
	
	System::Void DCSLogicLink::InitProperties()
	{
		IPS::Plugin::LinkBase::InitProperties();
	}//InitProperties
	
	#pragma endregion IPS_METHODS
	
	
	#pragma endregion IPS_LINK
	
}
#pragma endregion IPS_NAMESPACE
