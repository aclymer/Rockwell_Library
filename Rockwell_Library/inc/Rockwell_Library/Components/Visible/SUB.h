#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("SUB", IPS::Plugin::Visibility::VISIBLE, "Add")]
	[IPS::Plugin::LibraryImage("SUB.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,125)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Math Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 20, 13, 20, "Green", true, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 88, 20, 13, 20, "Red", true, "")]
		
	public ref class SUB : public MathBase
	{
	public:
		
		Rockwell_Library::SUB()
		{
			TypeDescription			= "SUB";
			Name					= "SUB";
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
		[IPS::Properties::DisplayName("Source A")]
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