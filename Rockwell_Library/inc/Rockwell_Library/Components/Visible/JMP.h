#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("JMP", IPS::Plugin::Visibility::VISIBLE, "Jump to Label")]
	[IPS::Plugin::LibraryImage("JMP.png")]
	[IPS::Plugin::LibrarySizeAttribute(50,50)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Relay Type Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 50, 25, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 50, 50, 100, "Red", false)]
	[IPS::Plugin::DrawingTextProviderAttribute(DCSLogicTaskDrawingTextProvider::typeid)]		
	public ref class JMP : public DCSLogicComponent
	{
	public:
		
		Rockwell_Library::JMP()
		{
			TypeDescription			= "Control Instructions";
			Name					= "JMP";
			Descriptor				= "Jump to Label";
			
			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
			
			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);
			
			Property.Visible		= true;
			Property.Value			= "Label (Q#:###)";
		}

		//
		// Methods
		//
		
		virtual void Activate_Compound() override
		{	
			try
			{
				m_Component = dynamic_cast<DCSLogicComponent^>(m_Project->GetComponent(Property.Value));
			}
			catch(Exception^ ex)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, "Label Not Found : " + Property.Value + ex->Message));
			}	
			if (m_Component == nullptr)
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, "Label Not Found : " + Property.Value));
		}
	
		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	private:

		DCSLogicComponent^						m_Component;
		LinkedListNode<DCSLogicComponent^>^		m_Node;
	};
}