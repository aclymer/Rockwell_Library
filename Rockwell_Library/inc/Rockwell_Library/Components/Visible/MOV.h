#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{    
	[IPS::Plugin::LibraryInfo("MOV", IPS::Plugin::Visibility::VISIBLE, "Property Copy")]
	[IPS::Plugin::LibraryImage("MOV.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,120)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Move and Logical Instructions")]
	[IPS::Plugin::Port("InputPort",	 Bool::BoolInputPort::typeid, -1,  0, -1,   0, 20, 13, 20, "Green", true, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 20, 13, 20, "Red", true, "")]
			
	public ref class MOV : public DCSLogicComponent
	{	
	public:

		Rockwell_Library::MOV()
		{
			TypeDescription			= "MOV";
			Name					= "MOV";
			Descriptor				= "Move Word";
				
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

			Dest_Value.Visible		= true;
			Dest.Visible			= true;	
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Trigger")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Inputs"})]
		virtual property IPS::Properties::Bool% Input
		{
			IPS::Properties::Bool% get() override
			{
				return m_Input;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Source")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Property
		{
			IPS::Properties::Text% get() override
			{
				return m_Property;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Destination")]
		[IPS::Properties::GridOrder(25)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text%  Dest
		{
			IPS::Properties::Text%  get()
			{
				return m_Dest;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(35)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::DataReferenceProperty%  Dest_Value
		{
			IPS::Properties::DataReferenceProperty%  get()
			{
				return m_Dest_Value;
			}
		}
		
	public:

		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	public:
		      
		IPS::Properties::DataReferenceProperty	m_Value; 
		IPS::Properties::DataReferenceProperty	m_Dest_Value;       
		IPS::Properties::Text					m_Dest;
		List<String^>							source_parsed;
		List<String^>							dest_parsed;
		IPS::Core::Component^					m_SourceComponent;
		IPS::Core::Component^					m_DestComponent;
	};    
}
