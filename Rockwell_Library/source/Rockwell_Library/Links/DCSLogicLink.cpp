#include "Stdafx.h"
#include "Rockwell_Library/Links/DCSLogicLink.h"
#include "Ports.h"

using namespace System;
using namespace DCS::Ports;
namespace Rockwell_Library {
    
    DCSLogicLink::DCSLogicLink() : IPS::Plugin::LinkBase(DCSPortBase::typeid, DCSPortBase::typeid)
    {
    }
    
    System::Void DCSLogicLink::InitProperties()
    {
        IPS::Plugin::LinkBase::InitProperties();
    }
    
}