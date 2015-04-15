#pragma once
#include "Stdafx.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"

using namespace System;

namespace Rockwell_Library
{
	[IPS::Plugin::LibraryInfo("Text Property", IPS::Plugin::Visibility::VISIBLE, "Text Property")]
	[IPS::Plugin::LibrarySize(200, 25)]
	[IPS::Plugin::LibraryCategory("Properties")]
	[IPS::Plugin::LibraryRelativeSize(false)]
	[IPS::Plugin::LibraryImage("T_Property.png")]
	[IPS::Plugin::DrawingTextProvider(DCSLogicTaskDrawingTextProvider::typeid)]
	public ref class T_Property : public IPS::Plugin::ComponentBase
	{
	public:

		T_Property::T_Property()
		{
			Value.Visible		= true;
			Value.Value			= "Status String";
		}

		virtual void InitProperties() override
		{
			IPS::Plugin::ComponentBase::InitProperties();
		}
		
		//
		// ICustomPersistString overrides
		//
		
	public:

		[IPS::Properties::PropertyUsage(IPS::Properties::UseProperty::DYNAMIC)]
		[IPS::Properties::DisplayName("Text")]
		[IPS::Properties::GridOrder(1)]
		[IPS::Properties::GridCategory(gcnew cli::array< System::String^  >(1) {"Property"})]
		property IPS::Properties::Text% Value
		{
			IPS::Properties::Text% get()
			{
				return m_Text;
			}
		}

	private:

		IPS::Properties::Text			m_Text;

	};

}