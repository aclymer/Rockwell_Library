#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/XIC.h"

namespace Rockwell_Library
{
	void XIC::Execute(double p_dTimeStep)
	{
		IPS::Properties::Bool^ tempObject = dynamic_cast<IPS::Properties::Bool^>(Get_Property(Property.Value));
		
		if (tempObject != nullptr)
		{
			Value.Value = tempObject->Value;

			if (Value.Value == true)
				Output.Value = Input.Value;
		}
		else
			Output.Value = false;

		CloneRemoteDescription(Property.Value);
	}
}