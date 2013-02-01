// This is generated code. DO NOT MODIFY
#include "controlslibrary.h"
#include "layoutlibrary.h"
#include "LeahConfIntroForm.h"

void LeahConfIntroForm::InitFromXml()
	{
	this->Name.ReadValue( _L("IntroForm") );

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
	HeaderLabel->Text.ReadValue( _L("welcome to") );

	TitleLabel = new (ELeave) Label();
	titlePanel->AddControl( TitleLabel );
	TitleLabel->Create();
	TitleLabel->Name.ReadValue( _L("TitleLabel") );
	TitleLabel->Font.ReadValue( _L("title") );
	TitleLabel->Color.ReadValue( _L("white") );
	TitleLabel->TextAlignment.ReadValue( _L("left") );
	TitleLabel->Margin.ReadValue( _L("15 10 0 0") );
	TitleLabel->Text.ReadValue( _L("AllContacts - Sprint 5") );

	contentPanel = new (ELeave) Grid();
	rootLayout->AddControl( contentPanel );
	contentPanel->Create();
	contentPanel->Name.ReadValue( _L("contentPanel") );
	contentPanel->SetValue( &Grid::Row, _L("1") );
	contentPanel->RowDefinitions.ReadValue( _L("* Auto Auto Auto Auto") );

	WelcomeText = new (ELeave) TextBox();
	contentPanel->AddControl( WelcomeText );
	WelcomeText->Create();
	WelcomeText->Name.ReadValue( _L("WelcomeText") );
	WelcomeText->SetValue( &Grid::Row, _L("0") );
	WelcomeText->VerticalAlignment.ReadValue( _L("mid") );
	WelcomeText->Color.ReadValue( _L("white") );
	WelcomeText->Align.ReadValue( _L("lefttop") );
	WelcomeText->Margin.ReadValue( _L("15 10 15 10") );
	WelcomeText->Text.ReadValue( _L("The days when you had to worry about not losing your contacts are over.\nSync your contacts with Google and keep them automatically synced.") );

	grid1 = new (ELeave) Grid();
	contentPanel->AddControl( grid1 );
	grid1->Create();
	grid1->Name.ReadValue( _L("grid1") );
	grid1->ColumnDefinitions.ReadValue( _L("Auto * 2* 75") );
	grid1->RowDefinitions.ReadValue( _L("Auto") );
	grid1->SetValue( &Grid::Row, _L("1") );

	label5 = new (ELeave) Label();
	grid1->AddControl( label5 );
	label5->Create();
	label5->Name.ReadValue( _L("label5") );
	label5->Color.ReadValue( _L("white") );
	label5->Text.ReadValue( _L("auto") );
	label5->BackgroundColor.ReadValue( _L("darkgrey") );

	label6 = new (ELeave) Label();
	grid1->AddControl( label6 );
	label6->Create();
	label6->Name.ReadValue( _L("label6") );
	label6->Color.ReadValue( _L("orange") );
	label6->Text.ReadValue( _L("w1") );
	label6->SetValue( &Grid::Column, _L("1") );
	label6->BackgroundColor.ReadValue( _L("darkred") );
	label6->HorizontalAlignment.ReadValue( _L("mid") );

	label7 = new (ELeave) Label();
	grid1->AddControl( label7 );
	label7->Create();
	label7->Name.ReadValue( _L("label7") );
	label7->Color.ReadValue( _L("orange") );
	label7->Text.ReadValue( _L("w2 stretch") );
	label7->SetValue( &Grid::Column, _L("2") );
	label7->BackgroundColor.ReadValue( _L("darkgreen") );
	label7->HorizontalAlignment.ReadValue( _L("stretch") );

	label8 = new (ELeave) Label();
	grid1->AddControl( label8 );
	label8->Create();
	label8->Name.ReadValue( _L("label8") );
	label8->Color.ReadValue( _L("orange") );
	label8->Text.ReadValue( _L("fixed") );
	label8->SetValue( &Grid::Column, _L("3") );
	label8->BackgroundColor.ReadValue( _L("darkblue") );

	NeverShowCheckBox = new (ELeave) CheckBox();
	contentPanel->AddControl( NeverShowCheckBox );
	NeverShowCheckBox->Create();
	NeverShowCheckBox->Name.ReadValue( _L("NeverShowCheckBox") );
	NeverShowCheckBox->SetValue( &Grid::Row, _L("2") );
	NeverShowCheckBox->Color.ReadValue( _L("white") );
	NeverShowCheckBox->Margin.ReadValue( _L("15 10 0 10") );
	NeverShowCheckBox->Text.ReadValue( _L("Never show this again") );

	panel2 = new (ELeave) StackPanel();
	contentPanel->AddControl( panel2 );
	panel2->Create();
	panel2->Name.ReadValue( _L("panel2") );
	panel2->Orientation.ReadValue( _L("horizontal") );
	panel2->SetValue( &Grid::Row, _L("3") );

	label2 = new (ELeave) Label();
	panel2->AddControl( label2 );
	label2->Create();
	label2->Name.ReadValue( _L("label2") );
	label2->Color.ReadValue( _L("white") );
	label2->Text.ReadValue( _L("Inner ") );

	label3 = new (ELeave) Label();
	panel2->AddControl( label3 );
	label3->Create();
	label3->Name.ReadValue( _L("label3") );
	label3->Color.ReadValue( _L("white") );
	label3->Text.ReadValue( _L("layouts ") );

	label4 = new (ELeave) Label();
	panel2->AddControl( label4 );
	label4->Create();
	label4->Name.ReadValue( _L("label4") );
	label4->Color.ReadValue( _L("white") );
	label4->Text.ReadValue( _L("are working.") );

	softkeysGrid = new (ELeave) Grid();
	contentPanel->AddControl( softkeysGrid );
	softkeysGrid->Create();
	softkeysGrid->Name.ReadValue( _L("softkeysGrid") );
	softkeysGrid->ColumnDefinitions.ReadValue( _L("* * *") );
	softkeysGrid->RowDefinitions.ReadValue( _L("auto") );
	softkeysGrid->SetValue( &Grid::Row, _L("4") );

	ButtonNext = new (ELeave) Button();
	softkeysGrid->AddControl( ButtonNext );
	ButtonNext->Create();
	ButtonNext->Name.ReadValue( _L("ButtonNext") );
	ButtonNext->SetValue( &Grid::Column, _L("2") );
	ButtonNext->Margin.ReadValue( _L("10 10 10 10") );
	ButtonNext->HorizontalAlignment.ReadValue( _L("stretch") );
	ButtonNext->Text.ReadValue( _L("Next") );

	}
