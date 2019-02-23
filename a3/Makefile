FLAGS = -Wall -std=gnu99 -g

all: copy image_filter greyscale gaussian_blur edge_detection scale

copy: copy.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

image_filter: image_filter.o
	gcc ${FLAGS} -o $@ $^ -lm

greyscale: greyscale.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

gaussian_blur: gaussian_blur.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

edge_detection: edge_detection.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

scale: scale.o bitmap.o
	gcc ${FLAGS} -o $@ $^ -lm

%.o: %.c bitmap.h
	gcc ${FLAGS} -c $<

clean:
	rm *.o image_filter copy

test:
	mkdir images -p
	./copy < dog.bmp > images/dog_copy.bmp
	./greyscale < dog.bmp > images/dog_grey.bmp
	./gaussian_blur < dog.bmp > images/dog_blur.bmp
	./edge_detection < dog.bmp > images/dog_edges.bmp
	./scale 2 < dog.bmp > images/dog_big.bmp
	./image_filter dog.bmp images/dog_piped.bmp ./gaussian_blur ./gaussian_blur ./gaussian_blur ./greyscale "./scale 2"
