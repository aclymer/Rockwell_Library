#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/EQU.h"

namespace Rockwell_Library
{
	void EQU::Execute(double p_dTimeStep)
	{
		try
		{
			Value_A.ValueAsObject	= Get_Property(Source_A.Value);
			Value_B.ValueAsObject	= Get_Property(Source_B.Value);
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
		}

		if (Value_A.Value == Value_B.Value)
			Output.Value = Input.Value;
		else
			Output.Value = false;
	}
}