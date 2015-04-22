#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/FLL.h"

namespace Rockwell_Library
{
	void FLL::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			dest_string = Dest.Value;

			if (Length.Value < 1)
				Length.Value = 1;

			if (dest_string->StartsWith("#"))
				dest_string = dest_string->Replace("#","");

			currentWord.Parse(dest_string->Split(':')[1]);
			dest_string = dest_string->Split(':')[0] + ":";
			Value.ValueAsObject = Get_Property(Property.Value);

			for (int i = currentWord; i < currentWord + Length.Value - 1; i++)
			{
				Set_Property(dest_string + i.ToString(), Value);
			}
		}

		Output.Value = Input.Value;
	}
}
