/*
 * Fun with Hamming Code
 * By James Pryor
 * Calculates the Hamming Code (8,4) for a single user inputted character. Causes a random single
 * bit error, then corrects.
 */

#include <bitset>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool CalcParity(bitset<6> ParitySet, bool Even);

int main() {

    /*
     * Some Setup
     */
    char UserChar;      // User will input any character.
    int UserInt;        // Character's ascii int value.
    bitset<8> UserBits; // Same charcter in binary.
    char UserParity;    // User's selcted parity (odd or even).
    char again;         // Continue to run program.

    bool Parity;        // Parity as boolean.
    string DisParity;   // For displaying parity chosen.
    
    // Quick explination.
    cout << endl << "Displays ascii values and calculates the 8,4 Hamming code for an inputted ";
    cout << "character. Then randomly flips a bit, displays the error and correction." << endl;

    do {
        /*
         * User Input
         */
        cout << endl << "  Enter a character: ";
        cin >> UserChar;
        cout << "  Choose parity (e for even, o for odd): ";
        cin >> UserParity;
        cout << endl;

        // Convert chosen parity to useful mode.
        if(UserParity == 'e') {
            Parity = true;
            DisParity = "even";
        } else {
            Parity = false;
            DisParity = "odd";
        }

        // Get input in int.
        UserInt = UserChar;
        UserBits = UserChar;
        
        /*
         * Display ascii values from the user's input.
         */
        cout << "  ASCII Values for Input:" << endl;
        cout << "    char" << "    binary" << "    hex" << "    decimal" << endl;
        cout << "       " << UserChar << "  " << UserBits;
        cout << setw(7) << hex << UserInt;
        cout << setw(11) << dec << UserInt << endl << endl;

        
        /*
         * Calculate and Display Hamming Code
         * This site is useful: http://en.wikipedia.org/wiki/Hamming_code
         */
        // P1 covers bits 0, 1, 3, 4, 6
        bitset<6> P1; // unset bits stay 0 and don't matter for parity calcs
        P1.set(0, UserBits[7]);
        P1.set(1, UserBits[6]);
        P1.set(2, UserBits[4]);
        P1.set(3, UserBits[3]);
        P1.set(4, UserBits[1]);

        // P2 covers bits 0, 2, 3, 5, 6
        bitset<6> P2;
        P2.set(0, UserBits[7]);
        P2.set(1, UserBits[5]);
        P2.set(2, UserBits[4]);
        P2.set(3, UserBits[2]);
        P2.set(4, UserBits[1]);

        // P3 covers bits 1, 2, 3, 7
        bitset<6> P3;
        P3.set(0, UserBits[6]);
        P3.set(1, UserBits[5]);
        P3.set(2, UserBits[4]);
        P3.set(3, UserBits[0]);

        // P4 covers some bits too
        bitset<6> P4;
        P4.set(0, UserBits[3]);
        P4.set(1, UserBits[2]);
        P4.set(2, UserBits[1]);
        P4.set(3, UserBits[0]);

        // Hamming code in reverse order from UserBits.
        bitset<12> HammingCode;
        HammingCode.set(0, CalcParity(P1, Parity));
        HammingCode.set(1, CalcParity(P2, Parity));
        HammingCode.set(2, UserBits[7]);
        HammingCode.set(3, CalcParity(P3, Parity));
        HammingCode.set(4, UserBits[6]);
        HammingCode.set(5, UserBits[5]);
        HammingCode.set(6, UserBits[4]);
        HammingCode.set(7, CalcParity(P4, Parity));
        HammingCode.set(8, UserBits[3]);
        HammingCode.set(9, UserBits[2]);
        HammingCode.set(10, UserBits[1]);
        HammingCode.set(11, UserBits[0]);


        // Display Hamming Code of char.
        cout << "  Calculated Hamming Code: " << endl;
        cout << "     +--+-----+-----------+----------------parity bits (" << DisParity << ")";
        cout  << endl << "     |  |     |           |" << endl << "    ";
        for(int i = 0; i < 12; i++) {
            cout << " " << HammingCode[i] << " ";
        }
        cout << endl << "           |     |  |  |     |  |  |  |" << endl;
        cout << "           +-----+--+--+-----+--+--+--+----data bits" << endl << endl;

        /*
         * Making and Displaying Errors!
         */
        cout << "  Force random single-bit error:" << endl;
        // flip random bit.
        srand(time(NULL));
        int bittoflip = rand() % 12;
        HammingCode.flip(bittoflip);
        string getLocation[12] = {"P1", "P2", "D3", "P4", "D5", "D6", "D7", "P8", "D9", "DA", "DB", "DC"};
        cout << "    Location " << getLocation[bittoflip] << " bit flipped." << endl;
        cout << "    ";
        for(int i = 0; i < 12; i++) {
            cout << " " << HammingCode[i] << " ";
        }
        cout << endl << "    P1 P2 D3 P4 D5 D6 D7 P8 D9 DA DB DC <---- bit lcoations" << endl;
        cout << endl;
        
        /*
         * Not really necissary, but this section displays what the orginal data changed to because
         * of the error.
         */
        bitset<8> HammingError;
        HammingError.set(0, HammingCode[11]);
        HammingError.set(1, HammingCode[10]);
        HammingError.set(2, HammingCode[9]);
        HammingError.set(3, HammingCode[8]);
        HammingError.set(4, HammingCode[6]);
        HammingError.set(5, HammingCode[5]);
        HammingError.set(6, HammingCode[4]);
        HammingError.set(7, HammingCode[2]);

        int ErrorInt = HammingError.to_ulong();
        char ErrorChar = ErrorInt;

        cout << "  ASCII Values with Error:" << endl;
        if(bittoflip == 0 || bittoflip == 1 || bittoflip == 3 || bittoflip == 7) {
            cout << "    The ascii value will be unchanged because error was in parity bit.";
        } else {
            cout << "    char" << "    binary" << "    hex" << "    decimal" << endl;
            cout << "       " << ErrorChar << "  " << HammingError;
            cout << setw(7) << hex << ErrorInt;
            cout << setw(11) << dec << ErrorInt;
        }
        cout << endl << endl;
        /*
         * Error Fixing, and displaying... again.
         */
        // Fix error
        // find parity sets for fixing
        // P1 covers calc hamming code locations 0, 2, 4, 6, 8, 10
        P1.set(0, HammingCode[10]);  //finally figured out order doens't matter
        P1.set(1, HammingCode[8]);
        P1.set(2, HammingCode[6]);
        P1.set(3, HammingCode[4]);
        P1.set(4, HammingCode[2]);
        P1.set(5, HammingCode[0]);

        // P2 covers bits 1, 2, 5, 7, 9, 10
        P2.set(0, HammingCode[10]);
        P2.set(1, HammingCode[9]);
        P2.set(2, HammingCode[6]);
        P2.set(3, HammingCode[5]);
        P2.set(4, HammingCode[2]);
        P2.set(5, HammingCode[1]);

        // P3 covers bits 3, 4, 5, 6, 11
        P3.set(0, HammingCode[11]);
        P3.set(1, HammingCode[6]);
        P3.set(2, HammingCode[5]);
        P3.set(3, HammingCode[4]);
        P3.set(4, HammingCode[3]);
        P3.set(5, 0); // since reusing parity set variables, be sure to set unused to 0.

        // P4 covers 7, 8, 9, 10, 11
        P4.set(0, HammingCode[11]);
        P4.set(1, HammingCode[10]);
        P4.set(2, HammingCode[9]);
        P4.set(3, HammingCode[8]);
        P4.set(4, HammingCode[7]);
        P4.set(5, 0);

        cout << "  Parity Checking:" << endl;
        cout << "    first  parity set " << P1;
        int Pcount = 0;
        if(!CalcParity(P1, Parity)) {
            cout << " <--good";
        } else {
            cout << " <--error";
            Pcount += 1;
        }
        cout << endl << "    second parity set " << P2;
        if(!CalcParity(P2, Parity)) {
            cout << " <--good";
        } else {
            cout << " <--error";
            Pcount += 2;
        }
        cout << endl << "    third  parity set " << P3;
        if(!CalcParity(P3, Parity)) {
            cout << " <--good";
        } else {
            cout << " <--error";
            Pcount += 4;
        }
        cout << endl << "    fourth parity set " << P4;
        if(!CalcParity(P4, Parity)) {
            cout << " <--good";
        } else {
            cout << " <--error";
            Pcount += 8;
        }

        cout << endl << endl << "    Error found at location " << getLocation[Pcount-1] << "." << endl;



        cout << endl << "Run again (y/n)? ";
        cin >> again;

    } while(again != 'n');

    cout << endl;

    return 0;
}

// Count those ones.
bool CalcParity(bitset<6> ParitySet, bool Even) {
    int Count = 0;
    for(int i = 0; i < 6; i++) {
        if(ParitySet[i] == 1) {
            Count++;
        }
    }
    if(Even) {
        if(Count % 2) {
            return true;
        } else {
            return false;
        }
    } else {
        if(Count % 2) {
            return false;
        } else {
            return true;
        }
    }
}
