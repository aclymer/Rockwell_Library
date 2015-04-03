#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("LBL", IPS::Plugin::Visibility::VISIBLE, "Label")]
	[IPS::Plugin::LibraryImage("LBL.png")]
	[IPS::Plugin::LibrarySizeAttribute(50,50)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Control Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 50, 25, 100, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 50, 50, 100, "Red", false)]
	[IPS::Plugin::DrawingTextProviderAttribute(DCSLogicTaskDrawingTextProvider::typeid)]		
	public ref class LBL : public DCSLogicComponent
	{

	public:
		
		Rockwell_Library::LBL()
		{
			TypeDescription			= "Control Instructions";
			Name					= "LBL";
			Descriptor				= "Label";
			
			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
			
			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);
			
			Property.Visible		= true;
			Property.Value			= this->Identifier->Value;
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Label")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Property
		{
			IPS::Properties::Text% get() override
			{
				return m_Property;
			}
			void set(IPS::Properties::Text% value)
			{
				try
				{
					if (this->Identifier->Value != value.Value)
						this->Identifier->Value = value.Value;
				}
				catch(Exception^ ex)
				{
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, this->Identifier, "Label Already Exists : " + value.Value + ex->Message));
				}
				
				m_Property.Value = this->Identifier->Value;
			}
		}
		
		//
		// Methods
		//
		
		virtual void Activate_Compound() override
		{			
		}
	
		virtual void Execute(double) override;
		
		virtual void Step(double dDt) override
		{
		}

	};
}