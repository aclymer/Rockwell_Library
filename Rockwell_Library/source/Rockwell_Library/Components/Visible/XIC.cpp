#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIC.h"

namespace Rockwell_Library
{
	void XIC::Execute(double p_dTimeStep)
	{
		Value.Value = dynamic_cast<IPS::Properties::Bool^>(l_Object);

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
		l_Object = Get_Property(Property.Value);
		CloneRemoteDescription(Property.Value);	
	}
}