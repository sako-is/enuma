cc := clang
cflags := -std=gnu18 -g -fPIC
# include := -Iengine/ -I/root/1.3.231.2/x86_64/include/vulkan/
include := -Iengine/ -I$(VULKAN_SDK)/Include/vulkan/
libs := -lm -lglfw -lvulkan
defines := -DENM_EXPORT
files := %.c

all:
	mkdir -p bin/
	$(cc) $(cflags) $(include) $(libs) $(defines) $(files) -o bin/enuma.exe

# enuma: $(targets)
# 	$(cc) $(targets) -o $@

# $(targets): $(files)
# 	$(cc) $(cflags) $(include) $(libs) $< -o $@

clean:
# 	rm $(targets)
	rm -r bin