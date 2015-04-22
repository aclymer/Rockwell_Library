#include "Stdafx.h"
#include "Rockwell_Library/Tasks/DCSLogicTaskDrawingTextProvider.h"
#include "Rockwell_Library/Components/Hidden/DCSLogicComponent.h"
#include "Rockwell_Library/Tasks/DCSLogicTask.h"
#include "Rockwell_Library/Components/Hidden/MathBase.h"
#include "Rockwell_Library/Components/Visible/COP.h"
#include "Rockwell_Library/Components/Visible/FLL.h"
#include "Rockwell_Library/Components/Visible/MOV.h"
#include "Rockwell_Library/Components/Visible/TON.h"
#include "Rockwell_Library/Properties/T_Property.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

namespace Rockwell_Library
{

#define PAD 39

	//ref class MathBase;

	String^ DCSLogicTaskDrawingTextProvider::SplitString(String^ stringToSplit, int width)
	{		
		String^ splitstring = "";

		if (stringToSplit == nullptr)
			return stringToSplit;

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
					else
					{
						splitstring += ((Char)('\n')).ToString();
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
			if (l_pDCSLogicComponent->ShowSource.Value == true || DCSLogicTask::m_UpdateTextValues.Value == true)
			{
				returnDrawingTexts->Clear();			
				if (l_pDCSLogicComponent->Name == "Rung")
				{
					l_RungName.Location						= IPS::Plugin::TextLocation::Center;
					l_RungName.Text							= l_pDCSLogicComponent->Identifier->ToString();

					returnDrawingTexts->Add( l_RungName );
				}
				else if (l_pDCSLogicComponent->TypeDescription == "Relay Type Instructions" ||
						 l_pDCSLogicComponent->Name == "LBL" ||
						 l_pDCSLogicComponent->Name == "JMP")
				{
					string = "";
					Char character;
					for each (character in l_pDCSLogicComponent->Property.Value->ToCharArray())
					{
						if (character == '/' || character == '.')
						{
							character = '\n';
							string += character.ToString();
							string += character.ToString();
						}
						string += character.ToString();
					}	

					if (!string->Contains("\n"))
					{
						character = '\n';
						string += character.ToString();
						string += character.ToString();
					}
				
					l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
					l_DescriptionDrawingData.Text			= string;

					returnDrawingTexts->Add( l_DescriptionDrawingData );
				}
				else if (l_pDCSLogicComponent->TypeDescription == "Advanced Math Instructions")
				{
					string =	((Char)'\n').ToString();
					string +=	dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Source_A.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Value_A.Value), 4).ToString()->PadLeft(PAD);
					string +=	"<";
					string +=	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();
					string +=	SplitString(dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Source_B.Value, 21)->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Value_B.Value), 4).ToString()->PadLeft(PAD);	
					string +=	"<";	

					l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
					l_DescriptionDrawingData.Text			= string;

