#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OTE.h"

namespace Rockwell_Library
{
	void OTE::Execute(double p_dTimeStep)
	{					
		Set_Property(Property.Value, Input.Value);

		Value.ValueAsObject = Get_Property(Property.Value);

		Output.Value		= Input.Value;
	}
}