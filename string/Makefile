FILES = .karkkainen.cpp.hash .morris_pratt.cpp.hash .aho_corasick.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm $(FILES)
