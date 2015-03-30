#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/LIM.h"

namespace Rockwell_Library
{
	void LIM::Execute(double p_dTimeStep)
	{
		Value.Value		= dynamic_cast<IPS::Properties::Double^>(Get_Property(Property.Value));
		Value_A.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_A.Value));
		Value_B.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_B.Value));
		
		Output.Value			= Input.Value;

		if (Value_A.Value <= Value_B.Value)
		{
			if (Input.Value == true)
			{
				if (Value_A.Value <= Value.Value && Value.Value <= Value_B.Value)
					Output.Value = true;
				else
					Output.Value = false;

				Set_Property(Property.Value, Value.ValueAsObject);
			}
		}
		else if (Value_A.Value > Value_B.Value)
		{
			if (Input.Value == true)
			{
				if (Value_A.Value < Value.Value && Value.Value < Value_B.Value)
					Output.Value = false;
				else
					Output.Value = true;

				Set_Property(Property.Value, Value.ValueAsObject);
			}
		}
		else
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("Input Error: ", this->Identifier, "Low Limit must be less than or equal to High Limit"));
	}
}