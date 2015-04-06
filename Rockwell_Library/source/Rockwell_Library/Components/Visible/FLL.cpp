#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/FLL.h"

namespace Rockwell_Library
{
	void FLL::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			if (Length.Value < 1)
				Length.Value = 1;

			ParseAddress(dest_parsed, Dest.Value);
			Value.ValueAsObject = Get_Property(Property.Value);
			dest_string = gcnew String("");

			for (int i = 0; i < Length.Value; i++)
			{
				int j = 0;
				for (; j < dest_parsed.Count - 1; j++)
				{
					dest_string += dest_parsed[j];
				}
				Int16 currentWord;
				if (Int16::TryParse(dest_parsed[++j], currentWord))
				{
					dest_string += (currentWord + i).ToString();
					Set_Property(dest_string, Value);
				}
			}

		}

		Output.Value = Input.Value;
	}
}
