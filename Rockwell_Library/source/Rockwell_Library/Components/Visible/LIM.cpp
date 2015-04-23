#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/LIM.h"

namespace Rockwell_Library
{
	void LIM::Execute(double p_dTimeStep)
	{
		Output.Value = Input.Value;

		if (Input.Value)
		{
			try
			{
				Value.ValueAsObject		= Get_Property(Property.Value);
				Value_A.ValueAsObject	= Get_Property(Source_A.Value);
				Value_B.ValueAsObject	= Get_Property(Source_B.Value);
			}
			catch(Exception^ ex)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
			}

			if (Value_A.Value <= Value_B.Value)
			{
				if (Value_A.Value <= Value.Value && Value.Value <= Value_B.Value)
					Output.Value = true;
				else
					Output.Value = false;
			}
			else if (Value_A.Value > Value_B.Value)
			{
				if (Value_B.Value < Value.Value && Value.Value < Value_A.Value)
					Output.Value = false;
				else
					Output.Value = true;
			}
		}

		DCSLogicComponent::Execute(p_dTimeStep);
	}
}