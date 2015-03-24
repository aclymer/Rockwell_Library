#include "Stdafx.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"

namespace Rockwell_Library
{    
	void DCSLogicComponent::ReturnFromSubroutine()
	{
	}
	
	void DCSLogicComponent::JumpToSubroutine(String^ ladderPage)
	{
		l_Ladder = gcnew LinkedList<DCSLogicComponent^>;

		if (LadderPageDictionary.TryGetValue(ladderPage, l_Ladder))
		{		
			LinkedListNode<DCSLogicComponent^>^ l_NextNode = m_ExecutionQueue.First;

			for each (l_Component in l_Ladder)
			{
				m_ExecutionQueue.AddBefore(l_NextNode, l_Component);
			}
		}
	}
	
	void DCSLogicComponent::step()
	{		
		count = 0;
		l_Ladder = gcnew LinkedList<DCSLogicComponent^>;

		if (LadderPageDictionary.TryGetValue("U:2", l_Ladder))
		{		
			for each (l_Component in l_Ladder)
			{
				m_ExecutionQueue.AddLast(l_Component);
			}
		}

		while (m_ExecutionQueue.Count > 0)
		{
			l_Component = m_ExecutionQueue.First->Value;
			m_ExecutionQueue.RemoveFirst();
			l_Component->ReadInputs();
			l_Component->Execute(m_Project->TimeStep);
			l_Component->WriteOutputs();
			Diagnostics::Debug::WriteLine(l_Component->Identifier->ToString() + " Executed: " + count.ToString());
			count++;
			for each(l_BoolLink in l_Component->PortByName("OutputPort")->OutLinks)
			{
				Diagnostics::Debug::WriteLine(l_BoolLink->Enable.ToString());
				l_Value.ValueAsObject = l_BoolLink->GetPropertyFromPropID("From Property")->ValueAsObject;
				if (l_Value.Value == true)
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
		}		
	}
}