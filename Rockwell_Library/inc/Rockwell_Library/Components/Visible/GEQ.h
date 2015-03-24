#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("GEQ", IPS::Plugin::Visibility::VISIBLE, "Equal")]
	[IPS::Plugin::LibraryImage("GEQ.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,125)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Comparison Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 20, 13, 20, "Green", true, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 88, 20, 13, 20, "Red", true, "")]
		
	public ref class GEQ : public MathBase
	{
	public:
		
		Rockwell_Library::GEQ()
		{
			TypeDescription			= "GEQ";
			Name					= "GEQ";
			Descriptor				= "Equal";
			
			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
			
			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);
			
			Source_A.Visible		= true;
			Source_A.Value			= "Address";

			Value_A.Visible			= true;
			Value_A.Value			= false;

			Source_B.Visible		= true;
			Source_B.Value			= "Address";

			Value_B.Visible			= true;
			Value_B.Value			= 0;
		}

		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	};
}