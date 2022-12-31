@echo off

set cc = clang
set cflags = -std=c18 -g -fPIC
set include = -Iengine/ -I%VULKAN_SDK%/Include/vulkan/
set libs = -lm -lglfw -lvulkan
set defines = -DENM_EXPORT
for /f "delims=" %%F in ('dir /b /s "*.c" 2^>nul') do set files=%%F

cmd %cc% %cflags% %include% %libs% %defines% %files% -o bin/enuma.exe