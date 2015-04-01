#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CPT.h"
//#include "Rockwell_Library/Components/Hidden/Equation.h"

namespace Rockwell_Library
{
	void CPT::Execute(double p_dTimeStep)
	{
		l_ValToText = Source_B.Value;

		for each (System::Text::RegularExpressions::Match^ l_thisMatch in re->Matches(Source_B.Value))
		{
			Value_B.ValueAsObject = Get_Property(l_thisMatch->Value);
			l_ValToText = l_ValToText->Replace(l_thisMatch->Value, Value_B.Value.ToString());
		}

		l_ValToText = l_ValToText->Replace("|", "/");
	
		try
		{
			Value_B.Value = parser.Parse(l_ValToText, m_HashTable);
			Set_Property(Source_A.Value, Value_B);
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
		}

		Output.Value			= Input.Value;
	}
}