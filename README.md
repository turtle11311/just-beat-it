# just-beat-it

※ Environment:

1. linux
2. Qt version 5.9.4

※ Package needed:

1. git
2. Qt version 5.9.4 with Qt Charts & qmake(remember to install Qt Charts while installing Qt)
3. make
4. gcc & g++
5. python version 2.6, 2.7, or 3.2+
6. ffmpeg
7. aubio
   - sudo apt-get install aubio-tools libaubio-dev libaubio-doc
8. curl

※ Tools introduce:

1. youtube-dl
   - https://yt-dl.org/downloads/latest/youtube-dl
   
※ Configuration Setting:

1. Change the correct Socket Server IP address in socket.cpp line 14
2. Change the correct MySQL server url in mysql.cpp line 9

※ Setup:

1. mkdir [projectFolderPath]
2. git clone https://github.com/turtle11311/just-beat-it [projectFolderPath]
3. sudo cp [projectFolderPath]/sources/libs/libmysqlclient.so.18 /usr/lib/
4. mkdir [targetFolderPath]
5. cd [targetFolderPath]
6. qmake [projectFolderPath]/just-beat-it.pro
7. make
8. rm Makefile *.o *.h *.cpp
9. execute just-beat-it(remember to change current dir to [targetFolderPath] before running the game if execute with terminal)

