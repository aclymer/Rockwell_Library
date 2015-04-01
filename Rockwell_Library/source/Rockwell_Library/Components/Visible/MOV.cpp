#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/MOV.h"

namespace Rockwell_Library
{
	void MOV::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			if (ParseAddress(dest_parsed, Dest.Value)) 
			{
				if (dest_parsed[1] == "ST")
					CopyPropertyDescription(Property.Value, Dest.Value);					
				else if (dest_parsed[1] != "C")
					Set_Property(Dest.Value, Value);				
			}
			else
			{
				Value.Value = double::Parse(Property.Value);
				Set_Property(Dest.Value, Value);
			}
		}

		Output.Value = Input.Value;
	}
}
