// This is generated code. DO NOT MODIFY
#include "controlslibrary.h"
#include "layoutlibrary.h"
#include "Keyboard.h"

void Keyboard::InitFromXml()
	{
	this->BackgroundColor.ReadValue( _L("darkgrey") );

	rootLayout = new (ELeave) Grid();
	AddControl( rootLayout );
	rootLayout->Create();
	rootLayout->Name.ReadValue( _L("rootLayout") );
	rootLayout->RowDefinitions.ReadValue( _L("Auto") );

	lettersPage = new (ELeave) Grid();
	rootLayout->AddControl( lettersPage );
	lettersPage->Create();
	lettersPage->Name.ReadValue( _L("lettersPage") );
	lettersPage->SetValue( &Grid::Row, _L("0") );
	lettersPage->RowDefinitions.ReadValue( _L("Auto Auto Auto Auto") );
	lettersPage->Margin.ReadValue( _L("1 1 1 1") );
	lettersPage->DoubleBuffered.ReadValue( _L("true") );

	abcRow1 = new (ELeave) Grid();
	lettersPage->AddControl( abcRow1 );
	abcRow1->Create();
	abcRow1->Name.ReadValue( _L("abcRow1") );
	abcRow1->RowDefinitions.ReadValue( _L("Auto") );
	abcRow1->ColumnDefinitions.ReadValue( _L("* * * * * * * * * *") );

	abcRow2 = new (ELeave) Grid();
	lettersPage->AddControl( abcRow2 );
	abcRow2->Create();
	abcRow2->Name.ReadValue( _L("abcRow2") );
	abcRow2->SetValue( &Grid::Row, _L("1") );
	abcRow2->RowDefinitions.ReadValue( _L("Auto") );
	abcRow2->ColumnDefinitions.ReadValue( _L("0.5* * * * * * * * * * 0.5*") );

	abcRow3 = new (ELeave) Grid();
	lettersPage->AddControl( abcRow3 );
	abcRow3->Create();
	abcRow3->Name.ReadValue( _L("abcRow3") );
	abcRow3->SetValue( &Grid::Row, _L("2") );
	abcRow3->RowDefinitions.ReadValue( _L("Auto") );
	abcRow3->ColumnDefinitions.ReadValue( _L("1.5* * * * * * * * 1.5*") );

	abcRow4 = new (ELeave) Grid();
	lettersPage->AddControl( abcRow4 );
	abcRow4->Create();
	abcRow4->Name.ReadValue( _L("abcRow4") );
	abcRow4->SetValue( &Grid::Row, _L("3") );
	abcRow4->RowDefinitions.ReadValue( _L("Auto") );
	abcRow4->ColumnDefinitions.ReadValue( _L("1.5* * 4* * 2.5*") );

	numbersPage = new (ELeave) Grid();
	rootLayout->AddControl( numbersPage );
	numbersPage->Create();
	numbersPage->Name.ReadValue( _L("numbersPage") );
	numbersPage->RowDefinitions.ReadValue( _L("Auto Auto Auto Auto") );
	numbersPage->Margin.ReadValue( _L("1 1 1 1") );
	numbersPage->Visible.ReadValue( _L("false") );
	numbersPage->DoubleBuffered.ReadValue( _L("true") );

	numericRow1 = new (ELeave) Grid();
	numbersPage->AddControl( numericRow1 );
	numericRow1->Create();
	numericRow1->Name.ReadValue( _L("numericRow1") );
	numericRow1->RowDefinitions.ReadValue( _L("Auto") );
	numericRow1->ColumnDefinitions.ReadValue( _L("* * * * * * * * * *") );

	numericRow2 = new (ELeave) Grid();
	numbersPage->AddControl( numericRow2 );
	numericRow2->Create();
	numericRow2->Name.ReadValue( _L("numericRow2") );
	numericRow2->SetValue( &Grid::Row, _L("1") );
	numericRow2->RowDefinitions.ReadValue( _L("Auto") );
	numericRow2->ColumnDefinitions.ReadValue( _L("* * * * * * * * * *") );

	numericRow3 = new (ELeave) Grid();
	numbersPage->AddControl( numericRow3 );
	numericRow3->Create();
	numericRow3->Name.ReadValue( _L("numericRow3") );
	numericRow3->SetValue( &Grid::Row, _L("2") );
	numericRow3->RowDefinitions.ReadValue( _L("Auto") );
	numericRow3->ColumnDefinitions.ReadValue( _L("1.5* 7* 1.5*") );

	numericRow3Keys = new (ELeave) Grid();
	numericRow3->AddControl( numericRow3Keys );
	numericRow3Keys->Create();
	numericRow3Keys->Name.ReadValue( _L("numericRow3Keys") );
	numericRow3Keys->SetValue( &Grid::Column, _L("1") );
	numericRow3Keys->RowDefinitions.ReadValue( _L("Auto") );
	numericRow3Keys->ColumnDefinitions.ReadValue( _L("* * * * *") );

	numericRow4 = new (ELeave) Grid();
	numbersPage->AddControl( numericRow4 );
	numericRow4->Create();
	numericRow4->Name.ReadValue( _L("numericRow4") );
	numericRow4->SetValue( &Grid::Row, _L("3") );
	numericRow4->RowDefinitions.ReadValue( _L("Auto") );
	numericRow4->ColumnDefinitions.ReadValue( _L("1.5* * 4* * 2.5*") );

	symbolsPage = new (ELeave) Grid();
	rootLayout->AddControl( symbolsPage );
	symbolsPage->Create();
	symbolsPage->Name.ReadValue( _L("symbolsPage") );
	symbolsPage->RowDefinitions.ReadValue( _L("Auto Auto Auto Auto") );
	symbolsPage->Margin.ReadValue( _L("1 1 1 1") );
	symbolsPage->Visible.ReadValue( _L("false") );
	symbolsPage->DoubleBuffered.ReadValue( _L("true") );

	symbolsRow1 = new (ELeave) Grid();
	symbolsPage->AddControl( symbolsRow1 );
	symbolsRow1->Create();
	symbolsRow1->Name.ReadValue( _L("symbolsRow1") );
	symbolsRow1->RowDefinitions.ReadValue( _L("Auto") );
	symbolsRow1->ColumnDefinitions.ReadValue( _L("* * * * * * * * * *") );

	symbolsRow2 = new (ELeave) Grid();
	symbolsPage->AddControl( symbolsRow2 );
	symbolsRow2->Create();
	symbolsRow2->Name.ReadValue( _L("symbolsRow2") );
	symbolsRow2->SetValue( &Grid::Row, _L("1") );
	symbolsRow2->RowDefinitions.ReadValue( _L("Auto") );
	symbolsRow2->ColumnDefinitions.ReadValue( _L("0.5* * * * * * * * 0.5*") );

	symbolsRow3 = new (ELeave) Grid();
	symbolsPage->AddControl( symbolsRow3 );
	symbolsRow3->Create();
	symbolsRow3->Name.ReadValue( _L("symbolsRow3") );
	symbolsRow3->SetValue( &Grid::Row, _L("2") );
	symbolsRow3->RowDefinitions.ReadValue( _L("Auto") );
	symbolsRow3->ColumnDefinitions.ReadValue( _L("1.5* 7* 1.5*") );

	symbolsRow3Keys = new (ELeave) Grid();
	symbolsRow3->AddControl( symbolsRow3Keys );
	symbolsRow3Keys->Create();
	symbolsRow3Keys->Name.ReadValue( _L("symbolsRow3Keys") );
	symbolsRow3Keys->SetValue( &Grid::Column, _L("1") );
	symbolsRow3Keys->RowDefinitions.ReadValue( _L("Auto") );
	symbolsRow3Keys->ColumnDefinitions.ReadValue( _L("* * * * *") );

	symbolsRow4 = new (ELeave) Grid();
	symbolsPage->AddControl( symbolsRow4 );
	symbolsRow4->Create();
	symbolsRow4->Name.ReadValue( _L("symbolsRow4") );
	symbolsRow4->SetValue( &Grid::Row, _L("3") );
	symbolsRow4->RowDefinitions.ReadValue( _L("Auto") );
	symbolsRow4->ColumnDefinitions.ReadValue( _L("1.5* * 4* * 2.5*") );

	popupKey = new (ELeave) Button();
	rootLayout->AddControl( popupKey );
	popupKey->Create();
	popupKey->Name.ReadValue( _L("popupKey") );
	popupKey->SetValue( &Grid::Row, _L("0") );
	popupKey->Text.ReadValue( _L("B") );
	popupKey->Margin.ReadValue( _L("1 1 1 1") );
	popupKey->HorizontalAlignment.ReadValue( _L("center") );
	popupKey->VerticalAlignment.ReadValue( _L("center") );
	popupKey->Align.ReadValue( _L("midmid") );
	popupKey->Visible.ReadValue( _L("false") );
	popupKey->MinimumSize.ReadValue( _L("72 40") );
	popupKey->BackgroundColor.ReadValue( _L("grey") );
	popupKey->Color.ReadValue( _L("black") );

	}
