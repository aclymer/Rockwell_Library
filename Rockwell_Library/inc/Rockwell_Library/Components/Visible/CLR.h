#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{    
	[IPS::Plugin::LibraryInfo("CLR", IPS::Plugin::Visibility::VISIBLE, "Clear")]
	[IPS::Plugin::LibraryImage("CLR.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,100)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Math Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 25, 13, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 25, 25, 100, "Red", false)]
	[IPS::Plugin::DrawingTextProviderAttribute(DCSLogicTaskDrawingTextProvider::typeid)]		
	public ref class CLR : public DCSLogicComponent
	{	
	public:

		Rockwell_Library::CLR()
		{
			TypeDescription			= "Math Instructions";
			Name					= "CLR";
			Descriptor				= "Clear";
				
			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
			
			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);
			
			Value.Visible			= true;
			Value.Value				= 0;

			Property.Visible		= true;
			Property.Value			= "Address";
		}
			
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Dest")]
		[IPS::Properties::GridOrder(100)]
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
		[IPS::Properties::GridOrder(140)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Integer% Value
		{
			IPS::Properties::Integer% get() new
			{
				return m_Value;
			}
		}
		
	public:			
			
		virtual void Activate_Compound() override
		{			
		}
		
		virtual void Execute(double p_dTimeStep) override;
		
		virtual void Step(double dDt) override
		{
		}

	public:
		
		IPS::Properties::Integer		m_Value;
		IPS::Core::Property^			l_Property;
	};    
}
