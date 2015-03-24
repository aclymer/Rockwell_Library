#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("PID", IPS::Plugin::Visibility::VISIBLE, "Proportional/Integral/Derivative")]
	[IPS::Plugin::LibraryImage("PID.png")]
	[IPS::Plugin::LibrarySizeAttribute(250,150)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "PID Control")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 17, 10, 17, "Green", true, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 90, 17, 10, 17, "Red", true, "")]
		
	public ref class PID : public MathBase
	{
	public:
		
		Rockwell_Library::PID()
		{
			TypeDescription			= "PID";
			Name					= "PID";
			Descriptor				= "Proportional/Integral/Derivative";
			
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
			Property.Value			= "Address";

			Value_A.Visible			= true;
			Value_A.Value			= 0;

			Source_A.Visible		= true;
			Source_A.Value			= "Address";

			Source_B.Visible		= true;
			Source_B.Value			= "Address";

			Value_B.Visible			= true;
			Value_B.Value			= 0;
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Control Block")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Source_A
		{
			IPS::Properties::Text% get() override
			{
				return m_Source_A;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Process Variable")]
		[IPS::Properties::GridOrder(30)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text%  Source_B
		{
			IPS::Properties::Text%  get() override
			{
				return m_Source_B;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Control Variable")]
		[IPS::Properties::GridOrder(166)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Property
		{
			IPS::Properties::Text% get() override
			{
				return m_Property;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Control Block Length")]
		[IPS::Properties::GridOrder(200)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Integer% Length
		{
			IPS::Properties::Integer% get()
			{
				return m_Length;
			}
		}
		
		virtual void Execute(double) override;		
		
		virtual void Step(double dDt) override
		{
		}

	public:

		IPS::Properties::Integer	m_Length;
	};
}