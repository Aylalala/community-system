TARGET=client
FILE=*.c
CONFIG=-lpthread -L./ -lfont -lm

CC=arm-linux-gcc

$(TARGET):$(FILE)
	$(CC) $^ -o $@ $(CONFIG) 

clean:
	$(RM) $(TARGET)
