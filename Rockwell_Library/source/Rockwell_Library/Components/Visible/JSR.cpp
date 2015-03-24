#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/JSR.h"

namespace Rockwell_Library
{
	void JSR::Execute(double p_dTimeStep)
	{
		if (Input.Value)
			DCSLogicComponent::JumpToSubroutine(Property.Value);

		Output.Value = Input.Value;
	}
}