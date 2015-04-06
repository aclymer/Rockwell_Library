#include "stdafx.h"
#include "Rockwell_Library/Components/Visible/JMP.h"

namespace Rockwell_Library
{
	void JMP::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			m_Component = dynamic_cast<DCSLogicComponent^>(m_Project->GetComponent(Property.Value));

			if (m_Component != nullptr)
				m_Node = m_ExecutionQueue.Find(m_Component);

			if (m_Node != nullptr)
				l_ThisNode = m_Node;
		}

		Output.Value = Input.Value;
	}
}