#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OTU.h"

namespace Rockwell_Library
{
	void OTU::Execute(double p_dTimeStep)
	{
		Value.Value		= false;

		if (Input.Value == true)
			Set_Property(Property.Value, Value);

		Output.Value	= Input.Value;
	}
}