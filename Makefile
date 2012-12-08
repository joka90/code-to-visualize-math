#
# Makefile för kalkylatorn, nivå G, GNU GCC (g++)
#
# Variabeln GCC4_V (se LDFLAGS) sätts i prog/gcc/4 och anger den aktuella 
# versionen av GCC 4 (normalt den senaste som är installerad på IDA).
#
# gccfilter är ett hjälpmedel för att förenkla och färglägga diagnostiska
# meddelanden från g++ (gcc).
#

# Filkataloger där andra delar av programet finns.
#EXPRESSION = ../Expression

# Kompilator
#CCC = g++
CXX = g++-4.4

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lfftw3

# Preprocessorflaggor, -I lägger till en filkatalog i inkluderingssökvägen.
CPPFLAGS += -I../SFML/include/

# Länkflaggor - Fix för att lösa lokala problem med C++ länkbibliotek.
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
