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
				if (Dest.Value->Contains("ST"))
				{
					m_StatusText.ValueAsObject = Get_Property(Property.Value);
					Set_Property(Dest.Value, m_StatusText);
				}
				else if (!Dest.Value->Contains("C"))
				{
					source_parsed.Clear();
					dest_parsed.Clear();

					source_parsed.Add(Property.Value->Remove(Property.Value->LastIndexOfAny(splitArray) + 1));
					dest_parsed.Add(Dest.Value->Remove(Dest.Value->LastIndexOfAny(splitArray) + 1));

					source_parsed.Add(Property.Value->Substring(Property.Value->LastIndexOfAny(splitArray) + 1));
					dest_parsed.Add(Dest.Value->Substring(Dest.Value->LastIndexOfAny(splitArray) + 1));
					
					if (source_parsed[0]->StartsWith("#"))
						source_parsed[0]	= source_parsed[0]->Remove(0,1);
					
					if (dest_parsed[0]->StartsWith("#"))
						dest_parsed[0]		= dest_parsed[0]->Remove(0,1);

					Int16 start, end;
					Int16::TryParse(source_parsed[1], start);
					Int16::TryParse(dest_parsed[1], end);

					for (int i = 0; i < Length.Value; i++)
					{
						source_string		= source_parsed[0] + (start + i).ToString();
						dest_string			= dest_parsed[0] + (end + i).ToString();

						if (m_PropertyDictionary.ContainsKey(source_string))
							Dest_Value.ValueAsObject = Get_Property(source_string);
						else
							IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, "Property does not exist: " + source_string));
						
						if (m_PropertyDictionary.ContainsKey(dest_string))
							Set_Property(dest_string, Dest_Value);
						else
							IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, "Property does not exist: " + dest_string));
					}
				}
			}
			catch(Exception^ ex)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, ex->Message + ex->Source));
			}
		}

		Output.Value = Input.Value;

		DCSLogicComponent::Execute(p_dTimeStep);
	}
}
