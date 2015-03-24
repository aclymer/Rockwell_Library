#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("ADD", IPS::Plugin::Visibility::VISIBLE, "Add")]
	[IPS::Plugin::LibraryImage("ADD.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,150)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Math Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 17, 13, 17, "Green", true, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 88, 17, 13, 17, "Red", true, "")]
		
	public ref class ADD : public MathBase
	{
	public:
		
		Rockwell_Library::ADD()
		{
			TypeDescription			= "ADD";
			Name					= "ADD";
			Descriptor				= "Add";
			
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
		[IPS::Properties::DisplayName("Destination")]
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
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(200)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Double% Value
		{
			IPS::Properties::Double% get() new
			{
				return m_Value;
			}
		}
		
		virtual void Execute(double) override;		
		
		virtual void Step(double dDt) override
		{
		}

	public:

		IPS::Properties::Text		m_Source_A;
		IPS::Properties::Double		m_Value;
		IPS::Properties::Double		m_Value_A;
		IPS::Properties::Double		m_Value_B;
	};
}