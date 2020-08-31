PAPER = fastad-report
TEX = $(wildcard *.tex)
BIB = references.bib
FIGS = $(wildcard figures/*.pdf figures/*.png graphs/*.pdf graphs/*.png)

PDFLATEX=pdflatex -halt-on-error

.PHONY: all clean open o

$(PAPER).pdf: $(TEX) $(BIB) $(FIGS) acmart.cls
	echo $(FIGS)
	$(PDFLATEX) $(PAPER)
	bibtex $(PAPER)
	$(PDFLATEX) $(PAPER)
	$(PDFLATEX) $(PAPER)

open o: $(PAPER).pdf
	open $(PAPER).pdf

clean:
	rm -f *.aux *.bbl *.blg *.log *.out $(PAPER).pdf
