//---------------------------------------------------------------------------

#ifndef DiplomMainH
#define DiplomMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TMenuItem *N15;
	TMemo *Memo1;
	TMemo *Memo2;
	TLabel *Label1;
	TLabel *Label2;
	TMenuItem *N16;
	TMenuItem *N17;
	TPageControl *PageControl1;
	TButton *Button1;
	TMenuItem *N18;
	TMenuItem *N19;
	TButton *Button2;
	TFontDialog *FontDialog1;
	TMemo *Memo3;
	TLabel *Label3;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TLabel *Label4;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	TImage *Image1;
	void __fastcall N15Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
	/*void __fastcall tableKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall tableSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);*/

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	void createContrils();
	void ShowComponents();
	void HideComponents();
	void deleteControls();

	void EnableButtons();

	void ShowSelecterPage(int i);
	void maxExpertFactorLbl();
	void New();

	int selectedExpert;
	int maxExpertFactor;

	TPageControl **PageControls;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
