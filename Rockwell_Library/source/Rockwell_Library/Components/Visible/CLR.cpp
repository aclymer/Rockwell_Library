#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CLR.h"

namespace Rockwell_Library
{
	void CLR::Execute(double p_dTimeStep)
	{
		try
		{
			Value.ValueAsObject = Get_Property(Property.Value);
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
		}

		if (Input.Value)
		{
			Value.Value = 0;
			Set_Property(Property.Value, Value.ValueAsObject);
		}

		Output.Value = Input.Value;
	}
}
