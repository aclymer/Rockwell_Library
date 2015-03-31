#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIO.h"

namespace Rockwell_Library
{
	void XIO::Execute(double p_dTimeStep)
	{
		try
		{
			Value.ValueAsObject = Get_Property(Property.Value);
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
		}

		if (Value.Value == false)
			Output.Value = Input.Value;
		else
			Output.Value = false;		
	}

	void XIO::Activate_Compound()
	{		
		CloneRemoteDescription(Property.Value);
	}
}