#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CLR.h"

namespace Rockwell_Library
{
	void CLR::Execute(double p_dTimeStep)
	{
		Value.ValueAsObject = Get_Property(Property.Value);

		if (Input.Value)
		{
			Value.Value = 0;
			Set_Property(Property.Value, Value.ValueAsObject);
			Value.ValueAsObject = Get_Property(Property.Value);
		}

		Output.Value = Input.Value;
	}
}
