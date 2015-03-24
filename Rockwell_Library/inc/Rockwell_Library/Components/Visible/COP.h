#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{    
	[IPS::Plugin::LibraryInfo("COP", IPS::Plugin::Visibility::VISIBLE, "Property Copy")]
	[IPS::Plugin::LibraryImage("COP.png")]
	[IPS::Plugin::LibrarySizeAttribute(200,125)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "File Manipulation Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 50, 25, 100, "Green", true, "")]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 88, 50, 25, 100, "Red", false, "")]
	
	public ref class COP : public DCSLogicComponent
	{	
	public:

		Rockwell_Library::COP()
		{
			TypeDescription			= "COP";
			Name					= "COP";
			Descriptor				= "Copy File";
				
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

			Length.Visible			= true;
			Dest.Visible			= true;
			Dest_Value.Visible		= true;
		}
			
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Destination")]
		[IPS::Properties::GridOrder(35)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Dest
		{
			IPS::Properties::Text% get()
			{
				return m_Dest;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(36)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::DataReferenceProperty% Dest_Value
		{
			IPS::Properties::DataReferenceProperty% get()
			{
				return m_Dest_Value;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Length")]
		[IPS::Properties::GridOrder(40)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Integer% Length
		{
			IPS::Properties::Integer%  get()
			{
				return m_Length;
			}
		}
		
	public:			
				
		virtual void Execute(double p_dTimeStep) override;
		
		virtual void Step(double dDt) override
		{
		}

	public:
		
		IPS::Properties::DataReferenceProperty	m_Value;
		IPS::Properties::Text					m_Dest;
		IPS::Properties::DataReferenceProperty	m_Dest_Value;
		IPS::Properties::Integer				m_Length;
		List<String^>							source_parsed;
		List<String^>							dest_parsed;
		IPS::Core::Component^					m_SourceComponent;
		IPS::Core::Component^					m_DestComponent;
		IPS::Core::Property^					m_TransferProperty;
	};    
}
