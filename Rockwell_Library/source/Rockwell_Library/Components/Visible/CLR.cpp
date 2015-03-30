#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CLR.h"

namespace Rockwell_Library
{
	void CLR::Execute(double p_dTimeStep)
	{
		Value.Value = dynamic_cast<IPS::Properties::Integer^>(Get_Property(Property.Value));

		if (Input.Value)
		{
			Value.Value = 0;
			Set_Property(Property.Value, Value.ValueAsObject);
		}

		Output.Value = Input.Value;
	}
}
