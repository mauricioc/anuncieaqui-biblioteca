FILES = .dotemacs.hash .hashgen.hash .template.cpp.hash .dotvimrc.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm $(FILES)
