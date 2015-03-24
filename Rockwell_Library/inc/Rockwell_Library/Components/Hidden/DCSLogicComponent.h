#pragma once
#include "Ports.h"
#include "Stdafx.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Collections::Generic;
using namespace System::Text::RegularExpressions;
using namespace DCS::Ports;

namespace Rockwell_Library
{
	ref class MetaDataEditor;
	
	[IPS::Plugin::LibraryInfo("Rockwell Logic Component Base", IPS::Plugin::Visibility::HIDDEN, "Rockwell Logic Component Base")]
	public ref class DCSLogicComponent : public DCS::Components::DCSComponentBase
	{

	public:

		DCSLogicComponent()
		{
			m_Project			= IPS::Server::IProject::GetInstance();

			DCS::DCSPropertyTextProvider::DCSPropertyTextProvider();

			Input.Visible		= false;
			Output.Visible		= false;
			Property.Visible	= false;
			Value.Visible		= false;			
		}

	public:
		
		//
		// General
		//
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Input")]
		[IPS::Properties::GridOrder(0)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		virtual property IPS::Properties::Bool%  Input
		{
			IPS::Properties::Bool% get()
			{
				return m_Input;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Output")]
		[IPS::Properties::GridOrder(1)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		virtual property IPS::Properties::Bool%  Output
		{
			IPS::Properties::Bool%  get()
			{
				return m_Output;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Source")]
		[IPS::Properties::GridOrder(100)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text%  Property
		{
			IPS::Properties::Text%  get()
			{
				return m_Property;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(101)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Bool%  Value
		{
			IPS::Properties::Bool%  get()
			{
				return m_Value;
			}
		}
		
		//
		// Methods
		//

		void	ReturnFromSubroutine();
		void	JumpToSubroutine(String^);
		
		virtual bool CloneRemoteDescription(String^ source)
		{	
			try
			{				
				if (this->UserDescription->Value != m_Project->GetComponent(source)->UserDescription->Value)
					this->UserDescription->Value = m_Project->GetComponent(source)->UserDescription->Value;
				return true;
			}
			catch(System::Exception^ e)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(e->Message, this->Identifier, "(Clone ID) Invalid Identifier: " + (String::IsNullOrEmpty(source) ? "-blank-" : source)));
				return false;
			}
		}
		
		virtual System::Object^ Get_Property(String^ source)
		{	
			try
			{				
				return m_Project->GetComponent(source)->GetPropertyFromPropID("Value")->ValueAsObject;
			}
			catch(System::Exception^ e)
			{
				IPS::Properties::Double Value;
				Value.Value = Value.Parse(source);
				if (Value.ValueAsObject == nullptr)
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(e->Message, this->Identifier, "(Get_Property) Invalid Identifier: " + source));
				return Value.ValueAsObject;
			}
		}
		
		virtual System::Void Set_Property(String^ destination, System::Object^ object)
		{
			try
			{
				m_Project->GetComponent(destination)->GetPropertyFromPropID("Value")->ValueAsObject = object;
			}
			catch(System::Exception^ e)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(e->Message, this->Identifier, "(Set_Property) Invalid Identifier: " + destination));
			}
		}

		void ParseAddress(List<String^>% parsed, String^ address)
		{
			parsed.Clear();
			try
			{
				Regex^ re = gcnew Regex("(#)?([A-Z]{1,2})((?:\\d+){0,3}?):([0-9]+)([./])?([\\dA-Z])?");
				if (re->IsMatch(address))
					parsed.AddRange(re->Split(address));
			}
			catch (Exception^ ex)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(address, this->Identifier, "Error in regular expression : " + ex->Message));
			}
		}
		
		virtual void ReadInputs() override
		{
			DCS::Components::DCSComponentBase::ReadInputs();
		}

		virtual void Execute(double p_dTimeStep)
		{
		}
		
		virtual void Step(double dDt) override
		{
		}
		
		virtual System::Void InitProperties() override
		{
			IPS::Plugin::ComponentBase::InitProperties();
		}

		static void step();
		
		static void Activate_Compound()
		{
			LadderPageDictionary.Clear();
			l_LinkList.Clear();

			try
			{
				for each (IPS::Core::DrawingPage^ l_Page in m_Project->Pages)
				{
					if (l_Page != nullptr && l_Page->UserDescription->Value->StartsWith("U:"))
					{
						for each (IPS::Core::Component^ r_Component in l_Page->Components)
						{
							l_Component = dynamic_cast<DCSLogicComponent^>(r_Component);
							
							if (l_Component != nullptr && l_Component->TypeDescription == "Rung" && l_Component->InputPort->IsConnected == false)
								LadderPageDictionary.Add(l_Page->UserDescription->Value, gcnew LinkedList<DCSLogicComponent^>(PopulateRungList(l_Component)));
						}
														
						// Add Drawing Page Links to LinkList
						for each (IPS::Core::Link^ l_Link in l_Page->Links)
						{
							l_BoolLink = dynamic_cast<DCS::Links::Bool_BoolLink^>(l_Link);
							if (l_BoolLink != nullptr)
								l_LinkList.AddLink(l_Link);
						}
					}
				}

				m_ExecutionQueue.Clear();

			} catch (Exception^ ex) { IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::GeneralError("Activate event.", ex->Source, ex->Message)); }
		}
		
	private:

		static LinkedList<DCSLogicComponent^>^ PopulateRungList(DCSLogicComponent^ l_FirstRung)
		{
			l_Ladder = gcnew LinkedList<DCSLogicComponent^>;
			l_Ladder->AddFirst(l_Component);

			LinkedListNode<DCSLogicComponent^>^ l_ThisRungItem =  l_Ladder->First;
			DCSLogicComponent^ l_NextRungItem = dynamic_cast<DCSLogicComponent^>(l_Component->PortByName("RungPort")->GetConnectedComponents()[0]);
			l_Ladder->AddLast(l_NextRungItem);
			bool EOR = true;

			do
			{	
				IPS::Core::ComponentList^ l_ConnectedList = l_ThisRungItem->Value->PortByName("OutputPort")->GetConnectedComponents();

				if (l_ConnectedList->Count > 0)
				{
					for each (DCSLogicComponent^ l_ConnectedComponent in l_ConnectedList)
					{
						if (l_Ladder->Contains(l_ConnectedComponent))
							l_Ladder->Remove(l_ConnectedComponent);
						
						if (l_NextRungItem == nullptr)
							l_Ladder->AddLast(l_ConnectedComponent);
						else
							l_Ladder->AddBefore(l_Ladder->Last, l_ConnectedComponent);
					}						
				}
				
				l_ThisRungItem = l_ThisRungItem->Next;

				if (l_ThisRungItem != nullptr)
				{
					if (l_ThisRungItem->Value->TypeDescription == "Rung")
					{
						if (l_ThisRungItem->Value->Ports->PortByName("RungPort")->GetConnectedComponents()->Count > 0)
						{
							l_NextRungItem = dynamic_cast<DCSLogicComponent^>(l_ThisRungItem->Value->Ports->PortByName("RungPort")->GetConnectedComponents()[0]);
							l_Ladder->AddLast(l_NextRungItem);
						}
						else
							l_NextRungItem = nullptr;
					} 
				}
				else
					EOR = false;

			} while (EOR == true);
			
			for each (DCSLogicComponent^ nothing in l_Ladder)
			{
				Diagnostics::Debug::WriteLine(nothing->Identifier->Value);
			}
				
			Diagnostics::Debug::WriteLine("");

			return l_Ladder;
		}

	public:

		IPS::Core::Page^								m_CurrentPage;
		static IPS::Server::IProject^					m_Project;

		String^											TypeDescription;
		String^											Name;
		String^											Descriptor;

		static Generic::Dictionary<String^ ,
				LinkedList<DCSLogicComponent^>^>		LadderPageDictionary;

		bool FindFirstRung(IPS::Core::Component^ component)
		{
			return true;
		}


	private:
		
		static int count								= 0;
		static DCSLogicComponent^						l_Component;
		static Generic::LinkedList<DCSLogicComponent^>	m_ExecutionQueue;
		static IPS::Properties::Bool					l_Value;
		Bool::BoolInputPort^							l_BoolInputPort;
		Bool::BoolOutputPort^							r_BoolOutputPort;
		Bool::BoolOutputPort^							l_BoolOutputPort;
		IPS::Core::LinkDrawingData^						l_LinkDrawingData;
		IPS::Core::ComponentList						m_DCSLogicComponents;
		String^											l_InitSubroutine;
		static IPS::Core::LinkList						l_LinkList;
		static DCS::Links::Bool_BoolLink^				l_BoolLink;		
		static LinkedList<DCSLogicComponent^>^			l_Ladder;
		
		void InitCompoundProperties()
		{
		}
		
	protected:
		
			IPS::Properties::Bool						m_Input;
			IPS::Properties::Bool						m_Output;
			IPS::Properties::Bool						m_Value;
			IPS::Properties::Text						m_Property;
			DCSInputPortBase^							InputPort;
			DCSOutputPortBase^							OutputPort;
	};
	
}