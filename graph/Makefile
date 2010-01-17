FILES = .busacker_gowen.cpp.hash .dinic.cpp.hash .gabow.cpp.hash .dijkstra_sparse_fast.cpp.hash

all: $(FILES)

.PHONY: clean

$(FILES): .%.hash: %
	../gen_hash.sh $< $@

clean:
	rm $(FILES)
