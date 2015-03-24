#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/ADD.h"

namespace Rockwell_Library
{
	void ADD::Execute(double p_dTimeStep)
	{
		Value.ValueAsObject		= Get_Property(Property.Value);
		Value_A.ValueAsObject	= Get_Property(Source_A.Value);
		Value_B.ValueAsObject	= Get_Property(Source_B.Value);

		if (Input.Value == true)
		{
			Value.Value = Value_A.Value + Value_B.Value;
			Set_Property(Property.Value, Value.ValueAsObject);
		}

		Output.Value = Input.Value;
	}
}