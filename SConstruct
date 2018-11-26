# SConstruct

sources3 = []
#files
sources3.extend([
'src\\gtest_main.cc',
'src\\gtest-all.cc'
])
Library(source = sources3)

sources1 = []
#files
sources1.extend([
'src\\gtest_main.obj',
'src\\gtest-all.obj',
'src\\unittest_SimpleMath.cpp',
'src\\SimpleMath.cpp'
])
Program(target = 'unittest', source = sources1)


sources2 = []
#files
sources2.extend([
'src\\main.cpp',
'src\\SimpleMath.cpp'
])
Program(target = 'program', source = sources2)



