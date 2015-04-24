#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/PID.h"

namespace Rockwell_Library
{
	void PID::Execute(double p_dTimeStep)
	{	
		EN.Value					= Input.Value;
		Output.Value				= Input.Value;

		DCSLogicComponent::Execute(p_dTimeStep);
	}
}