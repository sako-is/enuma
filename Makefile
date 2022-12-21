cc := clang
cflags := -std=gnu18 -g -fPIC
include := -Iengine/ -I/root/1.3.231.2/x86_64/include/vulkan/
libs := -lm -lglfw -lvulkan
defines := -DENM_EXPORT
files := $(shell find . -type f -name "*.c")
targets := $(patsubst %.c, %.o, $(files))

all:
	mkdir -p bin/
	$(cc) $(cflags) $(include) $(libs) $(defines) $(files) -o bin/enuma

# enuma: $(targets)
# 	$(cc) $(targets) -o $@

# $(targets): $(files)
# 	$(cc) $(cflags) $(include) $(libs) $< -o $@

clean:
# 	rm $(targets)
	rm -r bin