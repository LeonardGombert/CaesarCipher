#include <iostream>
#include "Cipher.h"

int main() {
	char numbers[26] = { '1', '2', '3','4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26' };
	char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	char cipherShift[256];
	char encryptionMessage[256];
	Cipher<char, char>* internalCipher = new Cipher<char, char>(26, letters, letters);

	printf("Please determine Cipher Shift : \n\nA = ?");
	std::cin >> cipherShift;

	printf("Please enter your message : \n\n");
	std::cin >> encryptionMessage;

	internalCipher->SetCipherShift(cipherShift);
	internalCipher->EncryptMessage(encryptionMessage);
}