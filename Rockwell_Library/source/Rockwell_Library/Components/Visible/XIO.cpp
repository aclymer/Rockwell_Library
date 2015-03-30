#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIO.h"

namespace Rockwell_Library
{
	void XIO::Execute(double p_dTimeStep)
	{
		Value.Value = dynamic_cast<IPS::Properties::Bool^>(l_Object);

		if (Value.Value == false)
			Output.Value = Input.Value;
		else
			Output.Value = false;		
	}

	void XIO::Activate_Compound()
	{		
		l_Object = Get_Property(Property.Value);
		CloneRemoteDescription(Property.Value);
	}
}