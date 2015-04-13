#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/ABS.h"

namespace Rockwell_Library
{
	void ABS::Execute(double p_dTimeStep)
	{
		if (Input.Value == true)
		{
			Value_A.ValueAsObject	= Get_Property(Source_A.Value);
			Value_B.ValueAsObject	= Get_Property(Source_B.Value);
			Value_B.Value			= Math::Abs(Value_A.Value);

			Set_Property(Source_B.Value, Value_B);
		}

		Output.Value = Input.Value;
		DCSLogicComponent::Execute(p_dTimeStep);
	}
}