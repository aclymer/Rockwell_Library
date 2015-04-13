#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIC.h"

namespace Rockwell_Library
{
	void XIC::Execute(double p_dTimeStep)
	{
		Output.Value = false;

		if (Input.Value)
		{
			Value.ValueAsObject = Get_Property(Property.Value);

			if (Value.ValueAsObject != nullptr)
			{
				if (Value.Value == true)
					Output.Value = true;
			}
		}
	}

	void XIC::Activate_Compound()
	{		
		CloneRemoteDescription(Property.Value);
	}
}