#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CPT.h"

namespace Rockwell_Library
{
	void CPT::Execute(double p_dTimeStep)
	{
		Value_A.ValueAsObject	= Get_Property(Source_A.Value);

		if (Input.Value)
		{
			try
			{
				l_ValToText			= Source_B.Value->Replace(" ", "");
				Regex^ re			= gcnew Regex("(#)?([A-Z]{1,2})((?:\\d+){0,3}?):([0-9]+)([./]{0,1})([\\dA-Z]{0,4})");
				MatchCollection^ l_TheseMatches = re->Matches(l_ValToText);

				for each (Match^ l_thisMatch in l_TheseMatches)
				{
					if (l_thisMatch->Value != nullptr)
					{
						Value_B.ValueAsObject = Get_Property(l_thisMatch->Value);
						l_ValToText = l_ValToText->Replace(l_thisMatch->Value, Value_B.Value.ToString());
					}
				}

				if (l_ValToText->Contains("["))
				{
					l_ValToText = l_ValToText->Replace("[","");
					l_ValToText = l_ValToText->Replace("]","");
					l_TheseMatches = re->Matches(l_ValToText);

					for each (Match^ l_thisMatch in l_TheseMatches)
					{
						if (l_thisMatch->Value != nullptr)
						{
							Value_B.ValueAsObject = Get_Property(l_thisMatch->Value);
							l_ValToText = l_ValToText->Replace(l_thisMatch->Value, Value_B.Value.ToString());
						}
					}
				}

				l_ValToText			= l_ValToText->Replace("|", "/");	
				Value_B.Value		= parser.Parse(l_ValToText, m_HashTable);

				if (Value_B.Value.IsNaN(Value_B.Value))
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementWarning("Division by Zero.", this->Identifier, "NaN from Division by Zero."));
			}
			catch(Exception^ ex)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, ex->Message + ex->Source));
			}
			
			Set_Property(Source_A.Value, Value_B);
		}

		Output.Value				= Input.Value;
		DCSLogicComponent::Execute(p_dTimeStep);
	}
}