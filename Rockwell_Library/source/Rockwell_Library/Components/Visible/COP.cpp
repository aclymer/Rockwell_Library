#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/COP.h"

namespace Rockwell_Library
{
	void COP::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			ParseAddress(source_parsed, Property.Value);
			ParseAddress(dest_parsed, Dest.Value);

			if (dest_parsed[1] == "ST")
				m_Project->GetComponent(Dest.Value)->UserDescription->Value = m_Project->GetComponent(Property.Value)->UserDescription->Value;
			
			else if (dest_parsed[1] != "C")
			{
				Int16 start, end;
				Int16::TryParse(source_parsed[3], start);
				Int16::TryParse(dest_parsed[3], end);
				String^ source_string;
				String^ dest_string;
				for (int i = 0; i < Length.Value; i++)
				{
					source_string	= source_parsed[1] + source_parsed[2] + ":" + (start + i).ToString() + source_parsed[4] + (source_parsed.Count < 6 ? "" : source_parsed[5]);
					dest_string		= dest_parsed[1]   + dest_parsed[2]   + ":" + (end + i).ToString() + dest_parsed[4] + (dest_parsed.Count < 6 ? "" : dest_parsed[5]);

					Set_Property(dest_string, *dynamic_cast<IPS::Core::Property^>(Get_Property(source_string)));
				}
			}
		}

		Output.Value = Input.Value;
	}
}
