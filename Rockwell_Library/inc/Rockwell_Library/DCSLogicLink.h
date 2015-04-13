#pragma once

using namespace System;

#pragma region IPS_NAMESPACE
namespace Rockwell_Library {
	
	#pragma region IPS_LINK
	
	#pragma region IPS_ATTRIBUTES
	[IPS::Plugin::LibraryInfo("DCSLogicLink", IPS::Plugin::Visibility::VISIBLE, ""), 
	IPS::Plugin::LibraryImage("Link.png"), 
	IPS::Plugin::Width(1.5), 
	IPS::Plugin::LinkColor("Blue"), 
	IPS::Plugin::ArrowHeadSize(0), 
	IPS::Plugin::Pattern(System::Drawing::Drawing2D::DashStyle::Solid)]
	#pragma endregion IPS_ATTRIBUTES
	public ref class DCSLogicLink : public DCS::Links::Bool_BoolLink
	{
		#pragma region IPS_CONSTRUCTORS
		
		public: DCSLogicLink();
		#pragma endregion IPS_CONSTRUCTORS
		
		#pragma region IPS_PROPERTIES
		
		#pragma endregion IPS_PROPERTIES
		
		#pragma region IPS_METHODS
		
		public: virtual System::Void InitProperties() override;
		
		#pragma endregion IPS_METHODS
		
		#pragma region IPS_FIELDS
		
		#pragma endregion IPS_FIELDS
		
		
	};
	#pragma endregion IPS_LINK
	
}
#pragma endregion IPS_NAMESPACE
