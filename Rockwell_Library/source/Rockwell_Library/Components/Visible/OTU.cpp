#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OTU.h"

namespace Rockwell_Library
{
	void OTU::Execute(double p_dTimeStep)
	{
		Output.Value = Input.Value;
		Value.Value = false;

		if (Input.Value == true)
			Set_Property(Property.Value, Value);
	}
}