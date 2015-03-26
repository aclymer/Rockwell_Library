#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/SVC.h"

namespace Rockwell_Library
{	
	void SVC::Execute(double p_dTimeStep)
	{
		Output.Value = Input.Value;
	}		
}