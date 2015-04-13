#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/JSR.h"

namespace Rockwell_Library
{
	void JSR::Execute(double p_dTimeStep)
	{
		if (Input.Value)
		{
			//DCSLogicComponent::JumpToSubroutine(Property.Value);
			
			//l_Ladder = gcnew LinkedList<DCSLogicComponent^>();
			//m_ExecutionQueue.RemoveFirst();

			if (LadderPageDictionary.TryGetValue(Property.Value, l_Ladder))
			{		
				l_NextNode = l_ThisNode->Next;

				for each (l_Component in l_Ladder)
				{
					m_ExecutionQueue.AddBefore(l_NextNode, gcnew LinkedListNode<DCSLogicComponent^>(l_Component));
				}
			}
			else
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, "Ladder not found: " + Property.Value));			
		}

		Output.Value = Input.Value;
	}
}