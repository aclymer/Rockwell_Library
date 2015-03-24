#pragma once
#include "Stdafx.h"

using namespace System;
using namespace System::Collections;

namespace Rockwell_Library {

	ref class DCSLogicComponent;
	
	[IPS::Plugin::LibraryInfo("Rockwell DCS Logic Task", IPS::Plugin::Visibility::VISIBLE, "")]
	[IPS::Plugin::LibraryImage("Task.png")]
	public ref class DCSLogicTask : public IPS::Task::TaskBase
	{
	public: 

		DCSLogicTask()
		{
			m_pProject			= IPS::Server::IProject::GetInstance();
			Instance			= this;
		}			
		
		virtual System::Void InitProperties()					override;
		virtual System::Void Load(IPS::Core::Project^  project) override;
		virtual System::Void Unload()							override;		
		
	private:
			
		System::Void							LoadEvents();
		System::Void							UnloadEvents();
		System::Void 							Step(System::Void);
		System::Void 							Activate(System::Void);
		System::Void 							Deactivate(System::Void);

		IPS::Core::EventFunction^				m_pActivateEventHandler;
		IPS::Core::EventFunction^				m_pDeactivateEventHandler;
		IPS::Core::EventFunction^				m_pStepEventHandler;
								
	public:
		
		IPS::Core::Project^						m_pProject;
		static DCSLogicTask^					Instance;
		IPS::Core::ComponentList				m_DCSLogicComponents;
	};	

	
}