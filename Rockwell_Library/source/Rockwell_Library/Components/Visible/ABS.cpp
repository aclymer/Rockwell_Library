#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/ABS.h"

namespace Rockwell_Library
{
	void ABS::Execute(double p_dTimeStep)
	{
		Value_A.ValueAsObject	= Get_Property(Source_A.Value);
		Value_B.ValueAsObject	= Get_Property(Source_B.Value);

		if (Input.Value == true)
		{
			Value_B.Value	= Math::Abs(Value_A.Value);
			Set_Property(Source_B.Value, Value_B.ValueAsObject);
		}

		Output.Value = Input.Value;
	}
}