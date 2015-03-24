#include "Stdafx.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

namespace Rockwell_Library {

	void DCSLogicTaskDrawingTextProvider::GetDrawingText(Object^ objectToProvideMenuFor, System::Collections::Generic::List<IPS::Plugin::DrawingText>^ returnDrawingTexts)
	{
		l_pDCSLogicComponent = dynamic_cast<DCSLogicComponent^>(objectToProvideMenuFor);
		
		if (l_pDCSLogicComponent != nullptr)
		{
			returnDrawingTexts->Clear();			
			if (l_pDCSLogicComponent->TypeDescription == "Rung")
			{
				l_RungName.Location						= IPS::Plugin::TextLocation::Center;
				l_RungName.Text							= l_pDCSLogicComponent->Identifier->ToString();

				returnDrawingTexts->Add( l_RungName );
			}
			else
			{
				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Top;
				l_DescriptionDrawingData.Text			= l_pDCSLogicComponent->UserDescription->Value;
				l_DescriptionDrawingData.Bounds.Width	= 50.0;
				l_DescriptionDrawingData.Bounds.Height	= 50.0;
				Drawing::SizeF::Add(Drawing::Size(50,50), l_DescriptionDrawingData.Bounds.Size);

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
		}
	}
}