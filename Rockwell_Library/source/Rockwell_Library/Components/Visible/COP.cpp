#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/COP.h"

namespace Rockwell_Library
{
	void COP::Execute(double p_dTimeStep)
	{
		if (Length.Value < 1)
			Length.Value = 1;
		else if (Length.Value > 128)
			Length.Value = 128;

		if (Input.Value)
		{
			try
			{
				ParseAddress(source_parsed, Property.Value);
				ParseAddress(dest_parsed, Dest.Value);

				if (Dest.Value->Contains("ST"))
					m_Project->GetComponent(Dest.Value)->UserDescription->Value = m_Project->GetComponent(Property.Value)->UserDescription->Value;
			
				else if (!Dest.Value->Contains("C"))
				{
					source_string = gcnew String("");
					dest_string = gcnew String("");
					Int16 start, end;
					Int16::TryParse(source_parsed[4], start);
					Int16::TryParse(dest_parsed[4], end);
					for (int i = 0; i < Length.Value; i++)
					{
						source_parsed[4] = (start + i).ToString();
						for (int j = 0; j < source_parsed.Count; j++)
							source_string	+= source_parsed[j];

						dest_parsed[4] = (end + i).ToString();
						for (int k = 0; k < dest_parsed.Count; k++)
							dest_string		+= dest_parsed[k];

						Dest_Value.ValueAsObject = Get_Property(source_string);
						Set_Property(dest_string, Dest_Value);
					}
				}
			}
			catch(Exception^ ex)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
			}
		}

		Output.Value = Input.Value;
	}
}
