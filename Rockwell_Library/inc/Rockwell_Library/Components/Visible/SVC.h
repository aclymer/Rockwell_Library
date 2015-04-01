#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

using namespace System;
using namespace IPS::Server;
using namespace DCS::Ports;

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("SVC", IPS::Plugin::Visibility::VISIBLE, "Service Communications")]
	[IPS::Plugin::LibraryImage("SVC.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,100)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Communications Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid,  -1,  0, -1, 0, 25, 13, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 25, 13, 100, "Red", false)]
		
	public ref class SVC : public DCSLogicComponent
	{
	public:
		
		Rockwell_Library::SVC()
		{
			TypeDescription			= "Communications Instructions";
			Name					= "SVC";
			Descriptor				= "Service Communications";
			
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
		}
	
		virtual void Execute(double p_dTimeStep) override;
		
		virtual void Step(double dDt) override
		{
		}

	};
}