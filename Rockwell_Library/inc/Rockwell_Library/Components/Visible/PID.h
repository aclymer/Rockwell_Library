#pragma once
#include "Ports.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("PID", IPS::Plugin::Visibility::VISIBLE, "Proportional/Integral/Derivative")]
	[IPS::Plugin::LibraryImage("PID.png")]
	[IPS::Plugin::LibrarySizeAttribute(250,150)]
	[IPS::Plugin::LibraryRelativeSizeAttribute(false)]
	[IPS::Plugin::LibraryCategory("Ladder Logic", "PID Control")]
	[IPS::Plugin::Port("InputPort", Bool::BoolInputPort::typeid, -1, 0, -1, 0, 17, 10, 17, "Green", false)]
	[IPS::Plugin::Port("OutputPort", Bool::BoolOutputPort::typeid, 0, -1, -1, 100, 17, 20, 17, "Red", false)]

	public ref class PID : public MathBase
	{
	public:

		Rockwell_Library::PID()
		{
			TypeDescription			= "PID Control";
			Name					= "PID";
			Descriptor				= "Proportional/Integral/Derivative";

			Input.Visible			= true;
			Input.Value				= false;
			InputPort				= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);

			Output.Visible			= true;
			Output.Value			= false;
			OutputPort				= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);

			Property.Visible		= true;
			Property.Value			= "Address";

			Value.Visible			= true;
			Value.Value				= 0;

			PV_Source.Visible		= true;
			PV_Source.Value			= "Address";

			CV_Source.Visible		= true;
			CV_Source.Value			= "Address";

			PV.Visible				= true;
			PV.Value				= 0;

			CV.Visible				= true;
			CV.Value				= 0;

			Length.Visible			= true;
			Length.Value			= 0;

			CM.Visible				= true;
			CM.Value				= true;

			SP.Visible				= true;
			SP.Value				= 0;
						
			std::bitset<16>			m_ControlBlock;
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Control Block")]
		[IPS::Properties::GridOrder(10)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"PID"})]
		virtual property IPS::Properties::Text% Property
		{
			IPS::Properties::Text% get() override
			{
				return m_Property;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Control Block")]
		[IPS::Properties::GridOrder(424)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"PID"})]
		virtual property IPS::Properties::Double% Value
		{
			IPS::Properties::Double% get() new
			{
				return m_Value;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Process Variable")]
		[IPS::Properties::GridOrder(30)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"PID"})]
		virtual property IPS::Properties::Text% PV_Source
		{
			IPS::Properties::Text% get()
			{
				return m_Source_A;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Control Variable")]
		[IPS::Properties::GridOrder(166)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"PID"})]
		virtual property IPS::Properties::Text% CV_Source
		{
			IPS::Properties::Text%  get()
			{
				return m_Source_B;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Control Block Length")]
		[IPS::Properties::GridOrder(200)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"PID"})]
		virtual property IPS::Properties::Integer% Length
		{
			IPS::Properties::Integer% get()
			{
				return m_Length;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Auto/Manual (AM)")]
		[IPS::Properties::GridOrder(301)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% AM
		{
			IPS::Properties::Bool% get()
			{
				return m_CM;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Control Mode")]
		[IPS::Properties::GridOrder(302)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% CM
		{
			IPS::Properties::Bool% get()
			{
				return m_CM;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Deadband")]
		[IPS::Properties::GridOrder(303)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% DB
		{
			IPS::Properties::Bool% get()
			{
				return m_CM;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Setpoint SP")]
		[IPS::Properties::GridOrder(402)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% SP
		{
			IPS::Properties::Double% get()
			{
				return m_SP;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Gain Kc")]
		[IPS::Properties::GridOrder(403)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Kc
		{
			IPS::Properties::Double% get()
			{
				return m_Kc;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Reset Ti")]
		[IPS::Properties::GridOrder(404)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Ti
		{
			IPS::Properties::Double% get()
			{
				return m_Ti;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Rate Td")]
		[IPS::Properties::GridOrder(405)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Td
		{
			IPS::Properties::Double% get()
			{
				return m_Td;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Feed Forward Bias")]
		[IPS::Properties::GridOrder(406)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% FFb
		{
			IPS::Properties::Double% get()
			{
				return m_FFb;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Setpoint Max (Smax)")]
		[IPS::Properties::GridOrder(407)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Smax
		{
			IPS::Properties::Double% get()
			{
				return m_Smax;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Setpoint Min (Smin)")]
		[IPS::Properties::GridOrder(408)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Smin
		{
			IPS::Properties::Double% get()
			{
				return m_Smin;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Deaband")]
		[IPS::Properties::GridOrder(409)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Dband
		{
			IPS::Properties::Double% get()
			{
				return m_DB;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Output Max (CV%)")]
		[IPS::Properties::GridOrder(411)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Omax
		{
			IPS::Properties::Double% get()
			{
				return m_Omax;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Output Min (CV%)")]
		[IPS::Properties::GridOrder(412)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Omin
		{
			IPS::Properties::Double% get()
			{
				return m_Omin;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Loop Update")]
		[IPS::Properties::GridOrder(413)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% LU
		{
			IPS::Properties::Double% get()
			{
				return m_LU;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Scaled PV (%)")]
		[IPS::Properties::GridOrder(414)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% sPV
		{
			IPS::Properties::Double% get()
			{
				return m_sPV;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::RESULT)]
		[IPS::Properties::DisplayName("Scaled Error (%)")]
		[IPS::Properties::GridOrder(415)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% SE
		{
			IPS::Properties::Double% get()
			{
				return m_SE;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Output CV (%)")]
		[IPS::Properties::GridOrder(416)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% CV_Output
		{
			IPS::Properties::Double% get()
			{
				return m_CV_Output;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("MSW Integral Sum")]
		[IPS::Properties::GridOrder(417)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% MSW
		{
			IPS::Properties::Double% get()
			{
				return m_MSW;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("LSW Integral Sum")]
		[IPS::Properties::GridOrder(418)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% LSW
		{
			IPS::Properties::Double% get()
			{
				return m_LSW;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("PV")]
		[IPS::Properties::GridOrder(423)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% PV
		{
			IPS::Properties::Double% get()
			{
				return m_Value_A;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("CV")]
		[IPS::Properties::GridOrder(424)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% CV
		{
			IPS::Properties::Double% get()
			{
				return m_Value_B;
			}
		}

		virtual void Activate_Compound() override;

		virtual void Execute(double) override;

		virtual void Step(double dDt) override;

	public:

		IPS::Properties::Integer	m_Length;
		IPS::Properties::Double		m_Value;

	private:

		int							m_BaseWord;
		String^						m_BaseElement;
		IPS::Properties::Double		m_SP;
		IPS::Properties::Double		m_Error;
		IPS::Properties::Bool		m_CM;
		IPS::Properties::Double		m_Kc;
		IPS::Properties::Double		m_Ti;
		IPS::Properties::Double		m_Td;
		IPS::Properties::Double		m_FFb;
		IPS::Properties::Double		m_Smax;
		IPS::Properties::Double		m_Smin;
		IPS::Properties::Double		m_DB;
		IPS::Properties::Double		m_Omax;
		IPS::Properties::Double		m_Omin;
		IPS::Properties::Double		m_LU;
		IPS::Properties::Double		m_sPV;
		IPS::Properties::Double		m_SE;
		IPS::Properties::Double		m_CV_Output;
		IPS::Properties::Double		m_MSW;
		IPS::Properties::Double		m_LSW;
		IPS::Properties::Double		m_Error_prev;

	};
}