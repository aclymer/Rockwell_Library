#pragma once
#include "Ports.h"
#include <string>
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

using namespace System;
using namespace IPS::Server;
using namespace DCS::Ports;
using namespace info::lundin::Math;

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("MathBase", IPS::Plugin::Visibility::HIDDEN, "MathBase")]
	[IPS::Plugin::DrawingTextProviderAttribute(DCSLogicTaskDrawingTextProvider::typeid)]
	public ref class MathBase : public DCSLogicComponent
	{
	public:

		MathBase()
		{
			TypeDescription			= "MathBase";
			Name					= "MathBase";
			Descriptor				= "MathBase";

			Source_A.Visible		= false;

			Source_B.Visible		= false;

			Value_A.Visible			= false;

			Value_B.Visible			= false;
		}

		virtual ~MathBase(){};

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Source A")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text% Source_A
		{
			IPS::Properties::Text% get()
			{
				return m_Source_A;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(20)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Double% Value_A
		{
			IPS::Properties::Double% get()
			{
				return m_Value_A;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Source B")]
		[IPS::Properties::GridOrder(30)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Text%  Source_B
		{
			IPS::Properties::Text%  get()
			{
				return m_Source_B;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(40)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Components"})]
		virtual property IPS::Properties::Double%  Value_B
		{
			IPS::Properties::Double%  get()
			{
				return m_Value_B;
			}
		}

		//
		// Methods
		//

	public:

		IPS::Properties::Text			m_Source_A;
		IPS::Properties::Double			m_Value_A;
		IPS::Properties::Text			m_Source_B;
		IPS::Properties::Double			m_Value_B;
	};
}