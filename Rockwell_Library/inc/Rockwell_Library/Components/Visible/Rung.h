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
	[IPS::Plugin::LibraryInfo("Rung", IPS::Plugin::Visibility::VISIBLE, "Start Of Rung")]
	[IPS::Plugin::DrawingTextProvider(DCSLogicTaskDrawingTextProvider::typeid)]
	[IPS::Plugin::LibraryImage("Rung.png")]
	[IPS::Plugin::LibrarySize(100,50)]
	[IPS::Plugin::LibraryCategory("Ladder Logic")]
	[IPS::Plugin::Port("InputPort",	 Bool::BoolInputPort::typeid,  1,  0,  1, 50,   0, 50,  25, "Green", false, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 50, 25, 100, "Red",   false, "")]
	[IPS::Plugin::Port("RungPort",	 Bool::BoolOutputPort::typeid, 0,  1,  1, 50, 100, 50,  50, "Red",   false, "")]
		
	public ref class Rung : public DCSLogicComponent
	{
	public:

		Rockwell_Library::Rung()
		{

			TypeDescription					= "Rung";
			Name							= "Rung";
			Descriptor						= "Rung";
						
			InputPort						= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);

			Output.Visible					= true;
			Output.Value					= false;
			OutputPort						= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Input);

			Rung_Port.Visible				= true;
			Rung_Port.Value					= false;
			RungPort						= dynamic_cast<Bool::BoolOutputPort^>(PortByName("RungPort"));
			RungPort->SetAssociatedProperty(%m_Input);
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Energize")]
		[IPS::Properties::GridOrder(0)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		virtual property IPS::Properties::Bool% Output
		{			
			IPS::Properties::Bool% get() override
			{
				if (InputPort != nullptr && InputPort->IsConnected)
					m_Input = dynamic_cast<IPS::Properties::Bool^>(InputPort->AssociatedProperty);
					
				return m_Input;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("RungPort")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		virtual property IPS::Properties::Bool% Rung_Port
		{			
			IPS::Properties::Bool% get()
			{
				return m_Input;
			}
		}

		virtual System::Void InitProperties() override
		{
			IPS::Plugin::ComponentBase::InitProperties();
		}

		virtual void Execute(double) override;		
		
		virtual void Step(double dDt) override
		{
		}

	private:

		DCSOutputPortBase^							RungPort;
	};
}