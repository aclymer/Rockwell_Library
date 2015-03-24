#pragma once
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"

using namespace System;
using namespace System::Windows::Forms;

namespace Rockwell_Library {

	public ref class DCSLogicTaskDrawingTextProvider : DCS::DCSPropertyTextProvider
	{

	public: 

		DCSLogicTaskDrawingTextProvider()
		{
		}

		virtual void GetDrawingText(Object^ objectToProvideMenuFor, System::Collections::Generic::List<IPS::Plugin::DrawingText>^ returnDrawingTexts) override;
		
		property Object^ Context
		{
			virtual void set(Object^ newValue) override
			{
			}
		}
		
		IPS::Plugin::DrawingText		l_DescriptionDrawingData;
		IPS::Plugin::DrawingText		l_RungName;

	private:

		DCSLogicComponent^				l_pDCSLogicComponent;
	};

}