#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIC.h"

namespace Rockwell_Library
{
	void XIC::Execute(double p_dTimeStep)
	{
		try
		{
			Value.ValueAsObject = Get_Property(Property.Value);
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
		}

		if (Value.ValueAsObject != nullptr)
		{
			if (Value.Value == true)
				Output.Value = Input.Value;
		}
		else
			Output.Value = false;
	}

	void XIC::Activate_Compound()
	{		
		CloneRemoteDescription(Property.Value);
	}
}