※ Environment:

1. linux
2. Qt version 5.9.4

※ Package needed:

1. git
2. Qt version 5.9.4 with Qt Charts & qmake
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

※ Setup:

1. mkdir [projectFolderPath]
2. git clone https://github.com/turtle11311/just-beat-it [projectFolderPath]
3. sudo cp [projectFolderPath]/sources/libs/libmysqlclient.so.18 /usr/lib/
4. mkdir [targetFolderPath]
5. cd [targetFolderPath]
6. qmake [projectFolderPath]/just-beat-it.pro
7. make
8. rm Makefile *.o *.h *.cpp

