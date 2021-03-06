//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DiplomMain.h"
#include "AboutProgramm.h"
#include "DataForTabels.h"
#include "CreateAndComputeTables.h"
#include <vector>
using std::vector;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
DataForTabels dft;
//CreateAndComputeTables cnc;
vector<CreateAndComputeTables *> cnc;
String fileName;

 int indexi = 0; // ����� �������� ��� ������� �������
 int complite = 0; // �������� ���� ������� ����� ���������� ���������
 // �� ��� ������� ���������

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	 PageControls = 0;
	 selectedExpert = 1;
	 maxExpertFactor = 0;
	 fileName = "";
	 HideComponents();
}

//---------------------------------------------------------------------------
// � ���������
void __fastcall TForm1::N15Click(TObject *Sender)
{
	Application->CreateForm(__classid(TForm2), &Form2);
	Form2->ShowModal();
}

//---------------------------------------------------------------------------
// ����� ������ � ����������
void __fastcall TForm1::N11Click(TObject *Sender)
{
   if(FontDialog1->Execute())
			Form1->Font = FontDialog1->Font;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
	for(int i=0;i<Memo1->Lines->Count;i++)
		if(Memo1->Lines->Strings[i]=="")   //���� ������ ������
			 Memo1->Lines->Delete(i); //������� ��� ������

	 for(int i=0;i<Memo2->Lines->Count;i++)
		if(Memo2->Lines->Strings[i]=="")   //���� ������ ������
			 Memo2->Lines->Delete(i); //������� ��� ������

	 for(int i=0;i<Memo3->Lines->Count;i++)
		if(Memo3->Lines->Strings[i]=="")   //���� ������ ������
			 Memo3->Lines->Delete(i); //������� ��� ������

	if(Memo1->Lines->Count < 2)
	{
		MessageDlg("��������� ����������� ������ ���� ������ ��� ����� 2!",
						mtInformation, TMsgDlgButtons() << mbOK, 0);
		Memo1->SetFocus();
	}
	else
	if(Memo2->Lines->Count < 1)
	{
			MessageDlg("��������� ��������� ������ ���� ������ ��� ����� 1!",
						mtInformation, TMsgDlgButtons() << mbOK, 0);
		Memo2->SetFocus();
	}
	else
	if(Memo3->Lines->Count < 1)
	{
		MessageDlg("������ ���� ���� �� ���� �������!",
						mtInformation, TMsgDlgButtons() << mbOK, 0);
		Memo3->SetFocus();
	}
	else
	{
	 //�������� ���������� � ���������� ������
	dft.getDataForTabels(Memo1, Memo2, Memo3);

	Label4->Caption = dft.getExpertName(selectedExpert - 1);

	if(dft.getExpertsCount() > 1)
		Button3->Enabled = true;

	createContrils();

	for(int i = 0; i < dft.getExpertsCount(); i++)
	cnc[i]->createTables(&dft, PageControls[i]);

	Button1->Enabled = false;
	ShowComponents();
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	double maxFactor = 0;
   for(; indexi < dft.getExpertsCount(); )
   {
		try
		{
			cnc[indexi]->runCompute();
			indexi++;
			complite++;
		}
		catch(...)
		{
			ShowSelecterPage(indexi);
			selectedExpert = indexi+1;
			Label4->Caption = dft.getExpertName(indexi);
			EnableButtons();
			break;
		}
   }

   if(complite == dft.getExpertsCount())
   {
		Button2->Visible = false;
		Button5->Visible = true;

		maxFactor = cnc[0]->getFactor();
		Label4->Caption = dft.getExpertName(0);
		Label4->Color = clGreen;
		maxExpertFactor = 1;
		selectedExpert = 1;
		EnableButtons();
		ShowSelecterPage(0);

		 for(int kof = 0; kof < dft.getExpertsCount(); kof++)
		{
		   if (cnc[kof]->getFactor() > maxFactor)
		   {
				ShowSelecterPage(kof);
				selectedExpert = kof+1;
				Label4->Caption = dft.getExpertName(kof);
				Label4->Color = clGreen;
				maxExpertFactor = kof+1;
				EnableButtons();
		   }
		}
   }

}

//---------------------------------------------------------------------------
// ���������
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	selectedExpert++;
	if(selectedExpert > 1)
	{
		if(maxExpertFactor != 0)
			maxExpertFactorLbl();
		Button4->Enabled = true; //����������
		Label4->Caption = dft.getExpertName(selectedExpert - 1);
		ShowSelecterPage(selectedExpert-1);
	}

	if(selectedExpert == dft.getExpertsCount())
	{
		if(maxExpertFactor != 0)
			maxExpertFactorLbl();
		Button3->Enabled = false; //���������
	}
}


