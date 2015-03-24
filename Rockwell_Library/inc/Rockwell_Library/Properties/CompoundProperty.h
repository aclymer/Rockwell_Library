#pragma once
#include <bitset>

using namespace System;
using namespace System::Collections::Generic;

namespace Rockwell_Library {

	public ref class CompoundProperty : IPS::Properties::ObjectProperty
	{

	public:

		Object^ GetValue(bool p_bScaled)
		{
			if (p_bScaled == true)
			{
				return GetValueScaled();
			}
			else
			{
				return GetValueUnscaled();
			}
		}

		virtual void Ramp(double p_dIncrement)
		{
		}

		virtual Object^ GetValueUnscaled()
		{
			return ValueAsObject;
		}

		virtual Object^ GetValueScaled()
		{
			return GetValueUnscaled();
		}

		//
		// Info
		//

		virtual property String^ Name;
		virtual property String^ Description;
		virtual property String^ Default;
		virtual property String^ UnitsRange;
		virtual property bool CanConnect;
		virtual property bool CanSet;
		virtual property bool IsVisible;

		//
		// Status property
		//

		// Generic Status BITS
		virtual property bool B1
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[31];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[31] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B2
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[30];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[30] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B3
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[29];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[29] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B4
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[28];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[28] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B5
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[27];
			}

			virtual void set( bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[27] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B6
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[26];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[26] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B7
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[25];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[25] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B8
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[24];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[24] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B9
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[23];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[23] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B10
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[22];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[22] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B11
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[21];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[21] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B12
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[20];
			}

			virtual void set( bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[20] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B13
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[19];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[19] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B14
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[18];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[18] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B15
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[17];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[17] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		virtual property bool B16
		{
			virtual bool get()
			{
				return (bool) ((std::bitset<32>) this->Status)[16];
			}

			virtual void set(bool state)
			{
				std::bitset<32> temp = this->Status;
				temp[16] = state;
				this->Status = temp.to_ulong();
				return;
			}
		}
		
		//
		// Status property
		//
		property bool DN
		{
			bool get()
			{
				return this->B1;											// BIT 15
			}
			void set(bool state)
			{
				this->B1 = state;											// BIT 15
				return;
			}
		}

		virtual property int Status
		{
			virtual int get()
			{
				return m_Status;
			}
			virtual void set(int value)
			{
				m_Status = value;
			}
		}

	private:

		int m_Status;

	public:

		//
		// Associations
		//

		virtual property IPS::Core::Port^ AssociatedDCSPort;

		virtual property CompoundProperty^ ConnectedCompoundProperty;

		//
		// Miscellanious
		//

		virtual String^ GetActiveText()
		{
			return String::Empty;
		}

		virtual bool IsInput()
		{
			if (AssociatedDCSPort != nullptr)
			{
				return (AssociatedDCSPort->InLinkCount > 0);
			}
			return false;
		}

		virtual bool IsConnected()
		{
			if (AssociatedDCSPort != nullptr)
			{
				if (AssociatedDCSPort->InLinkCount > 0)
				{
					return (AssociatedDCSPort->InLinks->Count > 0);
				}
				else
				{
					return (AssociatedDCSPort->OutLinks->Count > 0);
				}
			}
			return false;
		}
	};
}
