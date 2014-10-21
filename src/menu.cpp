#include <iostream>
#include <string>
#include <vector>
#include <libxml2/libxml/parser.h>
#include <unistd.h>
#include "menu.hpp"
using namespace std;


// Construct empty menu.
Menu::Menu( void )
{
  name_          = "";
  parent_        = NULL;
  current_child_ = 0;
  executable_    = "";
  rom_path_      = "";
  description_   = "";
  cloneof_       = "";
  manufacturer_  = "";
  year_          = "";
  genre_         = "";
  available_     = false;
  is_game_       = false;
}


// Function declaration.
int ReadMenu( string path, string filename, Menu *menu );


// Construct new menu, and load it with "<path>/<filename>.xml".
Menu::Menu( string path, string filename )
{

  // Initialisation.
  name_          = "";
  parent_        = NULL;
  current_child_ = 0;
  executable_    = "";
  rom_path_      = "";
  description_   = "";
  cloneof_       = "";
  manufacturer_  = "";
  year_          = "";
  genre_         = "";
  available_     = false;

  // Load menu structure.
  ReadMenu( path, filename, this );

}


//Destruct menu structure.
Menu::~Menu( void )
{
  if ( children_.size( ) != 0 )
    for ( uint i = 0; i < children_.size( ); i++ )
      delete children_[i];
}


// Set name data member.
void Menu::SetName( string name )
{
  name_ = name;
}


// Set parent menu.
void Menu::SetParent( Menu *parent )
{
  parent_ = parent;
}


// Add child menu.
void Menu::AddChild( Menu *child )
{
  children_.push_back( child );
}


// Set the current child based on offset and filter flags.
void Menu::SetChild( long offset, uint filter_flags )
{

  // Don't do anything if there are no children.
  if ( children_.size( ) == 0 )
    return;

  unsigned long current_child = current_child_; // Store current child to check if unfiltered children exist.
  int i                       = 0;              // Offset iterator.

  // Find the child.
  while ( true )
  {
    bool filtered = false;
    if ( (filter_flags & MENU_FILTER_AVAILABLE) && !children_[current_child_]->Available( filter_flags ) )  // Check if the child is available.
      filtered = true;
    if ( (filter_flags & MENU_FILTER_MATURE)    &&  children_[current_child]->IsMature( ) )                 // Check if the child is mature.
      filtered = true;
    if ( (filter_flags & MENU_FILTER_CLONE)     &&  children_[current_child]->Cloneof( ) != "" )            // Check if the child is a clone.
      filtered = true;
    if ( !filtered ) // Only increase the iterator if the child isn't filtered.
    {
      if ( i == offset ) // Found the correct child.
        break;
      if ( offset >= 0 )
        i++;
      else
        i--;
    }
    if ( offset >= 0 )
      current_child_ = (current_child_+1)%children_.size( ); // Switch to the next child.
    else
      current_child_ = (current_child_-1)%children_.size( ); // Switch to the previous child.
    if ( (current_child_ == current_child) && i == 0 )       // Check if unfiltered children exist.
      break;
  }
}


// Set emulator executable data member.
void Menu::SetExecutable( string executable )
{
  executable_ = executable;
}


// Set rom path data member.
void Menu::SetRomPath( string rom_path )
{
  rom_path_ = rom_path;
}


// Set emulator parameter.
void Menu::AddParameter( string parameter )
{
  parameters_.push_back( parameter );
}


// Set game description data member.
void Menu::SetDescription( string description )
{
  description_ = description;
}


// Set clone of data member.
void Menu::SetCloneof( string cloneof )
{
  cloneof_ = cloneof;
}


// Set manufacturer data member.
void Menu::SetManufacturer( string manufacturer )
{
  manufacturer_ = manufacturer;
}


// Set year data member.
void Menu::SetYear( string year )
{
  year_ = year;
}


// Set genre data member.
void Menu::SetGenre( string genre )
{
  genre_ = genre;
}


// Set game available data member.
void Menu::SetAvailable( bool available )
{
  available_ = available;
}


// Set game indication data member.
void Menu::SetIsGame( bool is_game )
{
  is_game_ = is_game;
}


// Get name data member.
string Menu::Name( void )
{
  return name_;
}


// Get parent menu.
Menu *Menu::Parent( void )
{
  return parent_;
}


