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

		DCSLogicComponent::DCSLogicComponent()
		{
			DCS::DCSPropertyTextProvider::DCSPropertyTextProvider();

			m_Project						= IPS::Server::IProject::GetInstance();
			Input.Visible					= false;

			Output.Visible					= false;

			Property.Visible				= false;
			Property.Value					= "Address";

			Value.Visible					= false;	

			ExecutionSequenceNumber.Visible = false;

			TaskInclude.Visible				= false;

			ShowSource.Visible				= true;
			ShowSource.Value				= true;
		}

	public:
		
		//
		// General
		//
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Show Source Text")]
		[IPS::Properties::GridOrder(100)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		[IPS::Properties::CheckBoxAttribute()]
		virtual property IPS::Properties::Bool% ShowSource
		{
			IPS::Properties::Bool% get()
			{
				return m_ShowSource;
			}
		}
		
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
		virtual property IPS::Properties::Bool% Output
		{
			IPS::Properties::Bool% get()
			{
				return m_Output;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Source")]
		[IPS::Properties::GridOrder(100)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Property
		{
			IPS::Properties::Text% get()
			{
				return m_Property;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(101)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Bool% Value
		{
			IPS::Properties::Bool% get()
			{
				return m_Value;
			}
		}
		
		//
		// Methods
		//

		void ReturnFromSubroutine();
		void JumpToSubroutine(String^);
		
		virtual bool CloneRemoteDescription(String^ source)
		{	
			try
			{				
				if (this->UserDescription->Value != m_Project->GetComponent(source)->UserDescription->Value)
				{
					this->UserDescription->Value = m_Project->GetComponent(source)->UserDescription->Value;

					return true;
				}
			}
			catch(System::Exception^ e)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(e->Message, this->Identifier, "(Clone Desc) Invalid Identifier: " + (String::IsNullOrEmpty(source) ? "-blank-" : source)));
			}
			
			return false;
		}

		virtual bool CopyPropertyDescription(String^ source, String^ destination)
		{	
			try
			{	
				if (m_PropertyDictionary.TryGetValue(source, l_CloneSourceProperty))
					if (dynamic_cast<DCS::Components::DCSComponentBase^>(l_CloneSourceProperty) != nullptr)
						if (l_CloneDestComponent->UserDescription->Value != dynamic_cast<DCS::Components::DCSComponentBase^>(l_CloneSourceProperty)->UserDescription->Value)
						{
							l_CloneDestComponent->UserDescription->Value = dynamic_cast<DCS::Components::DCSComponentBase^>(l_CloneSourceProperty)->UserDescription->Value;

							return true;
						}
			}
			catch(System::Exception^ e)
			{
				IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(e->Message, this->Identifier, "(Copy Desc) Invalid Identifier: " + source));
			}
			
			return false;
		}
		
		virtual System::Object^ Get_Property(String^ source)
		{		
			l_Val = 0;
			if (!System::Double::TryParse(source, l_Val))
			{
				if (!m_PropertyDictionary.TryGetValue(source, l_Property))
				{
					l_Property = m_Project->GetComponent(source)->GetPropertyFromPropID("Value");
					m_PropertyDictionary.Add(source, l_Property);
				}
				if (l_Property != nullptr)
					return l_Property->ValueAsObject;
				else
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, "(Get_Property) Invalid Identifier: " + source));

			}
						
			return l_Val;
		}
		
		virtual System::Void Set_Property(String^ destination, IPS::Core::Property% l_SourceProperty)
		{
			if (!m_PropertyDictionary.TryGetValue(destination, l_Property))
			{
				l_Property = m_Project->GetComponent(destination)->GetPropertyFromPropID("Value");
				if (l_Property != nullptr)
					m_PropertyDictionary.Add(destination, l_Property);
				else
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", this->Identifier, "(Get_Property) Invalid Identifier: " + destination));
			}

			l_Property->ValueAsObject = l_SourceProperty.ValueAsObject;
		}

		bool ParseAddress(List<String^>% parsed, String^ address)
		{
			parsed.Clear();
			Regex^ re = gcnew Regex("(#)?([A-Z]{1,2})((?:\\d+){0,3}?):([0-9]+)([./])?([\\dA-Z])?");

			if (re->IsMatch(address))
				parsed.AddRange(re->Split(address));

			return re->IsMatch(address);
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

		static void step(bool);
		
		virtual void Activate_Compound()
		{
		}

		static void PopulateIOPropertyList()
		{
			l_SystemIOPage = dynamic_cast<IPS::Core::DrawingPage^>(m_Project->FindPagesWithComponent(m_Project->GetComponent("S:0")->Identifier)[0]);
			if (l_SystemIOPage != nullptr)
			{
				for each (IPS::Core::Component^ m_Component in l_SystemIOPage->Components)
				{
					if (dynamic_cast<DCS::Components::Properties::PropertyBase^>(m_Component) != nullptr)
					{
						if (!m_PropertyDictionary.ContainsKey(m_Component->Identifier->Value))
							m_PropertyDictionary.Add(m_Component->Identifier->Value, dynamic_cast<DCS::Components::Properties::PropertyBase^>(m_Component)->GetPropertyFromPropID("Value"));
					}
				}
			}
		}
		
	protected:
		
		// Sort and fill LadderList starting with
		// first Rung on page, then iterating through
		// all the connected rungs. Get connected components
		// for each Rung and insert them in the list 
		// before the next rung. If a component is already
		// on the list, move it to the end of that rung.
		//////////////////////////////////////////////////
		static LinkedList<DCSLogicComponent^>^ PopulateRungList(DCSLogicComponent^ l_FirstRung)
		{
			l_Ladder = gcnew LinkedList<DCSLogicComponent^>;
			l_Ladder->AddFirst(l_FirstRung);

			LinkedListNode<DCSLogicComponent^>^ l_ThisRungItem = l_Ladder->First;

			while (l_ThisRungItem->Value->PortByName("RungPort")->GetConnectedComponents()->Count > 0)
			{
				try
				{
					l_Ladder->AddLast(dynamic_cast<DCSLogicComponent^>(l_ThisRungItem->Value->PortByName("RungPort")->GetConnectedComponents()[0]));
					l_ThisRungItem = l_ThisRungItem->Next;
				}
				catch (Exception^ ex)
				{
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, l_ThisRungItem->Value->Identifier, ex->Message + " Dangling OutLink: ReConnect or Delete.")); 
				}
			}

			l_ThisRungItem = l_Ladder->First;
			LinkedListNode<DCSLogicComponent^>^ l_NextRungItem = l_ThisRungItem->Next;

			// Iterate through connected components until
			// an END component is reached or throw an exception
			// Every Ladder should have an END component added
			// that is automatically placed by the original system.
			////////////////////////////////////////////////////////
			while (l_Ladder->Last->Value->Name != "END")
			{	
				if (l_ThisRungItem == nullptr)
					break;

				if (l_ThisRungItem == l_NextRungItem)
					l_NextRungItem = l_ThisRungItem->Next;

				IPS::Core::ComponentList^ l_ConnectedList;

				try
				{
					l_ConnectedList = l_ThisRungItem->Value->PortByName("OutputPort")->GetConnectedComponents();

					if (l_ConnectedList->Count > 0)
					{
						for each (DCSLogicComponent^ l_ConnectedComponent in l_ConnectedList)
						{
							if (l_ThisRungItem->Value == l_ConnectedComponent)
							{
								IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", l_ConnectedComponent->Identifier, "Dangling OutLink: Connect EndPoint or Delete.")); 
								break;
							}
							else
							{
								if (l_Ladder->Contains(l_ConnectedComponent))
								{
									l_Ladder->Remove(l_ConnectedComponent);
								}
						
								if (l_NextRungItem != nullptr)
									l_Ladder->AddBefore(l_NextRungItem, l_ConnectedComponent);
								else
									l_Ladder->AddLast(l_ConnectedComponent);
							}
						}						
					}
				}
				catch (Exception^ ex)
				{
					IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, l_ThisRungItem->Value->Identifier, ex->Message + " Dangling OutLink: Connect EndPoint or Delete.")); 
				}
				
				// Catch a bad Rung-->Rung link
				// If "End of List" and LastItem != "END"
				/////////////////////////////////////////
				if (l_ThisRungItem->Next == nullptr && l_ThisRungItem->Value->Name != "END")
				{
					try
					{
						while (l_ThisRungItem->Value->Name != "Rung")
						{
							l_ThisRungItem = l_ThisRungItem->Previous;
						}

						IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("", l_ThisRungItem->Value->Identifier, "Discontinuity in Rungs, END not reached, check RungLinks.")); 
						break;
					}
					catch(Exception^ ex)
					{
						IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError(ex->Source, l_ThisRungItem->Value->Identifier, ex->Message + "Unknown Error in this Rung.")); 
					}
				}
				else
					l_ThisRungItem = l_ThisRungItem->Next;
			}

			return l_Ladder;
		}

	public:

		static System::Collections::Generic::Dictionary
					<String^, IPS::Core::Property^>		m_PropertyDictionary;
		static IPS::Server::IProject^					m_Project;

		String^											TypeDescription;
		String^											Name;
		String^											Descriptor;

		IPS::Properties::Bool							m_Input;
		IPS::Properties::Bool							m_Value;
		IPS::Properties::Bool							m_Output;
		IPS::Properties::Bool							m_ShowSource;
		IPS::Properties::Text							m_Property;

		DCSInputPortBase^								InputPort;
		DCSOutputPortBase^								OutputPort;

	private:

		double											l_Val;
		IPS::Properties::Double							pValue;
		static IPS::Core::Property^						l_Property;
		static IPS::Core::Property^						l_CloneSourceProperty;
		static DCSLogicComponent^						l_CloneDestComponent;
		static IPS::Core::DrawingPage^					l_SystemIOPage;
		static IPS::Properties::Bool					l_Value;
		static DCSLogicComponent^						l_Component;		
		static DCS::Links::Bool_BoolLink^				l_BoolLink;

		Bool::BoolInputPort^							l_BoolInputPort;
		Bool::BoolOutputPort^							r_BoolOutputPort;
		Bool::BoolOutputPort^							l_BoolOutputPort;
		IPS::Core::LinkDrawingData^						l_LinkDrawingData;
		
		void InitCompoundProperties()
		{
		}
		
	protected:
		
		static LinkedList<DCSLogicComponent^>^			l_Ladder;
		static IPS::Core::LinkList						l_LinkList;	
		static Generic::LinkedList<DCSLogicComponent^>	m_ExecutionQueue;
		static IPS::Core::ComponentList					m_DCSLogicComponents;
		static System::Collections::Generic::Dictionary
			<String^, LinkedList<DCSLogicComponent^>^>	LadderPageDictionary;
	};
	
}