SOURCES=$(wildcard *.adoc)

all: index.html

index.html: $(SOURCES)
	asciidoctor -b html5 index.adoc

clean:
	rm -rf *.html

.PHONY: clean
