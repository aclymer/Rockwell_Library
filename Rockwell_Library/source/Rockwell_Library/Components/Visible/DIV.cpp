#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/DIV.h"

namespace Rockwell_Library
{
	void DIV::Execute(double p_dTimeStep)
	{
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

			Value.Value = Value_A.Value / Value_B.Value;
			Set_Property(Property.Value, Value);
		}

		Output.Value = Input.Value;
		DCSLogicComponent::Execute(p_dTimeStep);
	}
}