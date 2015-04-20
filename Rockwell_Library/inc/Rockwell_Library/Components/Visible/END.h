#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"
#include "Rockwell_Library/Links/DCSLogicLink.h"

using namespace System;
using namespace IPS::Server;
using namespace DCS::Ports;

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("END", IPS::Plugin::Visibility::VISIBLE, "End Instruction")]
	[IPS::Plugin::LibraryImage("END.png")]
	[IPS::Plugin::LibrarySizeAttribute(50,50)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "End Instruction")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid,  -1,  0, -1, 0, 50, 25, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 50, 25, 100, "Red", false)]

	public ref class END : public DCSLogicComponent
	{
	public:

		Rockwell_Library::END()
		{
			TypeDescription			= "End Instruction";
			Name					= "END";
			Descriptor				= "End Instruction";

			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);

			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Input);
		}

		//
		// Methods
		//

		virtual void Activate_Compound() override
		{
			IPS::Core::DrawingPage^ l_Page = dynamic_cast<IPS::Core::DrawingPage^>(m_Project->FindPagesWithComponent(this->Identifier)[0]);

			for each (IPS::Core::Component^ r_Component in l_Page->Components)
			{
				l_Component = dynamic_cast<DCSLogicComponent^>(r_Component);

				if (l_Component != nullptr && l_Component->Name == "Rung" && l_Component->InputPort->IsConnected == false)
				{
					if (LadderPageDictionary.ContainsKey(l_Page->UserDescription->Value))
						LadderPageDictionary.Remove(l_Page->UserDescription->Value);

					LadderPageDictionary.Add(l_Page->UserDescription->Value, gcnew LinkedList<DCSLogicComponent^>(PopulateRungList(l_Component)));
				}
			}

			// Add Drawing Page Links to LinkList
			for each (IPS::Core::Link^ l_Link in l_Page->Links)
			{
				try
				{
					l_BoolLink = dynamic_cast<DCSLogicLink^>(l_Link);
					if (l_BoolLink != nullptr)
					{
						if (l_BoolLink->FromProperty == nullptr)
							IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("Dangling Link", l_BoolLink->Identifier, "Link StartPort is not connected."));
						else if (l_BoolLink->ToProperty == nullptr)
							IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("Dangling Link", l_BoolLink->Identifier, "Link EndPort is not connected."));
						else
							l_LinkList.AddLink(l_BoolLink);
					}
				}
				// Catch any dangling links
				catch(Exception^ ex)
				{
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, ((ElementImpl^) ex->Data)->Identifier, "Unknown Link Error occurred."));
				}
			}
		}

		virtual void Execute(double p_dTimeStep) override;

		virtual void Step(double dDt) override
		{
		}

	private:

		DCSLogicComponent^						l_Component;
		DCSLogicLink^							l_BoolLink;
	};
}