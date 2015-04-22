#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/PID.h"

namespace Rockwell_Library
{
	void PID::Execute(double p_dTimeStep)
	{
		Scaled_PV.Value				= (PV.Value * m_Slope.Value) + m_Offset.Value;
		CV_Output.Value				= (CV.Value * m_Slope.Value) + m_Offset.Value;
		
		if (CV_Output.Value > Omax.Value)
		{
			if (OL.Value)
				CV.Value = (Smax.Value - Smin.Value) * Omax.Value / 100;
			UL.Value = true;
			LL.Value = false;
		}
		else if (CV_Output.Value < Omin.Value)
		{
			if (OL.Value)
				CV.Value = (Smax.Value - Smin.Value) * Omin.Value / 100;
			UL.Value = false;
			LL.Value = true;
		}
		else
		{
			UL.Value = false;
			LL.Value = false;
		}
		
		Set_Property(CV_Source.Value, CV);
		Set_Property(m_BaseElement.Value + (m_BaseWord + 15).ToString(), SE);

		EN.Value					= Input.Value;
		Output.Value				= Input.Value;

		Set_Property(Property.Value, m_ControlBlock);
		DCSLogicComponent::Execute(p_dTimeStep);
	}
}