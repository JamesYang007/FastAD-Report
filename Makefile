PAPER = fastad-report
TEX = $(wildcard *.tex)
BIB = references.bib
FIGS = $(wildcard figs/*.pdf figs/*.png graphs/*.pdf graphs/*.png)

PDFLATEX=pdflatex -halt-on-error

STYLE=llncs.cls splncs04.bst

.PHONY: all style clean open o

$(PAPER).pdf: $(TEX) $(BIB) $(FIGS) $(STYLE)
	echo $(FIGS)
	$(PDFLATEX) $(PAPER)
	bibtex $(PAPER)
	$(PDFLATEX) $(PAPER)
	$(PDFLATEX) $(PAPER)

open o: $(PAPER).pdf
	open $(PAPER).pdf

clean:
	rm -f *.aux *.bbl *.blg *.log *.out $(PAPER).pdf
