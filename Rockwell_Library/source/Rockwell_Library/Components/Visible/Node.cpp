#include "Stdafx.h"
#include "Rockwell_Library/Components/Visible/Node.h"

namespace Rockwell_Library
{
	void Node::Execute(double p_dTimestep)
	{
		Output.Value = Input.Value;

		if (l_InLinks != nullptr && l_InLinks->Count > 1)
		{
			for each (IPS::Core::Link^ l_ThisInLink in l_InLinks)
			{
				l_ThisDCSLink = dynamic_cast<DCS::Links::DCSLinkBase^>(l_ThisInLink);

				if (l_ThisDCSLink != nullptr)
				{
					Output.Value |= (bool)l_ThisDCSLink->FromProperty->ValueAsObject;
				}
			}
		}
	}
}