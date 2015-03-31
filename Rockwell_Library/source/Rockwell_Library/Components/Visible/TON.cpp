#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/TON.h"

namespace Rockwell_Library
{
	void TON::Execute(double p_dTimeStep)
	{
		try
		{
			Timebase.ValueAsObject	= Get_Property(Property.Value + ".BASE");
			Preset.ValueAsObject	= Get_Property(Property.Value + ".PRE");
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, ex->Message));
		}

		TON::Set_Property(Property.Value + "/TT",  TT.Value);
		TON::Set_Property(Property.Value + "/EN",  Output.Value);
		TON::Set_Property(Property.Value + "/DN",  DN.Value);
		TON::Set_Property(Property.Value + ".ACC", ACC.ValueAsObject);
		
		Output.Value = Input.Value;
	}
}
