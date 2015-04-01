#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/DIV.h"

namespace Rockwell_Library
{
	void DIV::Execute(double p_dTimeStep)
	{
		try
		{
			Value.Value		= dynamic_cast<IPS::Properties::Double^>(Get_Property(Property.Value))->Value;
			Value_A.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_A.Value))->Value;
			Value_B.Value	= dynamic_cast<IPS::Properties::Double^>(Get_Property(Source_B.Value))->Value;
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
		}

		if (Input.Value == true)
		{
			Value.Value = Value_A.Value / Value_B.Value;
			Set_Property(Property.Value, Value);
		}

		Output.Value = Input.Value;
	}
}