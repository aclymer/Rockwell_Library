#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("OTL", IPS::Plugin::Visibility::VISIBLE, "Output Latch")]
	[IPS::Plugin::LibraryImage("OTL.png")]
	[IPS::Plugin::LibrarySizeAttribute(50,50)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Relay Type Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 50, 25, 100, "Green", false, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 88, 50, 25, 100, "Red", false, "")]
		
	public ref class OTL : public DCSLogicComponent
	{
	public:
		
		Rockwell_Library::OTL()
		{
			TypeDescription			= "OTL";
			Name					= "OTL";
			Descriptor				= "Output Latch";
			
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
		
		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	};
}