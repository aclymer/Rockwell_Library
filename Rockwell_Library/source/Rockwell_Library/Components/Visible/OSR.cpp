#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OSR.h"

namespace Rockwell_Library
{
	void OSR::Execute(double p_dTimeStep)
	{
		Output.Value = false;

		if (Input.Value)
		{
			Value.ValueAsObject = Get_Property(Property.Value);

			if (!Value.Value)
				Output.Value = true;
		}

		Set_Property(Property.Value, Input);
	}
}