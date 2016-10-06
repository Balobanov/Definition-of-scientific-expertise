#ifndef CREATETABLES_H
#define CREATETABLES_H

#include "DataForTabels.h"
#include <time.h>
#include <vector>
#include <algorithm>

using std::max;
using std::vector;

//����� ������� ������� � ��������� �� � PageControl
class CreateAndComputeTables
{
public:
	friend class DataForTabels;

	CreateAndComputeTables()
	{
	 pages = 0;
	 strTables = 0;

	 // ��� ������� ���������
	CriteriaTab = 0;
	pageCriteria = 0;

	 dft = 0;
	 pCtrl = 0;

	 outRezult = 0;
	 pageResult = 0;

	}

	~CreateAndComputeTables()
	 {
			if(strTables != 0)
			for(int i = 0; i < dft->getTableCount(); i++)
				delete strTables[i];

			if(pages != 0)
			for(int i = 0; i < dft->getTableCount(); i++)
				delete pages[i];

			if(CriteriaTab != 0)
			delete CriteriaTab;

			if(pageCriteria != 0)
			delete pageCriteria;

			if(outRezult != 0)
			delete outRezult;

			if(pageResult != 0)
			delete pageResult;
	 }


// ������� ������� � �������
void __fastcall tableKeyPress(TObject *Sender, System::WideChar &Key)
	 {
		   if ((Key>='0')&&(Key<='9')) {;} // �����
		   else if (Key==8) {} // <-
		   else
			if ((Key=='/'))
			{
				Key = '/';
			}
			else Key = 0; // �� �����
	 }

// ������� ������� � Edit
void __fastcall EditKeyPress(TObject *Sender, System::WideChar &Key)
	 {
		   if ((Key>='0')&&(Key<='9')) {;} // �����
		   else if (Key==8) {} // <-
		   else
			if ((Key=='/'))
			{
				Key = '/';
			}
			else Key = 0; // �� �����
	 }

// ������� �������
bool createTables(DataForTabels *dft, TPageControl *pctrl)
{
			this->dft = dft;
			pCtrl = pctrl;
			strTables = new TStringGrid * [dft->getTableCount()];
			pages = new TTabSheet * [dft->getTableCount()];

//---------------------    ��������� �����������     ---------------------------

			// ��������� ������� ��� ��������� ����������� �� ��������
			for(int i = 0; i < (dft->getTableCount()); i++)
			{
				pages[i] = new TTabSheet(pCtrl);
				pages[i]->Caption = "��������� �� �������� \"" + dft->getCriteriaName(i) + "\"";
				pages[i]->PageControl = pCtrl;

				strTables[i] = new TStringGrid(pages[i]);
				strTables[i]->Left = 1;
				strTables[i]->Top = 1;
				strTables[i]->Width = pCtrl->Width-10;
				strTables[i]->Height = 145;
				strTables[i]->TabOrder = pCtrl->TabOrder  + i;
				strTables[i]->Visible = true;
				strTables[i]->ColCount = dft->getAlternativesCount() + 1; // ������� �������� n �� n
				strTables[i]->RowCount = dft->getAlternativesCount() + 1; // �����������
				strTables[i]->Options << goEditing;
				strTables[i]->OnKeyPress = tableKeyPress;
				strTables[i]->Parent = pages[i];
			}

			// ������� ������������ ����� ��� ������ "��������� �� ��������"
			// �������� �����������
			for(int i = 0; i < dft->getTableCount(); i++){
				for (int j = 1; j <= dft->getAlternativesCount(); j++)
				{
					 strTables[i]->Cells[j][0] = dft->getAlternativesName(j-1);
					 strTables[i]->Cells[0][j] = dft->getAlternativesName(j-1);
				}
			}

			// ��������� ������� ��������� ������ ��������� "1"
			for(int i = 0; i < dft->getTableCount(); i++)
				for (int j = 1; j <= dft->getAlternativesCount(); j++)
					for (int k = j; k==j; k++)
				{
					 strTables[i]->Cells[j][k] = "1";
				}


//------------------------- ��������� ��������� --------------------------------

			//��������� ������� ��� ��������� ��������� ����� �����
				pageCriteria = new TTabSheet(pCtrl);
				pageCriteria->Caption = "��������� ���������";
				pageCriteria->PageControl = pCtrl;

				CriteriaTab = new TStringGrid(pageCriteria);
				CriteriaTab->Left = 1;
				CriteriaTab->Top = 1;
				CriteriaTab->Width = pCtrl->Width-10;
				CriteriaTab->Height = 145;
				CriteriaTab->Visible = true;
				CriteriaTab->ColCount = dft->getCriteriaCount() + 1; // ������� �������� n �� n
				CriteriaTab->RowCount = dft->getCriteriaCount() + 1; // �����������
				CriteriaTab->Options << goEditing;
				CriteriaTab->OnKeyPress = tableKeyPress;
				CriteriaTab->Parent = pageCriteria;

	// ����������� ������������� ������
		for (int j = 1; j <= dft->getCriteriaCount(); j++)
		{
				CriteriaTab->Cells[j][0] = dft->getCriteriaName(j-1);
				CriteriaTab->Cells[0][j] = dft->getCriteriaName(j-1);
		}

	// ��������� ������� ��������� "1"
			for (int j = 1; j <= dft->getCriteriaCount(); j++)
				for (int k = j; k==j; k++)
				{
					 CriteriaTab->Cells[j][k] = "1";
				}
//------------------------------------------------------------------------------

//---------------------------- ����������� ������� -----------------------------

		 pageCtrlQuest = new TTabSheet(pCtrl);
		 pageCtrlQuest->Caption = "����������� �������";
		 pageCtrlQuest->PageControl = pCtrl;

		 TScrollBox *scrBox;
		 scrBox = new TScrollBox(pageCtrlQuest);
		 scrBox->Parent = pageCtrlQuest;
		 scrBox->Height = pageCtrlQuest->Height - 5;
		 scrBox->Width = pageCtrlQuest->Width - 5;

		 edit = new TEdit * [dft->getCriteriaCount()];
		 lblControlQ = new TLabel * [dft->getCriteriaCount()];

		  int top = 1, left = 1;
		 for(int i = 0; i < dft->getCriteriaCount(); i++)
			{

				lblControlQ[i] = new TLabel(scrBox);
				lblControlQ[i]->Alignment= taCenter;
				lblControlQ[i]->AutoSize = true;

				lblControlQ[i]->Width = 160;
				lblControlQ[i]->Height = 40;
				lblControlQ[i]->WordWrap = false;
				lblControlQ[i]->Parent = scrBox;
				lblControlQ[i]->Left = left;
				lblControlQ[i]->Top = top;

				edit[i] = new TEdit(scrBox);
				edit[i]->Width = 30;
				edit[i]->Height = 21;
				edit[i]->Top = top;
				//edit[i]->Left = lblControlQ[i]->Width + 25;
				edit[i]->Parent = scrBox;
				edit[i]->OnKeyPress = EditKeyPress;
				top += 30;
			}

		generateQ();
		pCtrl->ActivePageIndex = 0;
		return true;
}

double getFactor() {return totalFactor;}

void generateQ()
{
		srand(time(NULL));

		 int index_j, index_i;

        for(int i = 0; i < dft->getCriteriaCount(); i++)
			{

				for(;;)
				{
					index_j = rand() % dft->getAlternativesCount() + 1;
					index_i = rand() % dft->getAlternativesCount() + 1;

					if (index_j > index_i)
					{
						factorIndex.push_back(index_i);
						factorIndex.push_back(index_j);
						break;
					}
				}

				lblControlQ[i]->Caption =
					"��������� �� �������� \""
					+ dft->getCriteriaName(i) + "\". "
					+ dft->getAlternativesName(index_j-1)
					+ "-"
					+ dft->getAlternativesName(index_i-1);
					edit[i]->Left = lblControlQ[i]->Width + 25;
			}
}

void runCompute()
{
		try
		{
		computeMatrix();
		computeVectors();
		 computeWeight();
		 computeGlobalVector();

		 outResult(pCtrl);
		}
		catch(...)
		{
			throw 1;
        }

}

bool computeMatrix()
{
	try
	{
		computeMatrixForAlternatives();
		computeMatrixForCriteria();
		computeFactor();
	}
	catch(...)
	{
		throw 1;
	}
	return true;
}

bool computeFactor()
{
	String temp_str;
	double Aji, Aij, Vk = 0;
	int k = 0;

		for(int i = 0; i < dft->getCriteriaCount(); i++)
			{
				try
				{
					temp_str = (String)edit[i]->Text;

					if(temp_str.Pos('/') != 0)
					{
						Aji = StrToFloat(valueInCell( temp_str.SubString(temp_str.Pos('/')+1, temp_str.Length())));
						//temp = temp.SubString(temp.Pos('/')+1, temp.Length());
						//strTables[tab]->Cells[i][j] = temp;
					}
					else
					{
						Aji = StrToFloat(valueInCell(temp_str));
					}

					Aij = StrToFloat(strTables[i]->Cells[factorIndex[k+1]][factorIndex[k]]);

				 if((Aji > 1.0f && Aij > 1.0f) || (Aji < 1.0f && Aij< 1.0f))
				   {
					  factorCoefficient.push_back(0.0f);
				   }
				   else
				   {
					   Vk += 1.0f - ( fabs(Aij - (1.0f / Aji)) / max(Aij, 1.0f / Aji));
				   }

					k+2;
				}
				catch(...)
				{
				String msg;
				msg = "��������! ������ � ����������� �������� ";
				MessageDlg(msg, mtInformation, TMsgDlgButtons() << mbOK, 0);
				pCtrl->ActivePageIndex = pCtrl->PageCount - 1;
				throw 1;
				}
			}

			totalFactor = (Vk / dft->getCriteriaCount()) * 100.0f;

	return true;
}

// ������ �������� ������� �������� ��� ������� ����������
bool computeMatrixForAlternatives()
{
String temp;
for(int tab = 0; tab <  dft->getTableCount(); tab++)
	for(int i = 1; i <= dft->getAlternativesCount(); i++)
		for(int j = i; j <= dft->getAlternativesCount(); j++)
			{
				try
				{
					temp = strTables[tab]->Cells[j][i];

					if(temp.Pos('/') != 0)
					{
						strTables[tab]->Cells[j][i] = valueInCell( temp.SubString(temp.Pos('/')+1, temp.Length()) );
						temp = temp.SubString(temp.Pos('/')+1, temp.Length());
						strTables[tab]->Cells[i][j] = temp;
					}
					else
					{
					strTables[tab]->Cells[i][j] = valueInCell(temp);
					}
				}
				catch(...)
				{
				String msg;
				msg = "��������! ������ � ������� " + dft->getCriteriaName(tab);
				MessageDlg(msg,mtInformation, TMsgDlgButtons() << mbOK, 0);
				pCtrl->ActivePageIndex = tab;
				throw 1;
				}
			}
	return true;
}


// ������ �������� ������� ��� ������� ��������
bool computeMatrixForCriteria()
{
String temp;
	for(int i = 1; i <= dft->getCriteriaCount(); i++)
		for(int j = i; j <= dft->getCriteriaCount(); j++)
			{
				try
				{
					temp = CriteriaTab->Cells[j][i];

					if(temp.Pos('/') != 0)
					{
						CriteriaTab->Cells[j][i] = valueInCell( temp.SubString(temp.Pos('/')+1, temp.Length()) );
						temp = temp.SubString(temp.Pos('/')+1, temp.Length());
						CriteriaTab->Cells[i][j] = temp;
					}
					else
					{
					CriteriaTab->Cells[i][j] = valueInCell(temp);
					}
				}
				catch(...)
				{
				String msg;
				msg = "��������! ������ � ������� ��������� ���������";
				MessageDlg(msg,mtInformation, TMsgDlgButtons() << mbOK, 0);
				pCtrl->ActivePageIndex = pCtrl->PageCount - 2;
				throw 1;
				}
			}
	return true;
}


// ��������� �������� � ������
String valueInCell(String str)
	{return FloatToStr(1.0 / StrToFloat(str));}


void computeVectors()
{
//------------------------------------------------------------------------------
	// ������� ��� ������� �����������
	double res = 0, temp = 1;

	for(int tab = 0; tab < dft->getTableCount(); tab++)
		for(int i = 1; i <= dft->getAlternativesCount(); i++)
		{
			 for(int j = 1; j <= dft->getAlternativesCount(); j++)
				{
				   temp *= StrToFloat(strTables[tab]->Cells[j][i]);
				}
					res = pow(temp, 1.0 / (double)dft->getAlternativesCount());
					VectorsAlternatives.push_back(res);
					temp = 1;
		}

	// ����� ��� ������� ��������
		for(int i = 1; i <= dft->getCriteriaCount(); i++)
		{
			 for(int j = 1; j <= dft->getCriteriaCount(); j++)
				{
				   temp *= StrToFloat(CriteriaTab->Cells[j][i]);
				}
					res = pow(temp, 1.0 / (double)dft->getCriteriaCount());
					VectorCriterias.push_back(res);
					temp = 1;
		}
}


void computeWeight()
{
//-------------------     ��� ��� ������       ------------------------------

		// ������������
		double summa, temp;
		int k = 0; // ��� ���������� ����� ������ ������� (������ �������)
		int t = 0; // ��� ���������� ������� ������� ��� �������

		//��� ��� ������ �����������
		for(int i = 0; i < VectorsAlternatives.size(); i+=dft->getAlternativesCount())
		{
			for(int j = 0; j < dft->getAlternativesCount(); j++)
			{
				 summa += VectorsAlternatives[k];
				 k++;
			}

			for(int l = 0; l < dft->getAlternativesCount(); l++)
			{
				temp = VectorsAlternatives[t] / summa;
				WeightAlternatives.push_back(temp);
				t++;
			}
			summa=0;
		}

		k = 0;
		t = 0;
		summa = 0;
		//��� ��� ������ ��������
		for(int i = 0; i < VectorCriterias.size(); i+=dft->getCriteriaCount())
		{
			for(int j = 0; j < dft->getCriteriaCount(); j++)
			{
				 summa += VectorCriterias[k];
				 k++;
			}

			for(int l = 0; l < dft->getCriteriaCount(); l++)
			{
				temp = VectorCriterias[t] / summa;
				WeightCriterias.push_back(temp);
				t++;
			}
			summa=0;
		}
//------------------------------------------------------------------------------
}


void  computeGlobalVector()
{
	double temp = 0;
	int k = 0;
	for(int i = 0; i < dft->getAlternativesCount(); i++)
	{
		for(int j = 0; j < dft->getCriteriaCount(); j++)
		{
			double a;
			double b;
			a = WeightCriterias[j];
			b = WeightAlternatives[k];
			 temp +=  a * b;
			 k += dft->getAlternativesCount();
		}
		globalVectors.push_back(temp);
		temp = 0;
		k = i+1;
	}
}


void outResult(TPageControl *pCtrl)
{

	pageResult = new TTabSheet(pCtrl);
	pageResult->Caption = "���������";
	pageResult->PageControl = pCtrl;

	outRezult = new TMemo(pCtrl);
	outRezult->Width = pCtrl->Width - 10;
	outRezult->Height  = 145;
	outRezult->ScrollBars = ssVertical;
	outRezult->Parent = pageResult;

	double max = globalVectors[0], value;
	short index = 0;

	TVarRec args[1];
	String format;

	outRezult->Lines->Add("\n������������:\n");
	for(int i = 0; i < dft->getAlternativesCount(); i++)
	{
		value = globalVectors[i] * 100.0f;
		args[0] = value;

		format = format.Format("%.2f", &args[0], 0);

		if(globalVectors[i] > max)
		{
			max = globalVectors[i];
			index = i;
		}

		outRezult->Lines->Add(dft->getAlternativesName(i) + " = " + format + "%");
		//
	}

	outRezult->Lines->Add("\n");
	outRezult->Lines->Add("������ ������������");

	args[0] = max * 100.0f;
	format = format.Format("%.2f", &args[0], 0);

	outRezult->Lines->Add(dft->getAlternativesName(index) + " = " + format + "%\n");

	outRezult->Lines->Add("\n");
	outRezult->Lines->Add("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	outRezult->Lines->Add("����������� ������� � ��������");
	args[0] = totalFactor;
	format = format.Format("%.2f", &args[0], 0);
	outRezult->Lines->Add(format + "%");
	outRezult->Lines->Add("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

	pCtrl->ActivePageIndex = pCtrl->PageCount - 1;

	//Form1->Label4->Color = clGreen;
}


void SaveToFile(TSaveDialog *SaveDlg)
{

}


void LoadFormFile(TOpenDialog *OpnDlg)
{

}

//------------------------------------------------------------------------------
private:
	 TTabSheet **pages;
	 TStringGrid **strTables;

	 // ��� ������� ���������
	 TStringGrid *CriteriaTab;
	 TTabSheet *pageCriteria;

	 DataForTabels *dft;
	 TPageControl *pCtrl;

	vector<double> VectorsAlternatives;
	vector<double> VectorCriterias;

	vector<double> WeightAlternatives;
	vector<double> WeightCriterias;

	vector<double> globalVectors;
	vector<double> factorCoefficient;
	vector<int> factorIndex;

	double totalFactor;

	TMemo *outRezult;
	TTabSheet *pageResult;

	// ��� �������� "���������� �������"
	TLabel **lblControlQ;
	TTabSheet *pageCtrlQuest;
	TEdit **edit;
};

#endif
