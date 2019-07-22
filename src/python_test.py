# -*- coding: utf-8 -*- 
#-----------------------------------------------------------------------------------
# 
#-----------------------------------------------------------------------------------

if __name__=='__main__':
    import doctest, my_math
    doctest.testmod(my_math)
    
import unittest, my_math

class ProductTestCase(unittest.TestCase):
    
    def testIntegers(self):
        for x in xrange(-10, 10):
            for y in xrange(-10, 10):
                p = my_math.product(x, y)
                self.failUnless(p == x*y, 'Integer multiplication failed')
                
    def testFloats(self):
        for x in xrange(-10, 10):
            for y in xrange(-10, 10):
                x = x/10.0
                y = y/10.0
                p = my_math.product(x, y)
                self.failUnless(p == x*y, 'Float multiplication failed')
    

if __name__ == '__main__': unittest.main()
    