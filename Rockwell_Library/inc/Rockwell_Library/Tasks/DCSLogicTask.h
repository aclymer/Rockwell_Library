#pragma once
#include "Stdafx.h"

using namespace System;
using namespace System::Collections;

namespace Rockwell_Library {

	ref class DCSLogicComponent;
	
	[IPS::Plugin::LibraryInfo("Rockwell DCS Logic Task", IPS::Plugin::Visibility::VISIBLE, "")]
	[IPS::Plugin::LibraryImage("Rockwell_DCSLogic_Task.png")]
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

			ShowSource.Visible				= true;
			ShowSource.Value				= false;

			l_FirstPass						= true;
		}			
		
		virtual System::Void InitProperties()					override;
		virtual System::Void Load(IPS::Core::Project^  project) override;
		virtual System::Void Unload()							override;
				
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Animate Links")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		[IPS::Properties::CheckBox()]
		virtual property IPS::Properties::Bool% AnimateLinks
		{
			IPS::Properties::Bool% get()
			{
				return m_AnimateLinks;
			}
		}		
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Show Source Text (all)")]
		[IPS::Properties::GridOrder(100)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		[IPS::Properties::CheckBox()]
		virtual property IPS::Properties::Bool% ShowSource
		{
			IPS::Properties::Bool% get()
			{
				return m_ShowSource;
			}
		}
		
	private:
			
		static bool								l_FirstPass;
		System::Void							LoadEvents();
		System::Void							UnloadEvents();
		System::Void 							Step(System::Void);
		System::Void 							Activate(System::Void);
		System::Void 							Deactivate(System::Void);

		static IPS::Properties::Bool			m_ShowSource;
		IPS::Core::EventFunction^				m_pActivateEventHandler;
		IPS::Core::EventFunction^				m_pDeactivateEventHandler;
		IPS::Core::EventFunction^				m_pStepEventHandler;
								
	public:
		
		IPS::Core::Project^						m_pProject;
		static DCSLogicTask^					Instance;
		IPS::Properties::Bool					m_AnimateLinks;
		IPS::Core::ComponentList				m_DCSLogicComponents;
	};	

	
}