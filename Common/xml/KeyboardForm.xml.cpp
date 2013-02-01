// This is generated code. DO NOT MODIFY
#include "controlslibrary.h"
#include "layoutlibrary.h"
#include "KeyboardForm.h"

void KeyboardForm::InitFromXml()
	{
	this->Name.ReadValue( _L("keyboardForm") );

	keyboardLayout = new (ELeave) Grid();
	AddControl( keyboardLayout );
	keyboardLayout->Create();
	keyboardLayout->Name.ReadValue( _L("keyboardLayout") );
	keyboardLayout->RowDefinitions.ReadValue( _L("auto") );
	keyboardLayout->ColumnDefinitions.ReadValue( _L("*") );

	keyboard = new (ELeave) Keyboard();
	keyboardLayout->AddControl( keyboard );
	keyboard->Create();
	keyboard->Name.ReadValue( _L("keyboard") );
	keyboard->SetValue( &Grid::Row, _L("0") );
	keyboard->SetValue( &Grid::Column, _L("0") );

	}
