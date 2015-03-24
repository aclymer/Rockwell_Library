#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIC.h"

namespace Rockwell_Library
{
	void XIC::Execute(double p_dTimeStep)
	{
		Value.Value = (bool) Get_Property(Property.Value);
		
		if (Value.ValueAsObject != nullptr)
		{
			if (Value.Value == true)
				Output.Value = Input.Value;
		}
		else
			Output.Value = false;

		CloneRemoteDescription(Property.Value);
	}
}