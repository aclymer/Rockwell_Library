#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/MOV.h"

namespace Rockwell_Library
{
	void MOV::Execute(double p_dTimeStep)
	{
		System::Double^ value = gcnew double;
		bool constant = System::Double::TryParse(Property.Value, *value);

		if (Property.Value->StartsWith("#"))
			Property.Value = Property.Value->Remove(0,1);
		if (Dest.Value->StartsWith("#"))
			Dest.Value = Dest.Value->Remove(0,1);

		if (!constant)
		{
			ParseAddress(source_parsed, Property.Value);
			m_SourceComponent	= this->m_Project->GetComponent(Property.Value);
		}

		if (Input.Value)
		{
			if (constant)
				Set_Property(Dest.Value, dynamic_cast<System::Object^>(value));

			else 
			{
				ParseAddress(dest_parsed, Dest.Value);

				if (dest_parsed[1] == "ST")
					this->m_Project->GetComponent(Dest.Value)->UserDescription->Value = m_SourceComponent->UserDescription->Value;

				else if (dest_parsed[1] != "C")
					Set_Property(Dest.Value, Get_Property(Property.Value));	
			}
		}

		Output.Value = Input.Value;
	}
}
