#pragma once
#include <iostream>
#include <vector>
#include <string.h>

template<typename T>
struct CipherDisk {
	const T* keys;
	int start_pointer = 0;
};

// O for outside (disk)
// I for Inside (disk)
template<typename O, typename I>
struct Cipher {
public:
	Cipher(int arraySize, O* outsideRing, I* insideRing) :
		cipher_outside({ outsideRing, 0 }),
		cipher_inside({ insideRing, 0 }),
		cipher_size(arraySize - 1)
	{ };

	void SetCipherShift(const I* encryptionKey);
	void EncryptMessage(const O* message);

	void GetMessageSignature(const O* plaintextMessage);
	void EncryptMessageFromSignature(int messageLength);

public:
	CipherDisk<O> cipher_outside;
	CipherDisk<I> cipher_inside;
	const size_t cipher_size;

private:
	std::vector<int> messageSequence;
	std::vector<char> encryptedMessage;
};

template<typename O, typename I>
inline void Cipher<O, I>::SetCipherShift(const I* encryptionKey) {
	for (size_t i = 0; i < cipher_size; i++) {
		if (cipher_inside.keys[i] == *encryptionKey) {
			cipher_inside.start_pointer = i;
			// offset the "start" of the inside cipher
		}
	}
}

template<typename O, typename I>
inline void Cipher<O, I>::EncryptMessage(const O* plaintextMessage) {
	GetMessageSignature(plaintextMessage);
	EncryptMessageFromSignature(std::strlen(plaintextMessage));
}

// construct a "signature" made of character's index on the outside cipher
template<typename O, typename I>
inline void Cipher<O, I>::GetMessageSignature(const O* plaintextMessage) {
	for (size_t i = 0, j = 0; i < cipher_size;) {
		if (cipher_outside.keys[i] == plaintextMessage[j]) {
			messageSequence.push_back(i); // store the index
			j++; // increment the plaintext's evaluated char
			i = 0;
		}
		else {
			//i++; // TODO : don't think this works the way I think it does
		}
	}
}

// using the signature, encrypt the message by following the indexes and offsetting them
template<typename O, typename I>
inline void Cipher<O, I>::EncryptMessageFromSignature(int messageLength) {
	for (size_t i = 0; i < messageLength; i++) {
		encryptedMessage.push_back(cipher_inside.keys[cipher_inside.start_pointer + messageSequence[i]]);
		std::cout << encryptedMessage[i];
	}
}