#pragma once
#include "Stdafx.h"
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"
#include "Rockwell_Library/Components/Hidden/ITimer.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"

using namespace System;
using namespace IPS::Server;
using namespace DCS::Ports;

namespace Rockwell_Library
{	
	[IPS::Plugin::LibraryInfo("TON", IPS::Plugin::Visibility::VISIBLE, "Timer On Delay")]
	[IPS::Plugin::DrawingTextProvider(DCSLogicTaskDrawingTextProvider::typeid)]
	[IPS::Plugin::LibraryImage("TON.png")]
	[IPS::Plugin::LibrarySize(200,125)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "Timer and Counter Instructions")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 20, 13, 20, "Green", false)]
	[IPS::Plugin::Port("OutputPort",Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 20, 13, 20, "Red", false)]
	[IPS::Plugin::Port("DNPort",	Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 50, 13, 20, "Red", false)]

	public ref class TON : public DCSLogicComponent, ITimer
	{
	public:

		TON()
		{
			TypeDescription			= "TON";
			Name					= "TON";
			Descriptor				= "Timer On Delay";
			
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
			Property.Value			= "Address";

			DN.Visible				= true;
			DN.Value				= false;
			DNPort					= dynamic_cast<BoolOutputPort^>(PortByName("DNPort"));
			DNPort->SetAssociatedProperty(%m_Done);

			TT.Visible				= false;
			TT.Value				= false;

			ACC.Visible				= true;
			ACC.Value				= 0;

			Preset.Visible			= true;
			Preset.Value			= 0;
			Preset.SetDisplayUnit(IPS::Units::UnitGroup::Time, IPS::Units::Unit::s);

			Timebase.Visible		= true;
			Timebase.Value			= 1;
			Timebase.SetDisplayUnit(IPS::Units::UnitGroup::Time, IPS::Units::Unit::s);
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Timer")]
		[IPS::Properties::GridOrder(0)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Timer"})]
		virtual property IPS::Properties::Text% Property
		{
			IPS::Properties::Text% get() override
			{
				return m_Property;
			}
			void set(IPS::Properties::Text% text)
			{
				m_Property				= text;				
				m_EN_Dest.Value			= m_Property.Value + "/EN";
				m_TT_Dest.Value			= m_Property.Value + "/TT";
				m_DN_Dest.Value			= m_Property.Value + "/DN";
				m_ACC_Dest.Value		= m_Property.Value + ".ACC";
				m_Timebase_Source.Value = m_Property.Value + ".BASE";
				m_Preset_Source.Value	= m_Property.Value + ".PRE";
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Time Base")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Timer"})]
		virtual property IPS::Properties::Double% Timebase
		{
			IPS::Properties::Double% get()
			{
				return m_Timebase;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Preset")]
		[IPS::Properties::GridOrder(20)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Timer"})]
		virtual property IPS::Properties::Double% Preset
		{
			IPS::Properties::Double% get()
			{
				return m_Preset;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Accum")]
		[IPS::Properties::GridOrder(30)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Timer"})]
		virtual property IPS::Properties::Double% ACC
		{
			IPS::Properties::Double% get()
			{
				return m_Accumulated;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("EN")]
		[IPS::Properties::GridOrder(0)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Output"})]
		virtual property IPS::Properties::Bool% Output
		{
			IPS::Properties::Bool% get() override
			{
				return m_Output;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("DN")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Output"})]
		virtual property IPS::Properties::Bool% DN
		{
			IPS::Properties::Bool% get()
			{
				return m_Done;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::RESULT)]
		[IPS::Properties::DisplayName("TT")]
		[IPS::Properties::GridOrder(0)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Internal"})]
		virtual property IPS::Properties::Bool% TT
		{
			IPS::Properties::Bool% get()
			{
				return m_Timing;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::RESULT)]
		[IPS::Properties::DisplayName("IN Prev")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Internal"})]
		virtual property IPS::Properties::Bool% Value
		{
			IPS::Properties::Bool% get() override
			{
				return m_Value;
			}
		}

		void CountUp(double Ts)
		{
			// Increment Counter (sec)
			ACC.Value += Ts / Timebase.Value;
		}
		
		virtual void Step(double Ts) override
		{
			Output.Value = Input.Value;

			if (Input.Value == false)
			{
				ACC.Value		= 0;
				TT.Value		= false;
				DN.Value		= false;
			}
			else
				TT.Value		= true;

			if (Input.Value == true && ACC.Value < Preset.Value)
			{
				CountUp(Ts);
				if (ACC.Value >= Preset.Value)
				{
					TT.Value	= false;
					DN.Value	= true;
				}
			}

			Value.Value	= Input.Value;

			Execute(Ts);
		}
		
		virtual void Execute(double) override;
		
	public:
		
		IPS::Properties::Bool		m_Done;
		IPS::Properties::Double		m_Accumulated;
		IPS::Properties::Bool		m_Timing;
		IPS::Properties::Text		m_EN_Dest;
		IPS::Properties::Text		m_TT_Dest;
		IPS::Properties::Text		m_DN_Dest;
		IPS::Properties::Text		m_ACC_Dest;
		IPS::Properties::Text		m_Timebase_Source;
		IPS::Properties::Text		m_Preset_Source;
		IPS::Properties::Double		m_Preset;
		IPS::Properties::Double		m_Timebase;
		DCSOutputPortBase^			DNPort;
	};
}