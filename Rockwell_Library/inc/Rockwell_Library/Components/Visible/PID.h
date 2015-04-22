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

	public ref class PID : public DCSLogicComponent
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

			AM.Visible				= true;
			AM.Value				= 1;

			CM.Visible				= true;
			CM.Value				= true;

			Setpoint.Visible		= true;
			Setpoint.Value			= 0;

			Omax.Visible			= true;
			Omax.Value				= 16383;

			Omin.Visible			= true;
			Omin.Value				= 0;

			LL.Visible				= true;
			LL.Value				= false;

			UL.Visible				= true;
			UL.Value				= false;
						
			m_BaseElement.Value		= "Address";

			m_Bitset				= new std::bitset<16>(0);
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
		[IPS::Properties::DisplayName("Process Variable")]
		[IPS::Properties::GridOrder(30)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"PID"})]
		virtual property IPS::Properties::Text% PV_Source
		{
			IPS::Properties::Text% get()
			{
				return m_PV_Source;
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
				return m_CV_Source;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Control Block Length")]
		[IPS::Properties::GridOrder(200)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"PID"})]
		virtual property IPS::Properties::Double% Length
		{
			IPS::Properties::Double% get()
			{
				return m_Length;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Manual Mode")]
		[IPS::Properties::GridOrder(301)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% AM
		{
			IPS::Properties::Bool% get()
			{
				if (m_Bitset != nullptr)
					m_AM.Value				= m_Bitset->at(1);
				return m_AM;
			}	
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(1)			= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
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
				if (m_Bitset != nullptr)
					m_CM.Value				= m_Bitset->at(2);
				return m_CM;
			}	
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(2)			= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Output Limiting")]
		[IPS::Properties::GridOrder(303)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% OL
		{
			IPS::Properties::Bool% get()
			{
				if (m_Bitset != nullptr)
					m_OL.Value				= m_Bitset->at(3);
				return m_OL;
			}		
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(3)			= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Reset/Gain Enhancement")]
		[IPS::Properties::GridOrder(304)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% RG
		{
			IPS::Properties::Bool% get()
			{
				if (m_Bitset != nullptr)
					m_RG.Value				= m_Bitset->at(4);
				return m_RG;
			}	
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(4)			= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Deadband")]
		[IPS::Properties::GridOrder(308)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% DB
		{
			IPS::Properties::Bool% get()
			{
				if (m_Bitset != nullptr)
					m_DB.Value				= m_Bitset->at(8);
				return m_DB;
			}	
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(8)			= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Output Alarm Upper Limit")]
		[IPS::Properties::GridOrder(309)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% UL
		{
			IPS::Properties::Bool% get()
			{
				if (m_Bitset != nullptr)
					m_UL.Value				= m_Bitset->at(9);
				return m_UL;
			}			
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(9)			= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Output Alarm Lower Limit")]
		[IPS::Properties::GridOrder(310)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% LL
		{
			IPS::Properties::Bool% get()
			{
				if (m_Bitset != nullptr)
					m_LL.Value				= m_Bitset->at(10);
				return m_LL;
			}			
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(10)		= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("PID Enable")]
		[IPS::Properties::GridOrder(315)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% EN
		{
			IPS::Properties::Bool% get()
			{
				if (m_Bitset != nullptr)
					m_EN.Value				= m_Bitset->at(15);
				return m_EN;
			}			
			void set(IPS::Properties::Bool% value)
			{
				if (m_Bitset != nullptr)
					m_Bitset->at(15)		= value.Value;
				m_ControlBlock.Value	= (double) m_Bitset->to_ullong();				
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Setpoint")]
		[IPS::Properties::GridOrder(402)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Setpoint
		{
			IPS::Properties::Double% get()
			{
				return m_Setpoint;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Gain (Kc)")]
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
		[IPS::Properties::DisplayName("Reset (Ti)")]
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
		[IPS::Properties::DisplayName("Rate (Td)")]
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
		virtual property IPS::Properties::Double% Deadband
		{
			IPS::Properties::Double% get()
			{
				return m_Deadband;
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

		// Time Interval between PID calculations
		// The value is in 0.01 sec intervals. Value
		// should be 5-10 times faster than the natural
		// of the load. ( i.e. Value of 50 = 500ms )
		////////////////////////////////////////////////
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Loop Update")]
		[IPS::Properties::GridOrder(413)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% LoopUpdate
		{
			IPS::Properties::Double% get()
			{
				return m_LoopUpdate;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::STATIC)]
		[IPS::Properties::DisplayName("Scaled PV (%)")]
		[IPS::Properties::GridOrder(414)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Scaled_PV
		{
			IPS::Properties::Double% get()
			{
				return m_Scaled_PV;
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

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::RESULT)]
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
		[IPS::Properties::DisplayName("Integral Sum")]
		[IPS::Properties::GridOrder(417)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Parameters"})]
		virtual property IPS::Properties::Double% Int_Sum
		{
			IPS::Properties::Double% get()
			{
				return m_Int_Sum;
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
				return m_PV_Value;
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
				return m_CV_Value;
			}
		}
		
		virtual void Activate_Compound() override
		{
			m_BaseWord = m_BaseWord.Parse(Property.Value->Split(':')[1]);
			
			*m_Bitset					= (unsigned long long) m_ControlBlock.Value;
			m_BaseElement.Value			= Property.Value->Split(':')[0] + ":";
			m_ControlBlock.ValueAsObject= Get_Property(m_BaseElement.Value + (m_BaseWord + 0 ).ToString());	// Control Block
			m_Setpoint.ValueAsObject	= Get_Property(m_BaseElement.Value + (m_BaseWord + 2 ).ToString());	// Setpoint
			m_Kc.Value					= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 3 ).ToString()) / (10.0 + RG.Value * 90.0);	// Controller Gain
			m_Ti.Value					= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 4 ).ToString()) / (10.0 + RG.Value * 90.0);	// Reset
			m_Td.Value					= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 5 ).ToString()) / 100.0;	// Rate
			m_FFb.ValueAsObject			= Get_Property(m_BaseElement.Value + (m_BaseWord + 6 ).ToString());	// Feed Forward Bias
			m_Smax.ValueAsObject		= Get_Property(m_BaseElement.Value + (m_BaseWord + 7 ).ToString());	// Setpoint Max
			m_Smin.ValueAsObject		= Get_Property(m_BaseElement.Value + (m_BaseWord + 8 ).ToString());	// Setpoint Min
			m_Deadband.ValueAsObject	= Get_Property(m_BaseElement.Value + (m_BaseWord + 9 ).ToString());	// Deadband
			m_Omax.ValueAsObject		= Get_Property(m_BaseElement.Value + (m_BaseWord + 11).ToString());	// Output Max (CV%)
			m_Omin.ValueAsObject		= Get_Property(m_BaseElement.Value + (m_BaseWord + 12).ToString());	// Output Min (CV%)
			m_LoopUpdate.ValueAsObject	= Get_Property(m_BaseElement.Value + (m_BaseWord + 13).ToString());	// Loop Update
			m_Scaled_PV.ValueAsObject	= Get_Property(m_BaseElement.Value + (m_BaseWord + 14).ToString());	// Scaled PV
			m_SE.ValueAsObject			= Get_Property(m_BaseElement.Value + (m_BaseWord + 15).ToString());	// Scaled PV
			m_PV_Value.ValueAsObject	= Get_Property(PV_Source.Value);									// Process Variable
			m_CV_Value.ValueAsObject	= Get_Property(CV_Source.Value);									// Controlled Variable (CV%)
		}

		virtual void Execute(double) override;

		virtual void Step(double dDt) override
		{
			// Equation: 
			// Output = Kc * [Error + (E)dt / Ti + Td * D(-PV)/df] + bias
			//////////////////////////////////////////////////////////////
			m_PV_Value.ValueAsObject	= Get_Property(PV_Source.Value);									// Process Variable
			m_Setpoint.ValueAsObject	= Get_Property(m_BaseElement.Value + (m_BaseWord + 2 ).ToString());	// Setpoint
			m_Error.Value				= (CM.Value ? PV.Value - Setpoint.Value : Setpoint.Value - PV.Value);

			// Anti-Windup
			if (UL.Value == false && LL.Value == false)
				m_Integral.Value		= m_Integral.Value + m_Error.Value * dDt;

			Int_Sum.Value				= m_Integral / Ti.Value;
			m_Deriv.Value				= (m_Error_prev.Value - m_Error.Value) / dDt;
			CV.Value					= Kc.Value * (m_Error.Value + Int_Sum.Value  + Td.Value * m_Deriv.Value) + FFb.Value;
		
			m_Slope.Value				= (Omax.Value - Omin.Value) / (Smax.Value - Smin.Value);
			m_Offset.Value				= Omin.Value - Smin.Value * m_Slope.Value;
			m_Error_prev.Value			= m_Error.Value;
			SE.Value					= (m_Error.Value * m_Slope.Value) + m_Offset.Value;
			Scaled_PV.Value				= (PV.Value * m_Slope.Value) + m_Offset.Value;
			CV_Output.Value				= (CV.Value * m_Slope.Value) + m_Offset.Value;
			LoopUpdate.Value			= dDt / 0.01;
		}

	public:
		
		IPS::Properties::Double		m_ControlBlock;
		IPS::Properties::Double		m_Length;
		IPS::Properties::Double		m_Value;
		IPS::Properties::Text		m_PV_Source;
		IPS::Properties::Text		m_CV_Source;
		IPS::Properties::Double		m_PV_Value;
		IPS::Properties::Double		m_CV_Value;
		IPS::Properties::Bool		m_AM;

	private:

		int							m_BaseWord;
		std::bitset<16>*			m_Bitset;
		IPS::Properties::Text		m_BaseElement;
		IPS::Properties::Double		m_Setpoint;
		IPS::Properties::Double		m_Error;
		IPS::Properties::Double		m_Kc;
		IPS::Properties::Double		m_Ti;
		IPS::Properties::Double		m_Td;
		IPS::Properties::Double		m_FFb;
		IPS::Properties::Double		m_Smax;
		IPS::Properties::Double		m_Smin;
		IPS::Properties::Double		m_Deadband;
		IPS::Properties::Double		m_Omax;
		IPS::Properties::Double		m_Omin;
		IPS::Properties::Double		m_LoopUpdate;
		IPS::Properties::Double		m_Scaled_PV;
		IPS::Properties::Double		m_SE;
		IPS::Properties::Double		m_CV_Output;
		IPS::Properties::Double		m_Integral;
		IPS::Properties::Double		m_Int_Sum;
		IPS::Properties::Double		m_Deriv;
		IPS::Properties::Double		m_PV_Prev;
		IPS::Properties::Double		m_Error_prev;
		
				
		IPS::Properties::Double		m_Slope;
		IPS::Properties::Double		m_Offset;

		//
		// Control Block Bits
		//

		IPS::Properties::Bool		m_CM;
		IPS::Properties::Bool		m_OL;
		IPS::Properties::Bool		m_RG;
		IPS::Properties::Bool		m_DB;
		IPS::Properties::Bool		m_DA;
		IPS::Properties::Bool		m_LL;
		IPS::Properties::Bool		m_UL;
		IPS::Properties::Bool		m_EN;

	};
}