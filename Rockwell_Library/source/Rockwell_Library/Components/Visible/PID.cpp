#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/PID.h"

namespace Rockwell_Library
{
	void PID::Activate_Compound()
	{
		m_BaseElement		= Property.Value->Split(':')[0] + ":";
		m_BaseWord.Parse(Property.Value->Split(':')[1]);

		Value.ValueAsObject	= Get_Property(Property.Value);
		SP.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 2 ).ToString());	// Setpoint
		Kc.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 3 ).ToString());	// Controller Gain
		Ti.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 4 ).ToString());	// Reset
		Td.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 5 ).ToString());	// Rate
		FFb.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 6 ).ToString());	// Feed Forward Bias
		Smax.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 7 ).ToString());	// Setpoint Max
		Smin.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 8 ).ToString());	// Setpoint Min
		DB.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 9 ).ToString());	// Deadband
		//SP.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 10).ToString());	// INTERNAL USE - DO NOT CHANGE (??)
		Omax.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 11).ToString());	// Output Max (CV%)
		Omin.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 12).ToString());	// Output Min (CV%)
		LU.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 13).ToString());	// Loop Update
		sPV.ValueAsObject	= Get_Property(m_BaseElement + (m_BaseWord + 14).ToString());	// Scaled PV
	}

	void PID::Execute(double p_dTimeStep)
	{
		Output.Value = Input.Value;

		DCSLogicComponent::Execute(p_dTimeStep);
	}

	void PID::Step(double dDt)
	{
		// Equation: Output = Kc [Error + 1/Ti (E)dt + Td D (PV)/df] + bias

		m_Error.Value = (CM.Value ? PV.Value - SP.Value : SP.Value - PV.Value);
	}
}