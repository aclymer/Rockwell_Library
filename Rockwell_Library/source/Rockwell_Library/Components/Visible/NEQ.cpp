#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/NEQ.h"

namespace Rockwell_Library
{
	void NEQ::Execute(double p_dTimeStep)
	{
		Value_A.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_A.Value));
		Value_B.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_B.Value));

		if (Value_A.Value != Value_B.Value)
			Output.Value = Input.Value;
		else
			Output.Value = false;
	}
}