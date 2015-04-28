#pragma once
#include "Stdafx.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Collections;

namespace Rockwell_Library
{
	public ref class SortComponentByYPos : Generic::Comparer<IPS::Core::Component^>
	{
	public:
		
		virtual int Compare(IPS::Core::Component^ x, IPS::Core::Component^ y) override
		{
			x_ComponentDrawingData = dynamic_cast<IPS::Core::ComponentDrawingData^>(x);
			y_ComponentDrawingData = dynamic_cast<IPS::Core::ComponentDrawingData^>(y);

			if (x_ComponentDrawingData != nullptr && y_ComponentDrawingData != nullptr)
			{
				float temp = x_ComponentDrawingData->CenterPoint.Y - y_ComponentDrawingData->CenterPoint.Y;
				if (temp < 0)
					return -1;
				if (temp > 0)
					return 1;
			}

			return 0;
		}

	private:

		IPS::Core::ComponentDrawingData^	x_ComponentDrawingData;
		IPS::Core::ComponentDrawingData^	y_ComponentDrawingData;
	};
}