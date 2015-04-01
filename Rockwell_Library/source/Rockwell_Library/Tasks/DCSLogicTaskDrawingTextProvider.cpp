#include "Stdafx.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

namespace Rockwell_Library {

#define PAD 39

	ref class MathBase;

	String^ DCSLogicTaskDrawingTextProvider::SplitString(String^ stringToSplit, int width)
	{		
		String^ splitstring = "";

		if(stringToSplit->Length > width)
		{
			int counter = 0;

			for each(System::Char l_char in stringToSplit->ToCharArray())
			{
				counter++;
				if(counter > 20)
				{
					if(l_char == ' ')
					{
							l_char = '\n';
							counter = 0;
					}
				}
		 
				splitstring += l_char.ToString();
			}
		}
		else
				splitstring = stringToSplit;

		return splitstring;
	}

	void DCSLogicTaskDrawingTextProvider::GetDrawingText(Object^ objectToProvideMenuFor, System::Collections::Generic::List<IPS::Plugin::DrawingText>^ returnDrawingTexts)
	{
		l_pDCSLogicComponent = dynamic_cast<DCSLogicComponent^>(objectToProvideMenuFor);
		
		if (l_pDCSLogicComponent != nullptr)
		{
			returnDrawingTexts->Clear();			
			if (l_pDCSLogicComponent->Name == "Rung")
			{
				l_RungName.Location						= IPS::Plugin::TextLocation::Center;
				l_RungName.Text							= l_pDCSLogicComponent->Identifier->ToString();

				returnDrawingTexts->Add( l_RungName );
			}
			else if (l_pDCSLogicComponent->ShowSource.Value == true &&
					(l_pDCSLogicComponent->TypeDescription == "Relay Type Instructions" ||
					 l_pDCSLogicComponent->Name == "LBL" ||
					 l_pDCSLogicComponent->Name == "JMP"))
			{
				for each (Char character in l_pDCSLogicComponent->Property.Value->ToCharArray())
				{
					if (character == '/' || character == '.')
					{
						character = '\n';
						string = character.ToString();
						string += character.ToString();
					}
					string += character.ToString();
				}				
				
				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
				l_DescriptionDrawingData.Text			= string;

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
			else if (l_pDCSLogicComponent->TypeDescription == "Advanced Math Instructions")
			{
				string =	((Char)'\n').ToString();
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Source_A")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value_A")->ValueAsObject)->ToString()->PadLeft(PAD);
				string +=	"<";
				string +=	((Char)'\n').ToString();
				string +=	((Char)'\n').ToString();
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Source_B")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value_B")->ValueAsObject)->ToString()->PadLeft(PAD);	
				string +=	"<";	

				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
				l_DescriptionDrawingData.Text			= string;

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
			else if (l_pDCSLogicComponent->TypeDescription == "Comparison Instructions")
			{
				string =	((Char)'\n').ToString();
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Source_A")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value_A")->ValueAsObject)->ToString()->PadLeft(PAD);
				string +=	"<";
				string +=	((Char)'\n').ToString();
				string +=	((Char)'\n').ToString();
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Source_B")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value_B")->ValueAsObject)->ToString()->PadLeft(PAD);	
				string +=	"<";

				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
				l_DescriptionDrawingData.Text			= string;

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
			else if (l_pDCSLogicComponent->TypeDescription == "Math Instructions")
			{
				if (l_pDCSLogicComponent->Name == "CLR")
				{
					string =	((Char)'\n').ToString();
					string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Property")->ValueAsObject)->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	((System::Int32^)l_pDCSLogicComponent->GetPropertyFromPropID("Value")->ValueAsObject)->ToString()->PadLeft(PAD);
					string +=	"<";
					string +=	((Char)'\n').ToString();
				}
				else
				{
					string =	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();
					string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Source_A")->ValueAsObject)->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value_A")->ValueAsObject)->ToString()->PadLeft(PAD);
					string +=	"<";
					string +=	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();
					string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Source_B")->ValueAsObject)->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value_B")->ValueAsObject)->ToString()->PadLeft(PAD);	
					string +=	"<";
					string +=	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();
					string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Property")->ValueAsObject)->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value")->ValueAsObject)->ToString()->PadLeft(PAD);
					string +=	"<";	
				}

				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
				l_DescriptionDrawingData.Text			= string;

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
			else if (l_pDCSLogicComponent->TypeDescription == "File Manipulation Instructions")
			{
				string =	((Char)'\n').ToString();		
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Property")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();	
				string +=	((Char)'\n').ToString();
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Dest")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();
				string +=	((Char)'\n').ToString();		
				string +=	((System::Int32^)l_pDCSLogicComponent->GetPropertyFromPropID("Length")->ValueAsObject)->ToString()->PadLeft(PAD);	

				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
				l_DescriptionDrawingData.Text			= string;

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
			else if (l_pDCSLogicComponent->Name == "MOV")
			{
				string =	((Char)'\n').ToString();		
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Property")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Value")->ValueAsObject)->ToString()->PadLeft(PAD);
				string +=	"<";
				string +=	((Char)'\n').ToString();
				string +=	((Char)'\n').ToString();	
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Dest")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Dest_Value")->ValueAsObject)->ToString()->PadLeft(PAD);	
				string +=	"<";

				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
				l_DescriptionDrawingData.Text			= string;

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
			else if (l_pDCSLogicComponent->Name == "TON")
			{
				string =	((Char)'\n').ToString();
				string +=	((Char)'\n').ToString();	
				string +=	((String^)l_pDCSLogicComponent->GetPropertyFromPropID("Property")->ValueAsObject)->PadLeft(PAD);
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Timebase")->ValueAsObject)->ToString()->PadLeft(PAD);
				string +=	"<";
				string +=	((Char)'\n').ToString();
				string +=	((Char)'\n').ToString();
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("Preset")->ValueAsObject)->ToString()->PadLeft(PAD);
				string +=	"<";
				string +=	((Char)'\n').ToString();		
				string +=	((System::Double^)l_pDCSLogicComponent->GetPropertyFromPropID("ACC")->ValueAsObject)->ToString()->PadLeft(PAD);	
				string +=	"<";

				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
				l_DescriptionDrawingData.Text			= string;

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
			else
			{
				l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Top;
				l_DescriptionDrawingData.Text			= SplitString(l_pDCSLogicComponent->UserDescription->Value, (int)(dynamic_cast<DCS::Components::DCSComponentBase^>(l_pDCSLogicComponent)->DefaultSize.Width));

				returnDrawingTexts->Add( l_DescriptionDrawingData );
			}
		}
	}
}