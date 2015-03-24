#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/TON.h"

namespace Rockwell_Library
{
	void TON::Execute(double p_dTimeStep)
	{
		Timebase.ValueAsObject	= Get_Property(m_Timebase_Source.Value);
		Preset.ValueAsObject	= Get_Property(m_Preset_Source.Value);

		TON::Set_Property(m_TT_Dest.Value,  TT.Value);
		TON::Set_Property(m_EN_Dest.Value,  Output.Value);
		TON::Set_Property(m_DN_Dest.Value,  DN.Value);
		TON::Set_Property(m_ACC_Dest.Value, ACC.ValueAsObject);

		Output.Value = Input.Value;
	}
}
