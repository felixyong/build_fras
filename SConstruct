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

sources3 = []
#files
sources3.extend([
'src\\gtest_main.cc',
'src\\gtest-all.cc',
'src\\clPICtrl.cpp',
'src\\clPICtrl_UnitTest.cpp'
])
Program(target = 'clPICtrl_UnitTest', source = sources3)

sources4 = []
#files
sources4.extend([
'src\\main.cpp',
'src\\SimpleMath.cpp'
])
Program(target = 'program', source = sources4)



