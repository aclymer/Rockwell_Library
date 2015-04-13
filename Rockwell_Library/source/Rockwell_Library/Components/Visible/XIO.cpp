#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIO.h"

namespace Rockwell_Library
{
	void XIO::Execute(double p_dTimeStep)
	{
		Output.Value = false;

		if (Input.Value)
		{
			Value.ValueAsObject = Get_Property(Property.Value);

			if (Value.ValueAsObject != nullptr)
			{
				if (Value.Value == false)
					Output.Value = true;
			}
		}
	}

	void XIO::Activate_Compound()
	{		
		CloneRemoteDescription(Property.Value);
	}
}