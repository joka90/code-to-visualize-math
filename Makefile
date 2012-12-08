#
# Makefile f�r kalkylatorn, niv� G, GNU GCC (g++)
#
# Variabeln GCC4_V (se LDFLAGS) s�tts i prog/gcc/4 och anger den aktuella 
# versionen av GCC 4 (normalt den senaste som �r installerad p� IDA).
#
# gccfilter �r ett hj�lpmedel f�r att f�renkla och f�rgl�gga diagnostiska
# meddelanden fr�n g++ (gcc).
#

# Filkataloger d�r andra delar av programet finns.
#EXPRESSION = ../Expression

# Kompilator
#CCC = g++
CXX = g++-4.4

# Kompilatorflaggor, l�gg till '-g' om kompilering f�r avlusning ska g�ras.
CCFLAGS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lfftw3

# Preprocessorflaggor, -I l�gger till en filkatalog i inkluderingss�kv�gen.
CPPFLAGS += -I../SFML/include/

# L�nkflaggor - Fix f�r att l�sa lokala problem med C++ l�nkbibliotek.
LDFLAGS += -L../SFML/lib/

# Bra om man vill testa classer sepparat
music:  main.o MusicAnalyzer.o Makefile
	$(CXX) $(CPPFLAGS) $(CCFLAGS) $(LDFLAGS) -o music  main.o MusicAnalyzer.o

#Testfile for AnimatedSprite class
main.o: main.cc
	$(CXX) $(CPPFLAGS) $(CCFLAGS) -c main.cc

# Compile AnimatedSprite Class
MusicAnalyzer.o: MusicAnalyzer.h MusicAnalyzer.cc
	$(CXX) $(CPPFLAGS) $(CCFLAGS) -c MusicAnalyzer.cc


# 'make clean' tar bort objektkodsfiler och 'core' (minnesdump).
clean:
	@ \rm -rf *.o core
