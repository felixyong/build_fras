

#####################################
"""
repr function transfer par to string
"""
temp = 42
print ("The temperature is " + repr(temp))

#####################################
"""
Two ways for long stance
"""
print ('This is a very long string. \
It continues here.')
print ('''This is a very long string.
It continues here.''')

#####################################
"""
r - row string
"""
print (r'C:\nowhere')

#####################################
"""
单步调试
python -m pdb *.py

break 或 b ：设置断点
continue 或 c：继续执行程序
list 或 l：查看当前行的代码段
step 或 s：进入函数
return 或 r：执行代码直到从当前函数返回
exit 或 q：中止并退出
next 或 n：执行下一行
pp：打印变量的值
a：查看全部栈内变量
"""