					returnDrawingTexts->Add( l_DescriptionDrawingData );
				}
				else if (l_pDCSLogicComponent->TypeDescription == "Comparison Instructions")
				{
					string =	((Char)'\n').ToString();
					string +=	dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Source_A.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Value_A.Value), 4).ToString()->PadLeft(PAD);
					string +=	"<";

					if (l_pDCSLogicComponent->Name == "LIM")
					{
						string +=	((Char)'\n').ToString();
						string +=	((Char)'\n').ToString();
						string +=	l_pDCSLogicComponent->Property.Value->PadLeft(PAD);
						string +=	((Char)'\n').ToString();		
						string +=	Math::Round((l_pDCSLogicComponent->Value.Value), 4).ToString()->PadLeft(PAD);	
						string +=	"<";
					}

					string +=	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();
					string +=	dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Source_B.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Value_B.Value), 4).ToString()->PadLeft(PAD);	
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
						string +=	l_pDCSLogicComponent->Property.Value->PadLeft(PAD);
						string +=	((Char)'\n').ToString();		
						string +=	l_pDCSLogicComponent->Value.Value.ToString()->PadLeft(PAD);
						string +=	"<";
						string +=	((Char)'\n').ToString();
					}
					else
					{
						string =	((Char)'\n').ToString();
						string +=	((Char)'\n').ToString();
						string +=	dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Source_A.Value->PadLeft(PAD);
						string +=	((Char)'\n').ToString();		
						string +=	Math::Round((dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Value_A.Value), 4).ToString()->PadLeft(PAD);
						string +=	"<";
						string +=	((Char)'\n').ToString();
						string +=	((Char)'\n').ToString();
						string +=	dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Source_B.Value->PadLeft(PAD);
						string +=	((Char)'\n').ToString();		
						string +=	Math::Round((dynamic_cast<MathBase^>(l_pDCSLogicComponent)->Value_B.Value), 4).ToString()->PadLeft(PAD);	
						string +=	"<";
						string +=	((Char)'\n').ToString();
						string +=	((Char)'\n').ToString();
						string +=	l_pDCSLogicComponent->Property.Value->PadLeft(PAD);
						string +=	((Char)'\n').ToString();		
						string +=	Math::Round((l_pDCSLogicComponent->Value.Value), 4).ToString()->PadLeft(PAD);
						string +=	"<";	
					}

					l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
					l_DescriptionDrawingData.Text			= string;

					returnDrawingTexts->Add( l_DescriptionDrawingData );
				}
				else if (l_pDCSLogicComponent->TypeDescription == "File Manipulation Instructions")
				{
					string =	((Char)'\n').ToString();		
					string +=	l_pDCSLogicComponent->Property.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();	
					string +=	((Char)'\n').ToString();
					string +=	l_pDCSLogicComponent->Name == "FLL" ?
								dynamic_cast<FLL^>(l_pDCSLogicComponent)->Dest.Value->PadLeft(PAD) :
								dynamic_cast<COP^>(l_pDCSLogicComponent)->Dest.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();		
					string +=	l_pDCSLogicComponent->Name == "FLL" ?
								dynamic_cast<FLL^>(l_pDCSLogicComponent)->Length.Value.ToString()->PadLeft(PAD) :
								dynamic_cast<COP^>(l_pDCSLogicComponent)->Length.Value.ToString()->PadLeft(PAD);	

					l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
					l_DescriptionDrawingData.Text			= string;

					returnDrawingTexts->Add( l_DescriptionDrawingData );
				}
				else if (l_pDCSLogicComponent->Name == "JSR")
				{
					string =	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();		
					string +=	l_pDCSLogicComponent->Property.Value->PadLeft(PAD);
				
					l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
					l_DescriptionDrawingData.Text			= string;

					returnDrawingTexts->Add( l_DescriptionDrawingData );
				}
				else if (l_pDCSLogicComponent->Name == "MOV")
				{
					string =	((Char)'\n').ToString();		
					string +=	l_pDCSLogicComponent->Property.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<MOV^>(l_pDCSLogicComponent)->Value.Value), 4).ToString()->PadLeft(PAD);
					string +=	"<";
					string +=	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();	
					string +=	dynamic_cast<MOV^>(l_pDCSLogicComponent)->Dest.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<MOV^>(l_pDCSLogicComponent)->Dest_Value.Value), 4).ToString()->PadLeft(PAD);	
					string +=	"<";

					l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
					l_DescriptionDrawingData.Text			= string;

					returnDrawingTexts->Add( l_DescriptionDrawingData );
				}
				else if (l_pDCSLogicComponent->Name == "TON")
				{
					string =	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();	
					string +=	l_pDCSLogicComponent->Property.Value->PadLeft(PAD);
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<TON^>(l_pDCSLogicComponent)->Timebase.Value), 4).ToString()->PadLeft(PAD);
					string +=	"<";
					string +=	((Char)'\n').ToString();
					string +=	((Char)'\n').ToString();
					string +=	Math::Round((dynamic_cast<TON^>(l_pDCSLogicComponent)->Preset.Value), 4).ToString()->PadLeft(PAD);
					string +=	"<";
					string +=	((Char)'\n').ToString();		
					string +=	Math::Round((dynamic_cast<TON^>(l_pDCSLogicComponent)->ACC.Value), 4).ToString()->PadLeft(PAD);	
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
		else if (dynamic_cast<T_Property^>(objectToProvideMenuFor) != nullptr)
		{
			l_DescriptionDrawingData.Location		= IPS::Plugin::TextLocation::Center;
			l_DescriptionDrawingData.Text			= dynamic_cast<T_Property^>(objectToProvideMenuFor)->Identifier->Value;

			returnDrawingTexts->Add( l_DescriptionDrawingData );
		}
	}
}