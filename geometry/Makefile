FILES = .point.cpp.hash .primitives.cpp.hash .hull.cpp.hash .kd_tree.cpp.hash .range_tree.cpp.hash .enclosing_circle.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm $(FILES)
