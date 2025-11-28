project('clox', 'c', version: '0.0.1', license: 'MIT')

inc = include_directories('include')
sources = [
    'src/chunk.c',
    'src/debug.c',
    'src/main.c',
    'src/memory.c',
    'src/value.c',
]
executable('clox', sources, include_directories: inc)
