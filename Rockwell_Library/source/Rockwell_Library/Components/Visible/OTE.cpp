#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/OTE.h"

namespace Rockwell_Library
{
	void OTE::Execute(double p_dTimeStep)
	{					
		Set_Property(Property.Value, Input.Value);

		Output.Value		= Input.Value;
	}
}