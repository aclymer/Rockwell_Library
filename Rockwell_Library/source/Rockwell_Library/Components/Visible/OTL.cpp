#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OTL.h"

namespace Rockwell_Library
{
	void OTL::Execute(double p_dTimeStep)
	{	
		if (Input.Value)
			Set_Property(Property.Value, Input);
		
		Value.ValueAsObject	= Get_Property(Property.Value);
		Output.Value		= Input.Value;
	}
}