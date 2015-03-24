#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/Rung.h"

namespace Rockwell_Library
{
	System::Void Rung::Execute(double p_dTimeStep)
	{
		Output.Value = Input.Value;
		Rung_Port.Value = Input.Value;
	}
}