#include <iostream>
#include <string>
#include "menu.hpp"
using namespace std;


void PrintMenu( Menu *menu )
{

  // Indentation based on the hierarchy
  Menu *menu_parser = menu;
  while ( menu_parser->Parent( ) )
  {
    menu_parser = menu_parser->Parent( );
    cout << "  ";
  }

  if ( menu->IsGame( ) ) // Print game command
  {
    if ( menu->Available( MENU_FILTER_NONE ) )
      cout << "Game \"" << menu->Description( ) << "\" uses emulator command \"" << menu->Command( ) << "\", and is available." << endl;
    else
      cout << "Game \"" << menu->Description( ) << "\" uses emulator command \"" << menu->Command( ) << "\", but is not available." << endl;
  }
  else // Print menu name and number of children, and print the child menus
  {
    cout << "Menu \"" << menu->Name( ) << "\" has " << menu->GetNrChildren( ) << " children." << endl;
    if ( menu->GetNrChildren( ) != 0 )
      for ( uint i = 0; i < menu->GetNrChildren( ); i++ )
        PrintMenu( menu->GetChild( i, 0 ) );
  }
  return;
}


int main( )
{

  Menu *menu = new Menu( "Menu", "menu" );
  cout << "Menu \"" << menu->Name( ) << "\" is loaded." << endl;
  PrintMenu( menu );
  return 0;

}
