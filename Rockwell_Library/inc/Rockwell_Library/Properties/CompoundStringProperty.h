#pragma once
#include "Rockwell_Library/Properties/CompoundProperty.h"

using namespace System;
using namespace System::ComponentModel;

namespace Rockwell_Library {

	public ref class CompoundStringProperty : CompoundProperty, IPS::Persistence::ICustomPersistString
	{
	public:

		CompoundStringProperty()
		{
		}


		//
		// ICustomPersistString overrides
		//

		virtual String^ GetValuesAsString(IPS::Persistence::PersistMode p_PersistMode)
		{
			return Val;
		}

		virtual void SetValuesFromString(String^ l_sValue)
		{
			Val = l_sValue;
		}

	public:

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Parameter")]
		[IPS::Properties::GridOrder(0x000001)]
		property IPS::Properties::Text% Parameter
		{
			IPS::Properties::Text% get()
			{
				return m_Parameter;
			}
		}

		property String^ Val
		{
			String^ get()
			{
				return m_Parameter.Value;
			}
			void set(String^ value)
			{
				m_Parameter.Value = value;
			}
		}

		[System::Obsolete("Don't use this", true)]
		virtual property Object^ Value
		{
			[System::Obsolete("Don't use this", true)]
			virtual Object^ get() override
			{
				return m_Parameter.Value;
			}
			[System::Obsolete("Don't use this", true)]
			virtual void set(Object^ value) override
			{
				m_Parameter.Value = value->ToString();
			}
		}

	private:

		IPS::Properties::Text m_Parameter;
	};

}