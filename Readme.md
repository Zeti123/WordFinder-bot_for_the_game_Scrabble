# WordFinder - bot for the game "Scrabble"

![obraz](https://user-images.githubusercontent.com/23141452/142049604-e94bea39-ca5e-44bf-88b3-531d90dfdea6.png)

## IMPORTANT
For the program to work properly, you need to put the "Src" folder in the program files into the folder with the compiled binary file.

## description
A bot, that can always find the word worth the most points in a game of Scrabble.
Implemented using a multithreaded trie tree based algorithm. Features a GUI, multiple undo, and parsing of user-provided dictionaries. 
Currently supported languages are English and Polish.
![obraz](https://user-images.githubusercontent.com/23141452/142050998-4c9a8311-5a97-4887-a3e7-c3a18ee6d070.png)

## how to add own dictionary
To add your own language, you need to prepare the words.txt file, which will contain a list of the words that WordFinder can use,
then create a letters_info.txt file that will contain information about which letters are available in a given language and how many points are worth.

words.txt: <br>
![obraz](https://user-images.githubusercontent.com/23141452/142167222-94396ba5-9845-492e-bd7a-bea0c2f90ac4.png)

letters_info.txt: <br>
![obraz](https://user-images.githubusercontent.com/23141452/142167486-8e71b3b3-0030-4a44-a0ac-f447df5606a1.png)


then the given 2 files should be placed in the folder <folder_with_binary_file>/Src/Languages/<language_name>/
![obraz](https://user-images.githubusercontent.com/23141452/142051333-b45584b8-ae30-43f9-a3d2-e49d3be9bcf8.png)
![obraz](https://user-images.githubusercontent.com/23141452/142051353-0a573a45-83d1-4199-8c1e-9e027199ba3d.png)


Disclaimer

SCRABBLE® is a registered trademark. All intellectual property rights in and to the game are owned in the U.S.A and Canada by Hasbro Inc., and throughout the rest of the world by J.W. Spear & Sons Limited of Maidenhead, Berkshire, England, a subsidiary of Mattel Inc. Mattel and Spear are not affiliated with Hasbro. Words with Friends is a trademark of Zynga with Friends.

This project is not affiliated with SCRABBLE®, Mattel Inc, Hasbro Inc, Zynga with Friends or Zynga Inc in any way. This software is for entertainment purposes only.
