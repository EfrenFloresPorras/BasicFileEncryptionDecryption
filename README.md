# BasicFileEncryptionDecryption
The code is about an interface which does file encryption and decryption in C++, this program will specifically do simple byte change encryption, with the addition of adding ".encrypted" terminology at the end to confirm the encryption of the file.

 * @file main.cpp
 * @brief File Encryption and Decryption Application
 
 * This application provides a simple GUI interface for encrypting and decrypting files using a symmetric encryption algorithm.
 * It uses Qt framework for the GUI components and file operations.
 
 * The encryption process increments each byte in the file by 1, while the decryption process decrements each byte by 1,
 * effectively performing a simple symmetric encryption/decryption algorithm.
 
 * The user can select a file to encrypt or a previously encrypted file to decrypt using the provided GUI buttons.
 * A progress bar shows the progress of the encryption or decryption process.
 * The bytes of the file before encryption/decryption are displayed in the console.
 
 * @note This application uses a simplistic encryption algorithm for demonstration purposes only.
 * It should not be considered secure for real-world encryption needs.
 
 
