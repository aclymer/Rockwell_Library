#include "Stdafx.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"

namespace Rockwell_Library {
	
	System::Void DCSLogicTask::InitProperties()
	{
		IPS::Task::TaskBase::InitProperties();
	}//InitProperties
	
	System::Void DCSLogicTask::Load(IPS::Core::Project^  project)
	{
		TaskBase::Load(project);
		m_pProject = project;
		LoadEvents();
		if (Instance == nullptr)
		{
			Instance = this;
		}
	}
	
	System::Void DCSLogicTask::Unload()
	{
		TaskBase::Unload();
		UnloadEvents();
	}

	System::Void DCSLogicTask::LoadEvents()
	{
		m_pActivateEventHandler = gcnew IPS::Core::EventFunction(this, &DCSLogicTask::Activate);
		Project->Events->AddActivateEvent(this, m_pActivateEventHandler);
		m_pDeactivateEventHandler = gcnew IPS::Core::EventFunction(this, &DCSLogicTask::Deactivate);
		Project->Events->AddDeactivateEvent(this, m_pDeactivateEventHandler);
		m_pStepEventHandler = gcnew IPS::Core::EventFunction(this, &DCSLogicTask::Step);
		Project->Events->AddStepEvent(this, m_pStepEventHandler);
	}
	
	System::Void DCSLogicTask::UnloadEvents()
	{
		Project->Events->RemoveActivateEvent(this);
		delete m_pActivateEventHandler;;
		Project->Events->RemoveDeactivateEvent(this);
		delete m_pDeactivateEventHandler;;
		Project->Events->RemoveStepEvent(this);
		delete m_pStepEventHandler;;
	}

	System::Void DCSLogicTask::Activate(System::Void )
	{
		try
		{				
			m_DCSLogicComponents.Clear();
			this->FilterComponents(DCSLogicComponent::typeid, m_DCSLogicComponents);
			for each (DCSLogicComponent^ l_DCSLogicComponent in m_DCSLogicComponents)
			{
				l_DCSLogicComponent->Activate_Compound();
			}
		}
		catch (Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("blabla", this->Identifier, "Unknown exception occured during DCSLogicTask::Activate event : " + ex->Message));
		}
	}

	System::Void DCSLogicTask::Deactivate(System::Void )
	{
		try
		{
		}
		catch (Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("blabla", this->Identifier, "Unknown exception occured during DCSLogicTask::Deactivate event : " + ex->Message));
		}
	}

	System::Void DCSLogicTask::Step(System::Void)
	{
		try
		{
			DCSLogicComponent::step();
		}
		catch (Exception^ ex)
		{
			IPS::Errors::ErrorSystem::Report(gcnew IPS::Errors::ElementError("blabla", this->Identifier, "Unknown exception occured during DCSLogicTask::step event : " + ex->Message));
		}
	}
}
