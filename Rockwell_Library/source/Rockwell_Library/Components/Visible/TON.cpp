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

		Set_Property(Property.Value + "/TT",  TT);
		Set_Property(Property.Value + "/EN",  Output);
		Set_Property(Property.Value + "/DN",  DN);
		Set_Property(Property.Value + ".ACC", ACC);
		
		Output.Value = Input.Value;

		IPS::Plugin::DrawingTextEventArgs().Empty;
	}
}
