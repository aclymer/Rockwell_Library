#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/END.h"

namespace Rockwell_Library
{	
	void END::Execute(double p_dTimeStep)
	{
		Output.Value = Input.Value;
	}		
}