// Get child based on offset and filter flags.
Menu *Menu::GetChild( long offset, uint filter_flags )
{

  // If no children exist, return NULL pointer.
  if ( children_.size( ) == 0 )
    return NULL;

  unsigned long current_child = current_child_; // Child iterator.
  int i                       = 0;              // Offset iterator.

  // Find the child.
  while ( true )
  {
    bool filtered = false;
    if ( (filter_flags & MENU_FILTER_AVAILABLE) && !children_[current_child]->Available( filter_flags ) ) // Check if the child is available.
      filtered = true;
    if ( (filter_flags & MENU_FILTER_MATURE)    &&  children_[current_child]->IsMature( ) )               // Check if the child is mature.
      filtered = true;
    if ( (filter_flags & MENU_FILTER_CLONE)     &&  children_[current_child]->Cloneof( ) != "" )          // Check if the child is a clone.
      filtered = true;
    if ( !filtered ) // Only increase the iterator if the child isn't filtered.
    {
      if ( i == offset ) // Found the correct child.
        return children_[current_child];
      if ( offset >= 0 )
        i++;
      else
        i--;
    }
    if ( offset >= 0 )
      current_child = (current_child+1)%children_.size( ); // Switch to the next child.
    else
      current_child = (current_child-1)%children_.size( ); // Switch to the previous child.
    if ( (current_child_ == current_child) && i == 0 )     // Check if unfiltered children exist.
      return children_[current_child];
  }
}


// Get number of children.
unsigned long Menu::GetNrChildren( void )
{
  return children_.size( );
}


// Get emulator executable data member.
string Menu::Executable( void )
{

  string executable = "";

  // Find the first executable data member in this menu or up the parent chain.
  if ( executable_ == "" && parent_ != NULL )
    return parent_->RomPath( );
  else
    return executable_;

}


// Get rom path data member.
string Menu::RomPath( void )
{

  string rom_path = "";

  // Find the first rom path data member in this menu or up the parent chain.
  if ( rom_path_ == "" && parent_ != NULL )
    return parent_->RomPath( );
  else
    return rom_path_;

}


// Get emulation command to start the game.
string Menu::Command( void )
{

  string command = "";

  // Check if executable data member is set. If so, add its parameters and the game name.
  if ( executable_ != "" )
  {
    command = executable_ + " ";
    if ( parameters_.size( ) != 0 )
      for ( uint i = 0; i < parameters_.size( ); i++ )
        command += parameters_[i] + " ";
    if ( is_game_ )
      return command + name_;
    else
      return command;
  }
  // If the executable data member is not set, check up the parent chain.
  else if ( parent_ != NULL )
    if ( is_game_ )
      return parent_->Command( ) + name_;
    else
      return parent_->Command( );
  else
    return "";

}


// Get game description data member.
string Menu::Description( void )
{
  return description_;
}


// Get clone of data member.
string Menu::Cloneof( void )
{
  return cloneof_;
}


// Get manufacturer data member.
string Menu::Manufacturer( void )
{
  return manufacturer_;
}


// Get year data member.
string Menu::Year( void )
{
  return year_;
}


// Get genre data member.
string Menu::Genre( void )
{
  return genre_;
}


// Get information whether current menu contains any available games or if the game is available depending on the filter flags.
bool Menu::Available( uint filter_flags )
{

  bool available = available_;

  // Combine information from the children.
  if ( children_.size( ) != 0 )
    for ( unsigned long i = 0; i < children_.size( ); i++ )
      available |= children_[i]->Available( filter_flags );

  // If this menu is a game, check the filters.
  if ( is_game_ )
  {
    if ( (filter_flags & MENU_FILTER_AVAILABLE) && !available_ )            // Check if the game is available.
      available = false;
    if ( (filter_flags & MENU_FILTER_MATURE)    && this->IsMature( ) )      // Check if the game is mature.
      available = false;
    if ( (filter_flags & MENU_FILTER_CLONE)     && this->Cloneof( ) != "" ) // Check if the game is a clone.
      available = false;
  }

  return available;

}


// Get game indication data member.
bool Menu::IsGame( void )
{
  return is_game_;
}


// Get mature indication from the genre.
bool Menu::IsMature( void )
{
  if ( genre_.find( "Mature", 0 ) == string::npos )
    return false;
  else
    return true;
}


// Read the emulator XML element.
int ReadEmulatorElement( xmlNode *root, Menu &menu )
{

  xmlNode *node      = root;

  menu.SetExecutable( std::string ((char*) xmlGetProp( node, (const xmlChar *)"name" )) );

  node = node->children;
  while ( node )
  {
    if ( node->type == XML_ELEMENT_NODE )
    {
      if ( std::string ((char*) node->name) == "param" )
        menu.AddParameter( std::string ((char*) xmlNodeGetContent( node )) );
      else if ( std::string ((char*) node->name) == "rom-path" )
        menu.SetRomPath( std::string ((char*) xmlNodeGetContent( node )) );
      else
      {
        cout << "Unexpected tag " << std::string ((char*) node->name) << " detected." << endl;
        return -1;
      }
    }
    node = node->next;
  }

  return 0;

}


