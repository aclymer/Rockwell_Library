#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/FLL.h"

namespace Rockwell_Library
{
	void FLL::Execute(double p_dTimeStep)
	{
		if (Property.Value->StartsWith("#"))
			Property.Value = Property.Value->Remove(0,1);
		if (Dest.Value->StartsWith("#"))
			Dest.Value = Dest.Value->Remove(0,1);

		if (Input.Value)
		{
			ParseAddress(dest_parsed, Dest.Value);
			Value.Value = dynamic_cast<IPS::Properties::Double^>(Get_Property(Property.Value))->Value;
			for (int i = 0; i < Length.Value; i++)
			{
				int j = 1;
				for (; j < dest_parsed.Count - 1; j++)
				{
					dest_parsed[0] += dest_parsed[j];
				}
				Int16 currentWord;
				if (Int16::TryParse(dest_parsed[++j], currentWord))
				{
					dest_parsed[0] += (currentWord + i).ToString();
					Set_Property(dest_parsed[0], Value.Value);
				}
			}

		}

		Output.Value = Input.Value;
	}
}
