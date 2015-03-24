#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

using namespace System;
using namespace IPS::Server;
using namespace DCS::Ports;

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("Node", IPS::Plugin::Visibility::VISIBLE, "Branch End")]
	[IPS::Plugin::LibraryImage("Node.png")]
	[IPS::Plugin::LibrarySizeAttribute(50,50)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Branching Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid,  -1,  0, -1, 50, 50, 100, 100, "Green", false, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 50, 50, 100, 100, "Red", false, "")]
		
	public ref class Node : public DCSLogicComponent
	{
	public:
		
		Rockwell_Library::Node()
		{
			TypeDescription			= "Node";
			Name					= "Node";
			Descriptor				= "Branch End";
			
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
				
		virtual void Execute(double p_dTimeStep) override
		{
		}
		
		virtual void Step(double dDt) override
		{
		}

	};
}