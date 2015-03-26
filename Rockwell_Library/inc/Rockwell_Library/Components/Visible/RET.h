#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("RET", IPS::Plugin::Visibility::VISIBLE, "Return From Subroutine")]
	[IPS::Plugin::DrawingTextProvider(DCSLogicTaskDrawingTextProvider::typeid)]
	[IPS::Plugin::LibraryImage("RET.png")]
	[IPS::Plugin::LibrarySize(200,50)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Control Instructions")]
	[IPS::Plugin::Port("InputPort",  Bool::BoolInputPort::typeid, -1,  0, -1, 0,   50, 6, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 50, 13, 100, "Red", false)]
		
	public ref class RET : public DCSLogicComponent
	{
	public:

		Rockwell_Library::RET()
		{			
			TypeDescription				= "RET";
			Name						= "RET";
			Descriptor					= "Return From Subroutine";
			
			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
			
			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);			
		}

		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	};
}