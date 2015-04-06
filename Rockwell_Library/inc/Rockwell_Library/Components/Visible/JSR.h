#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"

using namespace System;
using namespace IPS::Server;
using namespace DCS::Ports;

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("JSR", IPS::Plugin::Visibility::VISIBLE, "Jump To Subroutine")]
	[IPS::Plugin::DrawingTextProvider(DCSLogicTaskDrawingTextProvider::typeid)]
	[IPS::Plugin::LibraryImage("JSR.png")]
	[IPS::Plugin::LibrarySize(200,75)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Control Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 33, 13, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 33, 13, 100, "Red", false)]
		
	public ref class JSR : public DCSLogicComponent
	{
	public:

		Rockwell_Library::JSR()
		{			
			TypeDescription				= "Control Instructions";
			Name						= "JSR";
			Descriptor					= "Jump To Subroutine";
			
			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
			
			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);
			
			Property.Visible		= true;
			Property.Value			= "Address";
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Subroutine")]
		[IPS::Properties::GridOrder(101)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Component"})]
		virtual property IPS::Properties::Text% Property
		{
			IPS::Properties::Text% get() override
			{
				return m_Property;
			}
		}
		
		virtual void Activate_Compound() override
		{			
		}
	
		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	private:

		DCSLogicComponent^						l_Component;
		LinkedListNode<DCSLogicComponent^>^		l_NextNode;
	};
}