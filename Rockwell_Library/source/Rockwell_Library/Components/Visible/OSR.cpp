#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OSR.h"

namespace Rockwell_Library
{
	void OSR::Execute(double p_dTimeStep)
	{
		Output.Value = false;

		if (Input.Value == true && Value.Value == false)
			Output.Value = true;

		Set_Property(Property.Value, Input.ValueAsObject);
	}
}