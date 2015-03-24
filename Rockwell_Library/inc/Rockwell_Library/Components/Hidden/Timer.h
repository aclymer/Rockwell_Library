#pragma once
#include "Stdafx.h"
#include "Rockwell_Library/Components/Hidden/ITimer.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Collections::Generic;
using namespace DCS::Ports::Bool;
using namespace DCS::Ports::Double;
using namespace DCS::Ports::Integer;

namespace Rockwell_Library {

	public enum class TimerType { TON, TOF };

	public ref class Timer : public ITimer
	{
	public:

		Timer()
		{
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("IN_prev")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"General"})]
		property IPS::Properties::Bool% Input
		{
			IPS::Properties::Bool% get()
			{
				return m_Input;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Timer")]
		[IPS::Properties::GridOrder(0)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Timer"})]
		property IPS::Properties::Text% Source
		{
			IPS::Properties::Text% get()
			{
				return m_Source;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Time Base")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Timer"})]
		property IPS::Properties::Double% Timebase
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
		property IPS::Properties::Double% Preset
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
		property IPS::Properties::Double% ACC
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
		property IPS::Properties::Bool% EN
		{
			IPS::Properties::Bool% get()
			{
				return m_Enable;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("DN")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Output"})]
		property IPS::Properties::Bool% DN
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
		property IPS::Properties::Bool% TT
		{
			IPS::Properties::Bool% get()
			{
				return m_Timing;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::RESULT)]
		[IPS::Properties::DisplayName("IN")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Internal"})]
		property IPS::Properties::Bool% Input_Prev
		{
			IPS::Properties::Bool% get()
			{
				return m_Input_Prev;
			}
		}

		virtual	void Step(double Ts)
		{
			EN.Value = Input.Value;
			CountUp(Ts);
		}

		void CountUp(double Ts)
		{
			// Increment Counter (sec)
			ACC.Value += Ts / Timebase.Value;
		}

		void Assign(Timer^ timer)
		{
			this->Source.Value		= timer->Source.Value;
			this->DN.Value			= timer->DN.Value;
			this->Preset.Value		= timer->Preset.Value;
			this->ACC.Value			= timer->ACC.Value;
			this->EN.Value			= timer->EN.Value;
			this->Input.Value		= timer->Input.Value;
			this->Input_Prev.Value	= timer->Input_Prev.Value;
			this->TT.Value			= timer->TT.Value;
		}

	private:
		
		IPS::Properties::Text		m_Source;
		IPS::Properties::Double		m_Accumulated;
		IPS::Properties::Double		m_Preset;
		IPS::Properties::Double		m_Timebase;
		IPS::Properties::Bool		m_Enable;
		IPS::Properties::Bool		m_Input;
		IPS::Properties::Bool		m_Input_Prev;
		IPS::Properties::Bool		m_Done;
		IPS::Properties::Bool		m_Timing;
	};
	
	public ref class OnDelay : Timer
	{

	public:

		OnDelay()
		{
		}

		virtual void Step(double Ts) override
		{
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

			Input_Prev.Value	= Input.Value;
		}
	};

	public ref class OffDelay : Timer
	{

	public:

		OffDelay()
		{
		}

		virtual void Step(double Ts) override
		{
			if (Input.Value == true)
			{
				ACC.Value		= 0;
				TT.Value		= false;
				DN.Value		= true;
			}
			else
				TT.Value		= true;

			if (Input.Value == false && ACC.Value < Preset.Value)
			{
				TT.Value		= true;

				CountUp(Ts);

				if (ACC.Value >= Preset.Value)
				{
					TT.Value	= false;
					DN.Value	= false;
				}
			}

			Input_Prev.Value	= Input.Value;
		}
	};

}