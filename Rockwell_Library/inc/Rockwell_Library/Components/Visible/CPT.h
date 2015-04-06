#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("CPT", IPS::Plugin::Visibility::VISIBLE, "Compute")]
	[IPS::Plugin::LibraryImage("CPT.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,125)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Advanced Math Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 20, 13, 20, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 88, 20, 13, 20, "Red", false)]
	[IPS::Plugin::DrawingTextProviderAttribute(DCSLogicTaskDrawingTextProvider::typeid)]			
	public ref class CPT : public MathBase
	{
	public:
		
		Rockwell_Library::CPT()
		{
			TypeDescription			= "Advanced Math Instructions";
			Name					= "CPT";
			Descriptor				= "Compute";
			
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
			Value_A.Value			= 0;

			Source_B.Visible		= true;
			Source_B.Value			= "Expression";

			Value_B.Visible			= true;
			
			re = gcnew Regex("(#)?([A-Z]{1,2})((?:\\d+){0,3}?):([0-9]+)([./])?([\\dA-Z])?");
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Dest")]
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
		[IPS::Properties::DisplayName("Expression")]
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

	private:

		Regex^							re;
		String^							l_ValToText;
		ExpressionParser				parser;
		System::Collections::Hashtable^	m_HashTable;
	};
}