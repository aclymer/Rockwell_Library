#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/LIM.h"

namespace Rockwell_Library
{
	void LIM::Execute(double p_dTimeStep)
	{
		Value.ValueAsObject		= Get_Property(Property.Value);
		Value_A.ValueAsObject	= Get_Property(Source_A.Value);
		Value_B.ValueAsObject	= Get_Property(Source_B.Value);
		
		Output.Value			= Input.Value;

		if (Value_A.Value <= Value_B.Value)
		{
			if (Input.Value == true)
			{
				if (Value_A.Value <= Value.Value && Value.Value <= Value_B.Value)
					Output.Value = true;

				Set_Property(Property.Value, Value.ValueAsObject);
			}
		}
		else
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("Input Error: ", this->Identifier, "Low Limit must be less than or equal to High Limit"));
	}
}