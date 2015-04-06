#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/MOV.h"

namespace Rockwell_Library
{
	void MOV::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			try
			{
				if (Dest.Value->Contains("ST"))
					CopyPropertyDescription(Property.Value, Dest.Value);					
				else if (!Dest.Value->Contains("C"))
					Set_Property(Dest.Value, Value);	
				else
				{
					Value.Value = double::Parse(Property.Value);
					Set_Property(Dest.Value, Value);
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
