#pragma once
#include <iostream>

template<typename T>
struct CipherDisk {
	const T* cipher_keys;
	int start_pointer = 0;
	const int end_pointer;
};

// O for outside
// I for Inside
template<typename O, typename I>
struct Cipher {
public:
	Cipher(int arraySize, O* outsideRing, I* insideRing) :
		cipher_outside({ outsideRing, 0, arraySize - 1 }),
		cipher_inside({ insideRing, 0, arraySize - 1 })
		// elements are initialized with initializer lists
	{ };

	void EncryptCipher(I encryptionKey);
	void PassMessage(const O* message);

public:
	CipherDisk<O> cipher_outside;
	CipherDisk<I> cipher_inside;

private:
	int* messageSequence;
};

template<typename O, typename I>
inline void Cipher<O, I>::EncryptCipher(I encryptionKey) {
	// what does O correspond to ? 
	// look at  
	size_t length = cipher_inside.end_pointer;
	for (size_t i = 0; i < length; i++) {
		if (encryptionKey == cipher_inside.cipher_keys[i]) {
			cipher_inside.start_pointer = i;
			std::cout << "The inside ciper starting key index is " << i << ", which corresponds to " << cipher_inside.cipher_keys[i] << std::endl;
		}
	}
}

template<typename O, typename I>
inline void Cipher<O, I>::PassMessage(const O* message) {
	size_t length = cipher_outside.end_pointer;
	size_t messageLength = sizeof(message) / sizeof(message[0]);
	
	messageSequence = new int[messageLength];

	for (size_t i = 0, j = 0; i < length;) {
		if (cipher_outside.cipher_keys[i] == message[j]) {
			// found matching element. Store the index, increment and restart
			messageSequence[j] = i;
			i = 0;
			j++;
		}
		else {
			i++;
		}
	}

	std::cout << "The encrypted message is : ";
	for (size_t i = 0; i < messageLength; i++)
	{
		std::cout << cipher_inside.cipher_keys[cipher_inside.start_pointer + messageSequence[i]];
	}
	std::cout << '\n';
}