#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CPT.h"

namespace Rockwell_Library
{
	void CPT::Execute(double p_dTimeStep)
	{
		Value_A.ValueAsObject		= Get_Property(Property.Value);

		Output.Value = Input.Value;
	}
}