//------------------------------------------------------------------------------
// This class defines a hierarchical menu structure with games, and the
// necessary functions to load and manipulate them.
//------------------------------------------------------------------------------
#ifndef CABRIO_MENU_HPP_
#define CABRIO_MENU_HPP_


#include <string>
#include <vector>
#include <sys/types.h>
using namespace std;


// Define MENU filters
#define MENU_FILTER_NONE      0      // No filter
#define MENU_FILTER_AVAILABLE 1 << 0 // Filter unavailable games
#define MENU_FILTER_MATURE    1 << 1 // Filter mature games
#define MENU_FILTER_CLONE     1 << 2 // Filter clones


// Menu class, used to store hierarchical menu structures, emulation parameters, and game parameters
class Menu
{

  // Public functions
  public:

    // Constructor and destructor
    Menu( );                                                      // Construct empty menu
    Menu( string path, string filename );                         // Construct new menu, and load it with "<path>/<filename>.xml"
    ~Menu( );                                                     // Destruct menu structure

    // Set data members
    void SetName( string name );                                  // Set name data member
    void SetParent( Menu *parent );                               // Set parent menu
    void AddChild( Menu *child );                                 // Add child menu
    void SetChild( long offset, uint filter_flags );              // Set the current child based on offset and filter flags
    void SetExecutable( string executable );                      // Set emulator executable data member
    void SetRomPath( string rom_path );                           // Set rom path data member
    void AddParameter( string parameter );                        // Add emulator parameter
    void SetDescription( string description );                    // Set game description data member
    void SetCloneof( string cloneof );                            // Set clone of data member
    void SetManufacturer( string manufacturer );                  // Set manufacturer data member
    void SetYear( string year );                                  // Set year data member
    void SetGenre( string genre );                                // Set genre data member
    void SetAvailable( bool available );                          // Set game available data member
    void SetIsGame( bool is_game );                               // Set game indication data member

    // Get data members
    string        Name( );                                        // Get name data member
    Menu         *Parent( );                                      // Get parent menu
    Menu         *GetChild( long offset, uint filter_flags );     // Get child based on offset and filter flags
    unsigned long GetNrChildren( );                               // Get number of children
    string        Executable( );                                  // Get emulator executable data member
    string        RomPath( );                                     // Get rom path data member
    string        Command( );                                     // Get emulation command to start the game
    string        Description( );                                 // Get game description data member
    string        Cloneof( );                                     // Get clone of data member
    string        Manufacturer( );                                // Get manufacturer data member
    string        Year( );                                        // Get year data member
    string        Genre( );                                       // Get genre data member
    bool          Available( uint filter_flags );                 // Get information whether current menu contains any available games or if the game is available depending on the filter flags
    bool          IsGame( );                                      // Get game indication data member
    bool          IsMature( );                                    // Get mature indication from the genre

  // Private data members and functions
  private:

    // Data members
    string         name_;                                         // Name data member
    Menu          *parent_;                                       // Parent menu
    vector<Menu*>  children_;                                     // Children menu(s)/game(s)
    unsigned long  current_child_;                                // Current menu/game

    string         executable_;                                   // Emulator executable data member
    string         rom_path_;                                     // Rom path data member
    vector<string> parameters_;                                   // Emulator parameters

    string         description_;                                  // Game description
    string         cloneof_;                                      // Game clone of
    string         manufacturer_;                                 // Game manufacturer
    string         year_;                                         // Game year of publication
    string         genre_;                                        // Game genre
    bool           available_;                                    // Game availability
    bool           is_game_;                                      // Game indication

};


#endif
