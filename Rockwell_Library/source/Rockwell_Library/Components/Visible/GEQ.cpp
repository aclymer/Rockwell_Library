#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/GEQ.h"

namespace Rockwell_Library
{
	void GEQ::Execute(double p_dTimeStep)
	{
		Value_A.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_A.Value));
		Value_B.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_B.Value));

		if (Value_A.Value >= Value_B.Value)
			Output.Value = Input.Value;
		else
			Output.Value = false;
	}
}