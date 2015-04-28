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
			TypeDescription				= "PID Control";
			Name						= "PID";
			Descriptor					= "Proportional/Integral/Derivative";

			Input.Visible				= true;
			Input.Value					= false;
			InputPort					= dynamic_cast<Bool::BoolInputPort^>(PortByName("InputPort"));
			InputPort->SetAssociatedProperty(%m_Input);
				
			Output.Visible				= true;
			Output.Value				= false;
			OutputPort					= dynamic_cast<Bool::BoolOutputPort^>(PortByName("OutputPort"));
			OutputPort->SetAssociatedProperty(%m_Output);

			Property.Visible			= true;
			Property.Value				= "Address";
			
			Value.Visible				= false;

			PV_Source.Visible			= true;
			PV_Source.Value				= "Address";

			CV_Source.Visible			= true;
			CV_Source.Value				= "Address";

			SPV.Visible					= true;
			SPV.Value					= 0;

			CV.Visible					= true;
			CV.Value					= 0;

			Length.Visible				= true;
			Length.Value				= 0;

			AM.Visible					= true;
			AM.Value					= 1;

			CM.Visible					= true;
			CM.Value					= true;

			Setpoint.Visible			= true;
			Setpoint.Value				= 0;

			Omax.Visible				= true;
			Omax.Value					= 16383;

			Omin.Visible				= true;
			Omin.Value					= 0;

			LL.Visible					= true;
			LL.Value					= false;

			UL.Visible					= true;
			UL.Value					= false;
						
			m_BaseElement.Value			= "Address";

			m_BaseWord					= 0;
				
			ControlBlock.Visible		= false;
			ControlBlock.Value			= 0;
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
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Value")]
		[IPS::Properties::GridOrder(299)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Double% ControlBlock
		{
			IPS::Properties::Double% get()
			{
				std::bitset<16> m_Bitset= (unsigned long) m_ControlBlock.Value;
				m_Bitset[0]				= TM.Value;
				m_Bitset[1] 			= AM.Value;
				m_Bitset[2] 			= CM.Value;
				m_Bitset[3] 			= OL.Value;
				m_Bitset[4] 			= RG.Value;
				m_Bitset[5] 			= SC.Value;
				m_Bitset[6] 			= TF.Value;
				m_Bitset[7] 			= DA.Value;
				m_Bitset[8] 			= DB.Value;
				m_Bitset[9] 			= UL.Value;
				m_Bitset[10] 			= LL.Value;
				m_Bitset[11] 			= SP.Value;
				m_Bitset[12] 			= PV.Value;
				m_Bitset[13] 			= DN.Value;
				m_Bitset[14] 			= RA.Value;
				m_Bitset[15] 			= EN.Value;
				m_ControlBlock.Value	= (double) m_Bitset.to_ulong();

				return m_ControlBlock;
			}	
			void set(IPS::Properties::Double% value)
			{
				m_ControlBlock.Value	= value.Value;				
				std::bitset<16> m_Bitset= (unsigned long) value.Value;
				TM.Value				= m_Bitset[0];
				AM.Value     			= m_Bitset[1];
				CM.Value     			= m_Bitset[2];
				OL.Value     			= m_Bitset[3];
				RG.Value     			= m_Bitset[4];
				SC.Value     			= m_Bitset[5];
				TF.Value    			= m_Bitset[6];
				DA.Value     			= m_Bitset[7];
				DB.Value     			= m_Bitset[8];
				UL.Value     			= m_Bitset[9];
				LL.Value     			= m_Bitset[10];
				SP.Value     			= m_Bitset[11];
				SPV.Value    			= m_Bitset[12];
				DN.Value     			= m_Bitset[13];
				RA.Value     			= m_Bitset[14];
				EN.Value     			= m_Bitset[15];
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Timed Mode")]
		[IPS::Properties::GridOrder(300)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% TM
		{
			IPS::Properties::Bool% get()
			{
				return m_TM;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Manual Mode")]
		[IPS::Properties::GridOrder(301)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% AM
		{
			IPS::Properties::Bool% get()
			{
				return m_AM;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
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

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Output Limiting")]
		[IPS::Properties::GridOrder(303)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% OL
		{
			IPS::Properties::Bool% get()
			{
				return m_OL;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Reset/Gain Enhancement")]
		[IPS::Properties::GridOrder(304)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% RG
		{
			IPS::Properties::Bool% get()
			{
				return m_RG;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Scale Setpoint Flag")]
		[IPS::Properties::GridOrder(305)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% SC
		{
			IPS::Properties::Bool% get()
			{
				return m_SC;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Loop Update Too Fast")]
		[IPS::Properties::GridOrder(306)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% TF
		{
			IPS::Properties::Bool% get()
			{
				return m_TF;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Derivative Rate Action")]
		[IPS::Properties::GridOrder(307)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% DA
		{
			IPS::Properties::Bool% get()
			{
				return m_DA;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Deadband")]
		[IPS::Properties::GridOrder(308)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% DB
		{
			IPS::Properties::Bool% get()
			{
				return m_DB;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Output Alarm Upper Limit")]
		[IPS::Properties::GridOrder(309)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% UL
		{
			IPS::Properties::Bool% get()
			{
				return m_UL;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Output Alarm Lower Limit")]
		[IPS::Properties::GridOrder(310)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% LL
		{
			IPS::Properties::Bool% get()
			{
				return m_LL;
			}
		}
		
		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Setpoint Out Of Range")]
		[IPS::Properties::GridOrder(311)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% SP
		{
			IPS::Properties::Bool% get()
			{
				return m_SP;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("PV Out Of Range")]
		[IPS::Properties::GridOrder(312)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% PV
		{
			IPS::Properties::Bool% get()
			{
				return m_PV;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("PID Done")]
		[IPS::Properties::GridOrder(313)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% DN
		{
			IPS::Properties::Bool% get()
			{
				return m_DN;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("PID Rational Approximation")]
		[IPS::Properties::GridOrder(314)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% RA
		{
			IPS::Properties::Bool% get()
			{
				return m_RA;
			}
		}

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("PID Enable")]
		[IPS::Properties::GridOrder(315)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Control Block"})]
		virtual property IPS::Properties::Bool% EN
		{
			IPS::Properties::Bool% get()
			{
				return m_EN;
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
		virtual property IPS::Properties::Double% SPV
		{
			IPS::Properties::Double% get()
			{
				return m_SPV;
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
			m_BaseWord					= m_BaseWord.Parse(Property.Value->Split(':')[1]);			
			m_BaseElement.Value			= Property.Value->Split(':')[0] + ":";
			ControlBlock.Value			= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 0 ).ToString());			// Control Block
			Setpoint.ValueAsObject		= Get_Property(m_BaseElement.Value + (m_BaseWord + 2 ).ToString());						// Setpoint
			Kc.Value					= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 3 ).ToString()) / (10.0 + RG.Value * 90.0);	// Controller Gain
			Ti.Value					= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 4 ).ToString()) / (10.0 + RG.Value * 90.0);	// Reset
			Td.Value					= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 5 ).ToString()) / 100.0;	// Rate
			FFb.ValueAsObject			= Get_Property(m_BaseElement.Value + (m_BaseWord + 6 ).ToString());	// Feed Forward Bias
			Smax.ValueAsObject			= Get_Property(m_BaseElement.Value + (m_BaseWord + 7 ).ToString());	// Setpoint Max
			Smin.ValueAsObject			= Get_Property(m_BaseElement.Value + (m_BaseWord + 8 ).ToString());	// Setpoint Min
			Deadband.ValueAsObject		= Get_Property(m_BaseElement.Value + (m_BaseWord + 9 ).ToString());	// Deadband
			Omax.ValueAsObject			= Get_Property(m_BaseElement.Value + (m_BaseWord + 11).ToString());	// Output Max (CV%)
			Omin.ValueAsObject			= Get_Property(m_BaseElement.Value + (m_BaseWord + 12).ToString());	// Output Min (CV%)
			LoopUpdate.Value			= (double) Get_Property(m_BaseElement.Value + (m_BaseWord + 13).ToString()) / 100;	// Loop Update
			SPV.ValueAsObject			= Get_Property(PV_Source.Value);									// Process Variable
			CV.ValueAsObject			= Get_Property(CV_Source.Value);									// Controlled Variable (CV%)

			if (Smax.Value == Smin.Value)
				SC.Value				= true;
			else
				SC.Value				= false;			
		}

		virtual void Deactivate_Compound() override
		{
			Set_Property(Property.Value, ControlBlock);
		}

		virtual void Execute(double) override;

		virtual void Step(double dDt) override
		{
			// Equation: 
			// Output = Kc * [Error + (E)dt / Ti + Td * D(-PV)/df] + bias
			//////////////////////////////////////////////////////////////
			SPV.ValueAsObject			= Get_Property(PV_Source.Value);									// Process Variable
			
			if (SC.Value)
			{
				if (Setpoint.Value < 0)
					Setpoint.Value		= 0.0;
				else if (Setpoint.Value > 16383.0)
					Setpoint.Value		= 16383.0;
				
				if (SPV.Value < 0)
					SPV.Value			= 0.0;
				else if (SPV.Value > 16383.0)
					SPV.Value			= 16383.0;		
			}
			else
			{
				if (Setpoint.Value < Smin.Value)
					Setpoint.Value		= Smin.Value;
				else if (Setpoint.Value > Smax.Value)
					Setpoint.Value		= Smax.Value;
				
				if (SPV.Value < Smin.Value)
					SPV.Value			= Smin.Value;
				else if (SPV.Value > Smax.Value)
					SPV.Value			= Smax.Value;				
			}

			m_Setpoint.ValueAsObject	= Get_Property(m_BaseElement.Value + (m_BaseWord + 2 ).ToString());	// Setpoint

			SE.Value					= (CM.Value ? SPV.Value - Setpoint.Value : Setpoint.Value - SPV.Value);

			if (abs(SE.Value) <= Deadband.Value)
			{
				if (SE.Value * m_Error_prev < 0)
				{
					DB.Value				= true;
					SE.Value				= 0.0;
				}
			}
			else
				DB.Value					= false;

			// Anti-Windup
			if (UL.Value == false && LL.Value == false)
				m_Integral.Value	   += SE.Value * (dDt / LoopUpdate.Value);

			Int_Sum.Value				= m_Integral.Value / Ti.Value;
			m_Deriv.Value				= (m_Error_prev.Value - SE.Value) / (dDt / LoopUpdate.Value);

			if (Input.Value == false)
				m_Integral.Value		= 0.0;

			if (AM.Value == false)		// Auto Mode (AM = 0)
				CV.Value				= Kc.Value * (SE.Value + Int_Sum.Value  + Td.Value * m_Deriv.Value) + FFb.Value;
			else
				CV.Value				= Setpoint.Value;

			m_Error_prev.Value			= SE.Value;
			CV_Output.Value				= CV.Value / 163.84;

			// Output Limiting and Alarm
			if (CV_Output.Value > Omax.Value)
			{
				if (OL.Value)
				{
					CV.Value			= (Smax.Value - Smin.Value) * Omax.Value / 100;
					CV_Output.Value		= Omax.Value;
				}

				UL.Value				= true;
				LL.Value				= false;
			}
			else if (CV_Output.Value < Omin.Value)
			{
				if (OL.Value)
				{
					CV.Value			= (Smax.Value - Smin.Value) * Omin.Value / 100;
					CV_Output.Value		= Omin.Value;
				}

				UL.Value				= false;
				LL.Value				= true;
			}
			else if (Omin.Value < CV_Output.Value && CV_Output.Value < Omax.Value)
			{
				UL.Value				= false;
				LL.Value				= false;
			}	

			if (SC.Value)
			{
				if (CV.Value < 0)
					CV.Value			= 0.0;
				else if (CV.Value > 16383.0)
					CV.Value			= 16383.0;
			}
			else
			{	
				if (CV.Value < Smin.Value)
					CV.Value			= Smin.Value;
				else if (CV.Value > Smax.Value)
					CV.Value			= Smax.Value;
			}	

			Set_Property(CV_Source.Value, CV);
			Set_Property(Property.Value, m_ControlBlock);
			Set_Property(m_BaseElement.Value + (m_BaseWord + 16).ToString(), CV_Output);		
		}

	public:
		
		IPS::Properties::Double			m_ControlBlock;
		IPS::Properties::Double			m_Length;
		IPS::Properties::Double			m_Value;
		IPS::Properties::Text			m_PV_Source;
		IPS::Properties::Text			m_CV_Source;
		IPS::Properties::Double			m_PV_Value;
		IPS::Properties::Double			m_CV_Value;

	private:

		int								m_BaseWord;
		IPS::Properties::Text			m_BaseElement;
		IPS::Properties::Double			m_Setpoint;
		IPS::Properties::Double			m_Error;
		IPS::Properties::Double			m_Kc;
		IPS::Properties::Double			m_Ti;
		IPS::Properties::Double			m_Td;
		IPS::Properties::Double			m_FFb;
		IPS::Properties::Double			m_Smax;
		IPS::Properties::Double			m_Smin;
		IPS::Properties::Double			m_Deadband;
		IPS::Properties::Double			m_Omax;
		IPS::Properties::Double			m_Omin;
		IPS::Properties::Double			m_LoopUpdate;
		IPS::Properties::Double			m_SPV;
		IPS::Properties::Double			m_SE;
		IPS::Properties::Double			m_CV_Output;
		IPS::Properties::Double			m_Integral;
		IPS::Properties::Double			m_Int_Sum;
		IPS::Properties::Double			m_Deriv;
		IPS::Properties::Double			m_PV_Prev;
		IPS::Properties::Double			m_Error_prev;
		
				
		IPS::Properties::Double			m_Slope;
		IPS::Properties::Double			m_Offset;

		//
		// Control Block Bits
		//

		  IPS::Properties::Bool			m_TM;
		  IPS::Properties::Bool			m_AM;
		  IPS::Properties::Bool			m_CM;
		  IPS::Properties::Bool			m_OL;
		  IPS::Properties::Bool			m_RG;
		  IPS::Properties::Bool			m_SC;
		  IPS::Properties::Bool			m_TF;
		  IPS::Properties::Bool			m_DA;
		  IPS::Properties::Bool			m_DB;
		  IPS::Properties::Bool			m_UL;
		  IPS::Properties::Bool			m_LL;
		  IPS::Properties::Bool			m_SP;
		  IPS::Properties::Bool			m_PV;
		  IPS::Properties::Bool			m_DN;
		  IPS::Properties::Bool			m_RA;
		  IPS::Properties::Bool			m_EN;
	};
}