#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("LIM", IPS::Plugin::Visibility::VISIBLE, "Limit Test")]
	[IPS::Plugin::LibraryImage("LIM.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,150)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Comparison Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 17, 13, 17, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 17, 25, 17, "Red", false)]

	public ref class LIM : public MathBase
	{
	public:

		Rockwell_Library::LIM()
		{
			TypeDescription			= "Comparison Instructions";
			Name					= "LIM";
			Descriptor				= "Limit Test";

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

			Value.Visible			= true;
			Value.Value				= 0.0;

			Source_A.Visible		= true;
			Source_A.Value			= "Address";

			Value_A.Visible			= true;
			Value_A.Value			= 0.0;

			Source_B.Visible		= true;
			Source_B.Value			= "Address";

			Value_B.Visible			= true;
			Value_B.Value			= 0.0;
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Low Lim")]
		[IPS::Properties::GridOrder(0)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Source_A
		{
			IPS::Properties::Text% get() override
			{
				return m_Source_A;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Test")]
		[IPS::Properties::GridOrder(25)]
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
		[IPS::Properties::GridOrder(26)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Double% Value
		{
			IPS::Properties::Double% get() new
			{
				return m_Value;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("High Lim")]
		[IPS::Properties::GridOrder(30)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Source_B
		{
			IPS::Properties::Text% get() override
			{
				return m_Source_B;
			}
		}

		virtual void Activate_Compound() override
		{
		}

		virtual void Execute(double) override;

		virtual void Step(double dDt) override
		{
		}

	public:

		IPS::Properties::Double		m_Value;
	};
}