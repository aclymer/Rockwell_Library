#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/CLR.h"

namespace Rockwell_Library
{
	void CLR::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			for (int i = 0; i < 16; i++)
			{
				if (m_PropertyDictionary.TryGetValue(Property.Value + "/" + i.ToString(), l_Property))
					l_Property->ValueAsObject = false;
			}
		}

		Output.Value = Input.Value;
	}
}
