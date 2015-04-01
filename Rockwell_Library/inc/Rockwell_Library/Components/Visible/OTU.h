#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("OTU", IPS::Plugin::Visibility::VISIBLE, "Output Unlatch")]
	[IPS::Plugin::LibraryImage("OTU.png")]
	[IPS::Plugin::LibrarySize(50,50)]
	[IPS::Plugin::LibraryRelativeSize(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Relay Type Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 50, 25, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 88, 50, 25, 100, "Green", false)]
	[IPS::Plugin::DrawingTextProviderAttribute(DCSLogicTaskDrawingTextProvider::typeid)]		
	public ref class OTU : public DCSLogicComponent
	{
	public:
		
		Rockwell_Library::OTU()
		{
			TypeDescription			= "Relay Type Instructions";
			Name					= "OTU";
			Descriptor				= "Output Unlatch";
			
			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
			
			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);
			
			Value.Visible			= true;
			Value.Value				= false;

			Property.Visible		= true;
		}

		//
		// Methods
		//
		
		virtual void Activate_Compound() override
		{			
		}
	
		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	};
}