#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/RET.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	System::Void RET::Execute(double p_dTimeStep)
	{
		Output.Value = Input.Value;
	}
}