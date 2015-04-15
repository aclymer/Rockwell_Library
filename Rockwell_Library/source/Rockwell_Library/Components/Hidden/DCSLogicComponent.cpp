#include "Stdafx.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"

namespace Rockwell_Library
{    
	void DCSLogicComponent::ReturnFromSubroutine()
	{
		while (m_ExecutionQueue.Count > 1 && m_ExecutionQueue.First->Value->Name != "END")
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
	
	void DCSLogicComponent::step(bool l_AnimateLinks)
	{
		l_Ladder = gcnew LinkedList<DCSLogicComponent^>();

		try
		{
			if (DCSLogicTask::m_RunTestLadder.Value && LadderPageDictionary.TryGetValue("U:50", l_Ladder)) 
			{
				for each (l_Component in l_Ladder)
				{
					m_ExecutionQueue.AddLast(l_Component);
				}
			}

			if (LadderPageDictionary.TryGetValue("U:2", l_Ladder))
			{		
				for each (l_Component in l_Ladder)
				{
					m_ExecutionQueue.AddLast(l_Component);
				}
			}
		}
		catch(Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("blabla", l_Component->Identifier, ex->Message));
		}
		
		if (m_ExecutionQueue.Count > 0)
		{
			l_ThisNode = m_ExecutionQueue.First;
			
			if (l_ThisNode->Value->Input.Value)
				l_ThisNode->Value->Execute(m_Project->TimeStep);
					
			do
			{
				l_Component = l_ThisNode->Value;

				// Write Component ID to Console if true (Debuging)
				Diagnostics::Debug::WriteLineIf(DCSLogicTask::m_ExecID.Value, l_Component->Identifier->Value);
			/*
				if (l_Component->Input.Value)
				{
				*/
					l_Component->Execute(m_Project->TimeStep);

					try
					{
						for each(l_BoolLink in l_Component->PortByName("OutputPort")->OutLinks)
						{
							if (l_AnimateLinks && (bool)l_BoolLink->FromProperty->ValueAsObject)
							{
								l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Width = 2.0;
								l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Color = System::Drawing::Color::Cyan;
							}
							else
							{
								l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Width = 1.0;
								l_BoolLink->DrawingDatas->GetLinkDrawingDatas()[0]->Color = System::Drawing::Color::Blue;
							}

							l_BoolLink->GetPropertyPair()->TransferProperties();
						}
					}
					catch(Exception^ ex)
					{
						IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("blabla", l_BoolLink->Identifier, ex->Message));
					}
				//}

				l_ThisNode = l_ThisNode->Next;

			} while (l_ThisNode != nullptr);

			m_ExecutionQueue.Clear();
		}

		if (m_PropertyDictionary.TryGetValue("S:1/15", l_Property))
			(l_Property->ValueAsObject == (Object^)false ? true : l_Property->ValueAsObject = (Object^)false);
	}
}