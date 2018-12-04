# SConstruct

sources1 = []
#files
sources1.extend([
'src\\gtest_main.cc',
'src\\gtest-all.cc'
])
Library(source = sources1)

sources2 = []
#files
sources2.extend([
'src\\gtest_main.cc',
'src\\gtest-all.cc',
'src\\unittest_SimpleMath.cpp',
'src\\SimpleMath.cpp'
])
Program(target = 'unittest_SimpleMath', source = sources2)

sources4 = []
#files
sources4.extend([
'src\\main.cpp',
'src\\SimpleMath.cpp'
])
Program(target = 'program', source = sources4)



