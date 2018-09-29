
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//


///Users/Connor/Desktop/test.jpg


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>     //console in/out
#include <fstream>      //file in/out

using namespace std;

char colorToChar(sf::Color, int);	//function prototype

int main(){
    
    cout << ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .\n";
    cout << "\nIMAGE 2 TEXT v1.0\n";
    cout << "Connor Yass 09/15/2016\n";
    
    string imagePath;
    cout << "Paste the image file path here -> ";
    getline(cin, imagePath);
    
    sf::Image img;
    if(!img.loadFromFile(imagePath.c_str())){
        return EXIT_FAILURE;
    } else {
        cout << "Image opened at: " << imagePath << "\n";
    }
    
    string textFilePath = imagePath;
    for(int i = 0; i < 3; i++){
        textFilePath.pop_back();      //delete the image extension
    }
    textFilePath.append("txt");       //add the txt extension
    
    ofstream outputTextFile(textFilePath, ios::trunc);	//create a text file for output if it hasent been already
    if(!outputTextFile){
        cout << "Could not create output text file :(\n";
        return EXIT_FAILURE;
    } else {
        cout << "Text file outout to: " << textFilePath << "\n";
    }
    cout << "\n. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .\n";
    
    
    
    int pixelsPerLetter;
    std::cout << "Pixels per letter: ";
    std::cin >> pixelsPerLetter;
    while(pixelsPerLetter > 100 || pixelsPerLetter < 1){
        std::cout << "\tError: must be between 1 and 100. Try again: ";
        std::cin >> pixelsPerLetter;
    }
    
    int type;
    std::cout << "\n1. Complex:\t $@&X£Æ§0ž8#1€‡/|(){}[]?li-_¢ø%*±+÷~<>!;:,^°`'.· ";
    std::cout << "\n2. Simple:\t @#%*=+-:. ";
    std::cout << "\n3. Currency:\t $¢.  ";
    std::cout << "\n - Choose a scale: ";
    std::cin >> type;
    while(type > 3 || type < 1){
        std::cout << "\tError: must be between 1 and 3. Try again: ";
        std::cin >> pixelsPerLetter;
    }
    
    
    sf::Color tempColor;
    for(int y = 0; y < img.getSize().y; y = y + pixelsPerLetter){
        for(int x = 1; x < img.getSize().x; x = x + pixelsPerLetter){
            tempColor = img.getPixel(x, y);
            outputTextFile << colorToChar(tempColor, type) << " ";
        }
        outputTextFile << "\n";
    }
    
    outputTextFile.close();
    std::cout << "\nSuccess! File output to: " << textFilePath << "\n\n";
    
    return EXIT_SUCCESS;
}


/**
 This function converts a color to a character. Based off:
 http://paulbourke.net/dataformats/asciiart/
 @Param 1:	The color
 @Return:	The character
 */
char colorToChar(sf::Color C, int type = 2){
    
    //  Luminance = (2 * Red + 5 * Green + 1 * Blue) / 8
    int tempInt = (2 * C.r + 4 * C.b + C.b) / 8;    //convert the pizel to black and white (get the intensity of the color)
    
    //list of characters in order to choose from ranging from darkest on the left to lightest on the right (comment out one or the other)
    string CHARACTERS;
    
    switch(type){
        case 1:
            CHARACTERS = "$@&X£Æ§0ž8#1€‡/|(){}[]?li-_¢ø%*±+÷~<>!;:,^°`'.· ";    //Complex version
            break;
        case 2:
            CHARACTERS = "@#%*=+-:. ";                                        //simplified version
            break;
        case 3:
            CHARACTERS = "$¢.  ";                                             //currency only
            break;
    }
    
    
    int tempIndex = int( (tempInt/255.0) * CHARACTERS.length() );
    
    return ( CHARACTERS[ tempIndex ] );
}


