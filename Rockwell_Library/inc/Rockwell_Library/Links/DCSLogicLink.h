#pragma once
#include "Stdafx.h"

using namespace System;
using namespace IPS::Plugin;

namespace Rockwell_Library
{    
    [IPS::Plugin::LibraryInfo("Rockwell DCS Logic Link", IPS::Plugin::Visibility::VISIBLE, ""), 
    IPS::Plugin::LibraryImage("Link.png"), 
    IPS::Plugin::Width(1.5), 
    IPS::Plugin::LinkColor("Blue"), 
    IPS::Plugin::ArrowHeadSize(0.0), 
    IPS::Plugin::Pattern(System::Drawing::Drawing2D::DashStyle::Solid)]
    public ref class DCSLogicLink : public LinkBase
    {
        public:
			
			DCSLogicLink();
        
        public:
			
			virtual System::Void InitProperties() override;
        
    };
    
}