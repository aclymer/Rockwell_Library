#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CPT.h"
//#include "Rockwell_Library/Components/Hidden/Equation.h"

namespace Rockwell_Library
{
	void CPT::Execute(double p_dTimeStep)
	{		
		Value_B.EquationText			= Source_B.Value;	
		Output.Value					= Input.Value;
	}
}