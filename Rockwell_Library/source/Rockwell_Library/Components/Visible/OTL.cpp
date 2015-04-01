#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OTL.h"

namespace Rockwell_Library
{
	void OTL::Execute(double p_dTimeStep)
	{	
		Output.Value = Input.Value;

		if (Input.Value == true)
			Set_Property(Property.Value, Input);
	}
}