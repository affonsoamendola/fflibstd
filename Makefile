source = *.cpp
bin = test

CC = g++
LIBRARY = 
CFLAGS = -g -Ofast
INCLUDE = .

$(bin) : $(source) *.hpp
	$(CC) $(CFLAGS) -B$(INCLUDE) -o$(bin) $(source) $(LIBRARY)

clean:
	rm $(bin)
	
run:
	./$(bin)