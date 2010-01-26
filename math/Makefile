FILES = .crt.cpp.hash .frac.cpp.hash .lis.cpp.hash .simplex.cpp.hash .romberg.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm $(FILES)
