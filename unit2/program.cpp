// Author: Victor Arias
// Group 46:
// April 2016

#include <stdlib.h>
#include <iostream>
#include <locale.h> // Used to set language to spanish
#include <vector>
#include <sstream>
#include <functional> // For the menu functions array
#include <ctime>
#include <limits>

using namespace std;

// Pointer to menu functions, all must be void type
typedef void (*ptFunction)(); // Taken from http://www.newty.de/fpt/fpt.html

// Main functions
void showMenu(vector<string>);
int getSelectedOption(vector<ptFunction>);
// Menu functions
void showAuthorData();
void getAthleteData();
void raceTimes();
void averageTime();
void maxAndMinTimes();
void minToMaxTimes();
void racesOnTime();
void salir();

// Utility functions
void showEmptyRow(int quantity = 1); 
void showRow(string message = "", int indentLevel = 0, bool endLine = true);
string intToString(int);
int intLength(int);
int getAgeFromYear(int);
void clear_console();
void system_pause();

// Global athlete data
char g_athleteName[50];
int g_athleteAge;

int main() {
  int selectedMenuOption, menuSize;
  vector<string> menuOptions;
  // Array with menu functions, all must be void ;)
  vector<ptFunction> menuFunctions;
  
  // Using spanish language for tildes
  setlocale(LC_CTYPE, "Spanish");
  
  menuOptions.push_back("Datos del autor");
  menuOptions.push_back("Datos del atleta");
  menuOptions.push_back("Registro tiempos de carrera");
  menuOptions.push_back("Promedio de tiempos");
  menuOptions.push_back("Tiempo mayor y Tiempo menor");
  menuOptions.push_back("Tiempos ordenados de menor a mayor");
  menuOptions.push_back("Numero de carreras con un tiempo específico");
  menuOptions.push_back("Salir");
  
  
  menuFunctions.push_back(&showAuthorData);
  menuFunctions.push_back(&getAthleteData);
  menuFunctions.push_back(&raceTimes);
  menuFunctions.push_back(&averageTime);
  menuFunctions.push_back(&maxAndMinTimes);
  menuFunctions.push_back(&minToMaxTimes);
  menuFunctions.push_back(&racesOnTime);
  menuFunctions.push_back(&salir);
  
  menuSize = menuOptions.size();
  
  do {
    showMenu(menuOptions);
    selectedMenuOption = getSelectedOption(menuFunctions);
    
    clear_console();
    // Executes the function in the array
    menuFunctions[(selectedMenuOption - 1)]();
    
    system_pause();
  } while( selectedMenuOption != menuSize );
  
  return 0;
}

// Main functions
void showMenu(vector<string> menuOptions) {
  // Shows the passed menu
  int menuSize = menuOptions.size();
  int i;
  
  showRow("Menú de opciones:", 0);
  showEmptyRow();
  
  for(i = 0; i < menuSize; i++) {
    showRow(intToString(i+1) + ". " + menuOptions[i], 1);
  }
}

int getSelectedOption(vector<ptFunction> menuFunctions) {
  // Ask for a menu option and returns it.
  int selectedOption = -1, 
    functionsSize = menuFunctions.size();
  
  showEmptyRow();
  
  showRow("Seleccione una opción del menú:", 0, false);
  while (selectedOption < 1 || selectedOption > functionsSize) {
    if( selectedOption != -1) {
      showRow("Ups, no existe la opción elegida.");
      showRow("Por favor, seleccione una opción del menú:", 0, false);
    }
    if( !(cin >> selectedOption) ) {
      cin.clear();
      cin.ignore(80, '\n');
    }
  };
  
  return selectedOption;
}

// Menu functions
void showAuthorData() {
  showRow("Datos del autor:");
  showEmptyRow();
  showRow("Victor Arias", 1);
  showRow("CEAD MEdellín", 1);
  showRow("Abril 2016", 1);
}

void getAthleteData() {
  // Get the athlete basic info, then shows it
  int year;
  
  showRow("Datos del atleta:");
  showEmptyRow();
  showRow("Escriba el nombre del atleta:", 1, false);
  
  cin.ignore( numeric_limits <streamsize> ::max(), '\n' ); // Taken from http://www.cplusplus.com/forum/general/12234/ for cross platform
  // Globally defined athleteName
  cin.getline(g_athleteName, 50);
  
  showRow("Escriba el año en que nació:", 1, false);
  
  do {
    if( !(cin >> year) ) {
      cin.clear();
      cin.ignore(80, '\n');
    }
    // Globally defined athleteAge
    g_athleteAge = getAgeFromYear(year);
  } while ( g_athleteAge == -1 );
  
  clear_console();
  
  // Show Athlete Data
  showRow("Datos del atleta:");
  showRow("Nombre: ", 1, false);
  showRow(g_athleteName);
  showRow("Edad: " + intToString(g_athleteAge), 1);
}

void raceTimes() {
  // Actual record 26:17.53
  showRow("Registro de tiempos de carreras");
  showEmptyRow();
  showRow("");
  
}
void averageTime() {
  showRow("Mostrará el tiempo promedio de las carreras");
}
void maxAndMinTimes() {
  showRow("Mostrará el tiempo mínimo y el tiempo máximo de las carreras");
}
void minToMaxTimes() {
  showRow("Mostrará los tiempos de carreras ordenados de menor a mayor");
}
void racesOnTime() {
  showRow("Mostrará las carreras que cumplen un tiempo determinado");
}

void salir() {
  // Shows a good bye message
  showRow("Hasta luego ", 0, false);
  // If the athlete name is set, show it ;)
  if( g_athleteName[0] != '\0' ) {
    showRow(g_athleteName);
  }
}

// Utility functions

void showRow(string message, int indentLevel, bool endLine) {
  // Outputs a message to console with an specified indent.
  string output;
  for( int i = 0; i < indentLevel; i++) {
    output += "  ";
  }
  output += message;
  if(endLine) {
    cout << output << endl;
  } else {
    cout << output;
  }
}

void showEmptyRow(int quantity) {
  // Outputs an empty line to console.
  for(int i = 0; i < quantity; i++) {
    cout << endl; 
  }
}

string intToString(int number) {
  // Convert an integer to a string
  stringstream ss;
  string output;
  ss << number;
  ss >> output;
  return output;
}

int intLength(int number) {
  //Returns an integer length
  int counter=0;
  while(number) {        
    number = number/10;
    counter++;
  }
  return counter;
}

int getAgeFromYear(int year) {
  // Returns age based on birth year
  const int MIN_AGE = 10;
  const int MAX_AGE = 80;
  if( intLength(year) != 4 ) return -1;
  time_t timestamp;
  char currentYear [10];
  struct tm * timeinfo;
  int difference;
  
  time(&timestamp); 
  timeinfo = localtime(&timestamp);
  strftime(currentYear, 10, "%Y", timeinfo);
  difference = atoi(currentYear) - year;
  
  if( difference < MIN_AGE || difference > MAX_AGE ) return -1;
  return difference;
}

void clear_console() {
  // Cross platform cleaning screen
  #ifdef _WIN32
    system("cls");
  #else
    // Assume POSIX
    system ("clear");
  #endif
}

void system_pause() {
  // Cross platform system pause
  #ifdef _WIN32
    system("pause");
  #else
    // Assume POSIX
    cout << endl << "Presione Enter para continuar...";
    cin.ignore().get(); //Pause Command for Linux Terminal
  #endif
  clear_console();
}