#pragma once
#include "Stdafx.h"

using namespace System;
using namespace System::Collections;

namespace Rockwell_Library {

	ref class DCSLogicComponent;
	
	[IPS::Plugin::LibraryInfo("Rockwell DCS Logic Task", IPS::Plugin::Visibility::VISIBLE, "")]
	[IPS::Plugin::LibraryImage("Rockwell_DCSLogic_Task.png")]
	[IPS::Plugin::LibrarySizeAttribute(100,100)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	public ref class DCSLogicTask : public IPS::Task::TaskBase
	{
	public: 

		DCSLogicTask()
		{
			m_pProject						= IPS::Server::IProject::GetInstance();
			Instance						= this;

			this->m_CanUseMultipleThreads	= false;
			this->NumberOfThreads			= 1;

			AnimateLinks.Visible			= true;
			AnimateLinks.Value				= false;
			
			ExecID.Visible					= true;
			ExecID.Value					= false;

			UpdateTextValues.Visible		= true;
			UpdateTextValues.Value			= false;

			RegExString.Visible				= true;
			RegExString.Value				= "#?([A-Z]{1,2})((?:\\d+){0,3})?(:)([0-9]+)([./])?([\\dA-Z])?";
			//RegExString.Value				= "(#)?([A-Z]{1,2})((?:\\d+){0,3}?):([0-9]+)([./]{0,1})([\\dA-Z]{0,4})";

			l_FirstPass						= true;

			RunTestLadder.Visible			= true;
			RunTestLadder.Value				= false;
		}			
		
		virtual System::Void InitProperties()					override;
		virtual System::Void Load(IPS::Core::Project^  project) override;
		virtual System::Void Unload()							override;
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Update Component Text")]
		[IPS::Properties::GridOrder(100)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Text Options"})]
		virtual property IPS::Properties::Bool% UpdateTextValues
		{
			IPS::Properties::Bool% get()
			{
				return m_UpdateTextValues;
			}
		}
				
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Animate Links")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Debug"})]
		virtual property IPS::Properties::Bool% AnimateLinks
		{
			IPS::Properties::Bool% get()
			{
				return m_AnimateLinks;
			}
		}		
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Output Executed IDs")]
		[IPS::Properties::GridOrder(1000)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Debug"})]
		virtual property IPS::Properties::Bool% ExecID
		{
			IPS::Properties::Bool% get()
			{
				return m_ExecID;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Regular Expression")]
		[IPS::Properties::GridOrder(2000)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Debug"})]
		virtual property IPS::Properties::Text% RegExString
		{
			IPS::Properties::Text% get()
			{
				return m_RegExString;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Run Test Ladder")]
		[IPS::Properties::GridOrder(3000)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Debug"})]
		virtual property IPS::Properties::Bool% RunTestLadder
		{
			IPS::Properties::Bool% get()
			{
				return m_RunTestLadder;
			}
		}
		
	private:
			
		static bool								l_FirstPass;
		System::Void							LoadEvents();
		System::Void							UnloadEvents();
		System::Void 							Step(System::Void);
		System::Void 							Activate(System::Void);
		System::Void 							Deactivate(System::Void);

		IPS::Core::EventFunction^				m_pActivateEventHandler;
		IPS::Core::EventFunction^				m_pDeactivateEventHandler;
		IPS::Core::EventFunction^				m_pStepEventHandler;
								
	public:
		
		static IPS::Properties::Bool			m_RunTestLadder;
		static IPS::Properties::Text			m_RegExString;
		static IPS::Properties::Bool			m_UpdateTextValues;
		IPS::Core::Project^						m_pProject;
		static DCSLogicTask^					Instance;
		static IPS::Properties::Bool			m_ExecID;
		static IPS::Properties::Bool			m_AnimateLinks;
		static IPS::Core::ComponentList			m_DCSLogicComponents;
	};	

	
}