// Read the game XML element.
int ReadGameElement( xmlNode *root, Menu &menu )
{

  xmlNode *node      = root;
  Menu    *game_menu = new Menu( );

  menu.AddChild( game_menu );
  game_menu->SetParent( &menu );

  game_menu->SetName( std::string ((char*) xmlGetProp( node, (const xmlChar *)"name" )) );

  node = node->children;
  while ( node )
  {
    if ( node->type == XML_ELEMENT_NODE )
    {
      if      ( std::string ((char*) node->name) == "description" )
        game_menu->SetDescription( std::string ((char*) xmlNodeGetContent( node )) );
      else if ( std::string ((char*) node->name) == "cloneof" )
        game_menu->SetCloneof( std::string ((char*) xmlNodeGetContent( node )) );
      else if ( std::string ((char*) node->name) == "crc" );
      else if ( std::string ((char*) node->name) == "manufacturer" )
        game_menu->SetManufacturer( std::string ((char*) xmlNodeGetContent( node )) );
      else if ( std::string ((char*) node->name) == "year" )
        game_menu->SetYear( std::string ((char*) xmlNodeGetContent( node )) );
      else if ( std::string ((char*) node->name) == "genre" )
        game_menu->SetGenre( std::string ((char*) xmlNodeGetContent( node )) );
      else if ( std::string ((char*) node->name) == "emulator" )
        ReadEmulatorElement( node, menu );
      else
      {
        cout << "Unexpected tag " << std::string ((char*) node->name) << " detected." << endl;
        return -1;
      }
    }
    node = node->next;
  }
  game_menu->SetIsGame( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Name( ) + ".7z").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Cloneof( ) + ".7z").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Description( ) + ".7z").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Name( ) + ".zip").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Description( ) + ".zip").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Name( ) + ".smc").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Description( ) + ".smc").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Name( ) + ".rom").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );
  if ( access( (game_menu->RomPath( ) + "/" + game_menu->Description( ) + ".rom").c_str( ), 0 ) == 0 )
    game_menu->SetAvailable( true );

  return 0;

}


// Read the menu-item XML element.
int ReadMenuItemElement( string path, xmlNode *root, Menu &menu )
{

  xmlNode *node     = root;
  Menu    *sub_menu = new Menu( );
  string   filename = std::string ((char*) xmlGetProp( node, (const xmlChar *)"name" ));

  menu.AddChild( sub_menu );
  sub_menu->SetParent( &menu );

  node = node->children;
  while ( node )
  {
    if ( node->type == XML_ELEMENT_NODE )
    {
      if ( std::string ((char*) node->name) == "emulator" )
        ReadEmulatorElement( node, *sub_menu );
      else
      {
        cout << "Unexpected tag " << std::string ((char*) node->name) << " detected." << endl;
        return -1;
      }
        
    }
    node = node->next;
  }

  return ReadMenu( path, filename, sub_menu );

}


// Read the menu XML element.
int ReadMenuXML( string path, xmlNode *root, Menu &menu )
{

  xmlNode *node = root;

  if ( std::string ((char*) node->name ) != "menu" )
  {
    cout << "Game file does not contain the <menu> root element." << endl;
    return -1;
  }

  node = node->children;
  while ( node )
  {
    if ( node->type == XML_ELEMENT_NODE )
    {
      if ( std::string ((char*) node->name) == "game" )
      {
        if ( ReadGameElement( node, menu ) != 0 )
          return -1;
      }
      else if ( std::string ((char*) node->name) == "menu-item" )
      {
        if ( ReadMenuItemElement( path, node, menu ) != 0 )
          return -1;
      }
    }
    node = node->next;
  }
  
  return 0;

}


// Read the menu from <path>/<filename>.xml into the menu.
int ReadMenu( string path, string filename, Menu *menu )
{

  int        retval    = -1;
  xmlNodePtr menu_root = NULL;
  xmlDocPtr  menu_doc  = xmlReadFile( (path+"/"+filename+".xml").c_str( ), NULL, 0 );

  if ( menu_doc == NULL )
    cout << "Cannot read " << path + "/" + filename << ".xml." << endl;
  else
  {
    menu_root = xmlDocGetRootElement( menu_doc );
    if ( menu_root == NULL )
      cout << "Cannot get root element of menu file " << path + "/" + filename << ".xml." << endl;
    else
    {
      menu->SetName( filename );
      retval = ReadMenuXML( path, menu_root, *menu );
    }
  }
  xmlFreeDoc( menu_doc );
  return retval;
}
