// This is generated code. DO NOT MODIFY
#include "controlslibrary.h"
#include "layoutlibrary.h"
#include "LeahConfMainForm.h"

void LeahConfMainForm::InitFromXml()
	{
	this->Name.ReadValue( _L("MainForm") );

	rootLayout = new (ELeave) Grid();
	AddControl( rootLayout );
	rootLayout->Create();
	rootLayout->Name.ReadValue( _L("rootLayout") );
	rootLayout->RowDefinitions.ReadValue( _L("auto *") );

	titlePanel = new (ELeave) StackPanel();
	rootLayout->AddControl( titlePanel );
	titlePanel->Create();
	titlePanel->Name.ReadValue( _L("titlePanel") );

	HeaderLabel = new (ELeave) Label();
	titlePanel->AddControl( HeaderLabel );
	HeaderLabel->Create();
	HeaderLabel->Name.ReadValue( _L("HeaderLabel") );
	HeaderLabel->Color.ReadValue( _L("grey") );
	HeaderLabel->TextAlignment.ReadValue( _L("left") );
	HeaderLabel->Margin.ReadValue( _L("15 10 0 0") );
	HeaderLabel->Text.ReadValue( _L("setup") );

	TitleLabel = new (ELeave) Label();
	titlePanel->AddControl( TitleLabel );
	TitleLabel->Create();
	TitleLabel->Name.ReadValue( _L("TitleLabel") );
	TitleLabel->Font.ReadValue( _L("title") );
	TitleLabel->Color.ReadValue( _L("white") );
	TitleLabel->TextAlignment.ReadValue( _L("left") );
	TitleLabel->Margin.ReadValue( _L("15 10 0 0") );
	TitleLabel->Text.ReadValue( _L("AllContacts") );

	contentPanel = new (ELeave) Grid();
	rootLayout->AddControl( contentPanel );
	contentPanel->Create();
	contentPanel->Name.ReadValue( _L("contentPanel") );
	contentPanel->SetValue( &Grid::Row, _L("1") );
	contentPanel->RowDefinitions.ReadValue( _L("* Auto Auto") );

	Setup = new (ELeave) TextBox();
	contentPanel->AddControl( Setup );
	Setup->Create();
	Setup->Name.ReadValue( _L("Setup") );
	Setup->Color.ReadValue( _L("white") );
	Setup->SetValue( &Grid::Row, _L("0") );
	Setup->Align.ReadValue( _L("lefttop") );
	Setup->Margin.ReadValue( _L("15 10 15 10") );
	Setup->Text.ReadValue( _L("Setup steps:\n\n1. Login to Google\n2. Sync content options\n3. First sync\n4. Autosync options") );

	softkeysGrid = new (ELeave) Grid();
	contentPanel->AddControl( softkeysGrid );
	softkeysGrid->Create();
	softkeysGrid->Name.ReadValue( _L("softkeysGrid") );
	softkeysGrid->ColumnDefinitions.ReadValue( _L("* * *") );
	softkeysGrid->RowDefinitions.ReadValue( _L("auto") );
	softkeysGrid->SetValue( &Grid::Row, _L("1") );

	ButtonBack = new (ELeave) Button();
	softkeysGrid->AddControl( ButtonBack );
	ButtonBack->Create();
	ButtonBack->Name.ReadValue( _L("ButtonBack") );
	ButtonBack->SetValue( &Grid::Column, _L("0") );
	ButtonBack->Margin.ReadValue( _L("10 10 10 10") );
	ButtonBack->HorizontalAlignment.ReadValue( _L("stretch") );
	ButtonBack->Text.ReadValue( _L("Back") );

	ButtonExit = new (ELeave) Button();
	softkeysGrid->AddControl( ButtonExit );
	ButtonExit->Create();
	ButtonExit->Name.ReadValue( _L("ButtonExit") );
	ButtonExit->SetValue( &Grid::Column, _L("2") );
	ButtonExit->Margin.ReadValue( _L("10 10 10 10") );
	ButtonExit->HorizontalAlignment.ReadValue( _L("stretch") );
	ButtonExit->Text.ReadValue( _L("Exit") );

	keyboard = new (ELeave) Keyboard();
	contentPanel->AddControl( keyboard );
	keyboard->Create();
	keyboard->Name.ReadValue( _L("keyboard") );
	keyboard->SetValue( &Grid::Row, _L("2") );

	}
