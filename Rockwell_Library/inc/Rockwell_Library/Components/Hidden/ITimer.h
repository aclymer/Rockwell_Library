#pragma once

using namespace System;
using namespace System::Reflection;
using namespace System::Collections::Generic;
using namespace DCS::Ports::Bool;
using namespace DCS::Ports::Double;
using namespace DCS::Ports::Integer;

namespace Rockwell_Library
{
	public interface class ITimer
	{

	public:

		void Step(double Ts);
	};

}