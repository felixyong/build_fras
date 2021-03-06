# -*- coding: utf-8 -*- 
#-----------------------------------------------------------------------------------
# 
#-----------------------------------------------------------------------------------

import unittest, my_math
from subprocess import Popen, PIPE

class ProductTestCase(unittest.TestCase):
    
    def testIntegers(self):
        for x in range(-10, 10):
            for y in range(-10, 10):
                p = my_math.product(x, y)
                self.assertTrue(p == x*y, 'Integer multiplication failed')
                
    def testFloats(self):
        for x in range(-10, 10):
            for y in range(-10, 10):
                x = x/10.0
                y = y/10.0
                p = my_math.product(x, y)
                self.assertTrue(p == x*y, 'Float multiplication failed')
'''  
    def testWithPyLint(self):
        cmd = 'pylint', '-rn', 'my_math'
        pylint = Popen(cmd, stdout = PIPE, stderr = PIPE)
        self.assertEqual(pylint.stdout(), '')
'''   
if __name__ == '__main__': unittest.main()