project(
  'lstuff',
  'cpp',
  version : '0.1',
  meson_version : '>= 1.3.0',
  default_options : ['warning_level=3', 'cpp_std=c++17'],
)

incdir = include_directories('include')

cmake = import('cmake')
luau = cmake.subproject('luau')

luau_common = luau.dependency('Luau.Common')
luau_vm = luau.dependency('Luau.VM')
luau_cmp = luau.dependency('Luau.Compiler')
luau_ast = luau.dependency('Luau.Ast')


subdir('src')