//---------------------------------------------------------------------------
// ����������
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	selectedExpert--;
	if(selectedExpert == 1)
	{
		if(maxExpertFactor != 0)
			maxExpertFactorLbl();
		Button3->Enabled = true;   //���������
		Button4->Enabled = false; //����������
		Label4->Caption = dft.getExpertName(selectedExpert - 1);
		ShowSelecterPage(selectedExpert-1);
	}
	else
	{
		if(maxExpertFactor != 0)
			maxExpertFactorLbl();
		Button3->Enabled = true; //���������
		Label4->Caption = dft.getExpertName(selectedExpert - 1);
		ShowSelecterPage(selectedExpert-1);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
New();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
New();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TForm1::New()
{
	 deleteControls();
	 selectedExpert = 1;
	 maxExpertFactor = 0;
	 HideComponents();
	 Button2->Visible = false;
	 Button5->Visible = false;
	 Button1->Enabled = true;
	 cnc.clear();
	 vector<CreateAndComputeTables *>().swap(cnc);
	 dft.Clear();
	 fileName = "";
	 indexi = 0 ;
	 complite = 0;
}

void TForm1::maxExpertFactorLbl()
{
	if(selectedExpert == maxExpertFactor)
	  Label4->Color = clGreen;
	else
	Label4->Color = clRed;
}


void TForm1::createContrils()
{
	for(int i = 0; i < dft.getExpertsCount(); i++)
	 cnc.push_back(new CreateAndComputeTables());

	 PageControls = new TPageControl * [dft.getExpertsCount()];

	 for(int i = 0;  i < dft.getExpertsCount(); i++)
	 {
		PageControls[i] = new TPageControl(Form1);
		PageControls[i]->Parent = this;
		PageControls[i]->Left = 19;
		PageControls[i]->Top = 286;
		PageControls[i]->Width = 586;
		PageControls[i]->Height = 214;
		PageControls[i]->MultiLine = true;
		PageControls[i]->ScrollOpposite = true;
		PageControls[i]->TabOrder = 2;
		PageControls[i]->Visible = false;
	}
	PageControls[0]->Visible= true;
}
//---------------------------------------------------------------------------

void TForm1::ShowComponents()
{
	 if(PageControls != 0)
	 {
	 for(int i = 0;  i < dft.getExpertsCount(); i++)
	 {
	   PageControls[i]->Visible = false;
	 }
	 PageControls[0]->Visible= true;
	 }

	 Label4->Visible = true;
	 Button3->Visible = true;
	 Button4->Visible = true;
	 Button2->Visible = true;
}

void TForm1::HideComponents()
{
	 if(PageControls != 0)
	 for(int i = 0;  i < dft.getExpertsCount(); i++)
	 {
	   PageControls[i]->Visible = false;
	 }

	 Label4->Visible = false;
	 Label4->Color = clWhite;
	 Button3->Visible = false;
	 Button4->Visible = false;
	 Button2->Visible = false;
}

void TForm1::ShowSelecterPage(int select)
{
	 if(PageControls != 0)
	 for(int i = 0;  i < dft.getExpertsCount(); i++)
	 {
	   PageControls[i]->Visible = false;
	 }

	 PageControls[select]->Visible = true;
}

void TForm1::EnableButtons()
{
if(selectedExpert == dft.getExpertsCount())
	{
		Button3->Enabled = false; //���������
		Button4->Enabled = true; //����������
	}
	else
	if(selectedExpert == 1)
	{
	  Button4->Enabled = false;  //����������
	  Button3->Enabled = true;   //���������
	}
	else
	if(selectedExpert > 1 && selectedExpert < dft.getExpertsCount())
	{
	  Button4->Enabled = true;//����������
	  Button3->Enabled = true; //���������
	}
}

void TForm1::deleteControls()
{
	if(PageControls != 0)
	for(int i = 0;  i < dft.getExpertsCount(); i++)
		delete PageControls[i];
}

void __fastcall TForm1::N13Click(TObject *Sender)
{
	WinExec("hh help\\help.chm",SW_RESTORE);
}
//---------------------------------------------------------------------------

// ���������
void __fastcall TForm1::N4Click(TObject *Sender)
{
	if(fileName.IsEmpty())
	   N5->Click();
	else
	{
		//
    }
}
//---------------------------------------------------------------------------
// ���������
void __fastcall TForm1::N7Click(TObject *Sender)
{
	if(OpenDialog1->Execute())
	 {
		 // ��������� ������� ����� SaveDialog1->FileName;
		 fileName = OpenDialog1->FileName;
	 }
}
//---------------------------------------------------------------------------
//��������� ���
void __fastcall TForm1::N5Click(TObject *Sender)
{
	if(SaveDialog1->Execute())
	 {
		 // ��������� ������� ����� SaveDialog1->FileName;
		 fileName = SaveDialog1->FileName;
	 }
}
//---------------------------------------------------------------------------

