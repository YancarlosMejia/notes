all: proj_sub.pdf
	make -C pi

test:
	make -C pi test

.SUFFIXES:
.SUFFIXES: .pdf .tex

.tex.pdf:
	latexmk -pdf $<


clean:
	rm -f proj_sub.pdf
	rm -f *.aux
	rm -f *.fdb_latexmk
	rm -f *.fls
	rm -f *.log
	rm -f *.toc
	make -C pi clean
