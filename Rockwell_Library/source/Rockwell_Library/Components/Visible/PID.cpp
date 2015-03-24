#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/PID.h"

namespace Rockwell_Library
{
	void PID::Execute(double p_dTimeStep)
	{
		Value.ValueAsObject		= Get_Property(Property.Value);
		Value_A.ValueAsObject	= Get_Property(Source_A.Value);
		Value_B.ValueAsObject	= Get_Property(Source_B.Value);

		Output.Value = Input.Value;
	}
}