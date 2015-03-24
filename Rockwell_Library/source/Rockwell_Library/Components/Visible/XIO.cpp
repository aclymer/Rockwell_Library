#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIO.h"

namespace Rockwell_Library
{
	void XIO::Execute(double p_dTimeStep)
	{
		Value.Value = (bool) Get_Property(Property.Value);

		if (Value.Value == false)
			Output.Value = Input.Value;
		else
			Output.Value = false;
		
		CloneRemoteDescription(Property.Value);
	}
}