project('enuma', 'c', default_options : ['c_std=c18'])
add_global_arguments(['-DENM_EXPORT', '-g'], language : 'c')

deps = [dependency('vulkan'), dependency('glfw3')]
files = files([
	'engine/containers/vector.c',
	'engine/core/app.c',
	'engine/core/strings.c',
	'engine/ecs/ecs.c',
	'engine/log/logger.c',
	'engine/platform/pLinux.c',
	'engine/platform/pWindows.c',
	'engine/render/render.c',	
	'engine/render/vulkan/vulkan.c'
])

incdirs = ['engine']

executable('enuma', file : files, dependencies : deps, include_directories : files)

