#include "Stdafx.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"

namespace Rockwell_Library
{    
	void DCSLogicComponent::ReturnFromSubroutine()
	{
		while (m_ExecutionQueue.Count > 1 && m_ExecutionQueue.First->Value->TypeDescription != "END")
		{
			m_ExecutionQueue.RemoveFirst();
		}		
			
		m_ExecutionQueue.RemoveFirst();		
	}
	
	void DCSLogicComponent::JumpToSubroutine(String^ ladderPage)
	{
		l_Ladder = gcnew LinkedList<DCSLogicComponent^>();
		m_ExecutionQueue.RemoveFirst();

		if (LadderPageDictionary.TryGetValue(ladderPage, l_Ladder))
		{		
			LinkedListNode<DCSLogicComponent^>^ l_NextNode = m_ExecutionQueue.First;

			for each (DCSLogicComponent^ l_Component in l_Ladder)
			{
				m_ExecutionQueue.AddBefore(l_NextNode, l_Component);
			}
	
		}

		m_ExecutionQueue.First->Value->Execute(m_Project->TimeStep);
	}
	
	void DCSLogicComponent::step()
	{	
		l_Ladder = gcnew LinkedList<DCSLogicComponent^>();

		if (LadderPageDictionary.TryGetValue("U:2", l_Ladder))
		{		
			for each (l_Component in l_Ladder)
			{
				m_ExecutionQueue.AddLast(l_Component);
			}
		}
		while (m_ExecutionQueue.Count > 0)
		{
			m_ExecutionQueue.First->Value->Execute(m_Project->TimeStep);

			for each(l_BoolLink in m_ExecutionQueue.First->Value->PortByName("OutputPort")->OutLinks)
			{
				if ((bool)l_BoolLink->FromProperty->ValueAsObject)
				{
					l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Width = 2.0;
					l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Color = System::Drawing::Color::Cyan;
				}
				else
				{
					l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Width = 1.0;
					l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Color = System::Drawing::Color::Blue;
				}
			}
			m_ExecutionQueue.RemoveFirst();
		}
			
	}
}