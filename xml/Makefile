STYLESHEETS_DIR = ./stylesheet
FILENAME = report

all: html pdf

html:
	xsltproc -o $(FILENAME).html $(STYLESHEETS_DIR)/xhtml/report.xsl $(FILENAME).xml

fo:
	xsltproc -o $(FILENAME).fo $(STYLESHEETS_DIR)/fo/result-report.xsl $(FILENAME).xml

pdf: fo
	fop -pdf $(FILENAME).pdf -fo $(FILENAME).fo

clean:
	rm -rf $(FILENAME).html $(FILENAME).fo $(FILENAME).pdf
