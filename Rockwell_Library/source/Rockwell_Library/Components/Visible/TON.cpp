#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/TON.h"

namespace Rockwell_Library
{
	void TON::Execute(double p_dTimeStep)
	{
		Set_Property(Property.Value + "/TT",  TT);
		Set_Property(Property.Value + "/EN",  Output);
		Set_Property(Property.Value + "/DN",  DN);
		Set_Property(Property.Value + ".ACC", ACC);

		Output.Value = Input.Value;

		DCSLogicComponent::Execute(p_dTimeStep);
	}
}
