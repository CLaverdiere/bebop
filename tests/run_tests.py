# These tests assume an executable already exists.
# See the makefile for compiling and linking.

# TODO find a way to generate these instead of repeating them all, that's
# compatable with the ancient GL python version.

import unittest
import os, random
import subprocess

art_enable = False

# Integer arithmetic tests.
class TestProj1(unittest.TestCase):
    def setUp(self):
        pass

    def test_easy(self):
        fi = open("pass/test_p1_easy.bb", "r")
        fi.readline()
        expr = fi.readline().split('=')[1].strip()
        val = eval(expr)
        out = int(os.popen("./pass/test_p1_easy.out").read())
        self.assertEqual(val, out)

    def test_medium(self):
        fi = open("pass/test_p1_medium.bb", "r")
        fi.readline()
        expr = fi.readline().split('=')[1].strip()
        val = eval(expr)
        out = int(os.popen("./pass/test_p1_medium.out").read())
        self.assertEqual(val, out)

    def test_hard(self):
        fi = open("pass/test_p1_hard.bb", "r")
        fi.readline()
        expr = fi.readline().split('=')[1].strip()
        val = eval(expr)
        out = int(os.popen("./pass/test_p1_hard.out").read())
        self.assertEqual(val, out)

# Floating point and integer declaration, assignment, and printing tests.
class TestProj2(unittest.TestCase):
    def setup(self):
        pass

    def test_easy(self):
        out = int(os.popen("./pass/test_p2_easy.out").read())
        self.assertEqual(6, out)

    def test_medium(self):
        out = float(os.popen("./pass/test_p2_medium.out").read())
        self.assertEqual(28.1, out)

    def test_hard(self):
        out = float(os.popen("./pass/test_p2_hard.out").read())
        self.assertEqual(496.2, out)

class TestProj3(unittest.TestCase):
    def setup(self):
        pass

    def test_easy(self):
        out = os.popen("./pass/test_p3_easy.out").read()
        msg = out.lower()
        look_for = "let's jam"
        result = look_for in msg
        self.assertEqual(result, True)

    def test_medium(self):
        out = os.popen("echo '24 48 4.25 5.13' | ./pass/test_p3_medium.out")
        out.readline()
        iresult = int(out.readline())
        out.readline()
        fresult = float(out.readline())
        self.assertEqual(72, iresult)
        self.assertEqual(9.38, fresult)

    def test_hard(self):
        out = os.popen("echo '50 1 2 3 4 5 6 7 8 9 10' | ./pass/test_p3_hard.out")
        out.readline()
        temp_result = float(out.readline())
        out.readline()
        rand_result = int(out.readline())
        self.assertEqual(10.0, temp_result)
        self.assertEqual(97, rand_result)

class TestProj4(unittest.TestCase):
    def setup(self):
        pass

    def test_easy(self):
        result = os.popen("./pass/test_p4_easy.out").read()
        expect = "01000101111001010100114300123411234223433444"
        self.assertEqual(result, expect)

    def test_medium(self):
        out = os.popen("echo '83809' | ./pass/test_p4_medium.out").read()
        msg = out.lower()
        look_for = "doesn't converge"
        result = look_for in msg
        self.assertEqual(result, True)

    def test_hard(self):
        out = int(os.popen("./pass/test_p4_hard.out").read())
        self.assertEqual(24133, out)

class TestProj5(unittest.TestCase):
    def setup(self):
        pass

    def test_easy(self):
        out = os.popen("./pass/test_p5_easy.out").read()
        look_for = "17"
        result = look_for in out
        self.assertEqual(result, True)

    def test_medium(self):
        out = os.popen("./pass/test_p5_medium.out").read()
        look_for = "55"
        result = look_for in out
        self.assertEqual(result, True)

    def test_hard(self):
        out = int(os.popen("./pass/test_p5_hard.out").read())
        result = 533
        self.assertEqual(result, out)

class TestProj6(unittest.TestCase):
    def setup(self):
        pass

    def test_easy(self):
        out = float(os.popen("./pass/test_p6_easy.out").read())
        result = 720.0 + .745705
        self.assertEqual(result, out)

    def test_medium(self):
        out = int(os.popen("./pass/test_p6_medium.out").read())
        result = 40730
        self.assertEqual(result, out)

    def test_hard(self):
        out = os.popen("./pass/test_p6_hard.out").read()
        look_for = "++  +++"
        result = look_for in out
        self.assertEqual(result, True)

class TestProj7(unittest.TestCase):
    def setup(self):
        pass

    def test_final(self):
        out = os.popen("echo '1' | ./pass/test_p7_final.out").read()
        look_for = "6694"
        result = look_for in out
        self.assertEqual(result, True)
        if result == True and art_enable:
            with open("../art/see_you_space_cowboy.txt", 'r') as spike_file:
                print(spike_file.read())

# These are miscellaneous tests outside of the main project test cases, but are
# still meant to pass.
class TestPassing(unittest.TestCase):
    def setup(self):
        pass

    def test_array(self):
        out = float(os.popen("./pass/test_array.out").read())
        result = 7.0
        self.assertEqual(result, out)

    def test_array_local(self):
        out = os.popen("./pass/test_array_local.out").read()
        look_for = "2.4"
        result = look_for in out
        self.assertEqual(result, True)

    def test_array_bounds(self):
        out = os.popen("./pass/test_array_bounds.out").read()
        look_for = "HI THERE"
        result = look_for not in out
        self.assertEqual(result, True)

    def test_array_sort(self):
        out = os.popen("./pass/test_array_sort.out").read()
        look_for = "0, 1, 2, 3, 4, 5, 6, 7, 8, 9"
        result = look_for in out
        self.assertEqual(result, True)

    def test_leave_and_next(self):
        out = int(os.popen("./pass/test_leave_and_next.out").read())
        result = 150
        self.assertEqual(result, out)

    def test_nonetype(self):
        out = os.popen("./pass/test_nonetype.out").read()
        look_for = "nayyay"
        result = look_for in out
        self.assertEqual(result, True)

    def test_scope1(self):
        out = float(os.popen("./pass/test_scope1.out").read())
        result = 3.4
        self.assertEqual(result, out)

    def test_string_type(self):
        out = os.popen("./pass/test_string_type.out").read()
        look_for = "alpha and the omega"
        result = look_for in out
        self.assertEqual(result, True)

    def test_struct_global(self):
        out = os.popen("./pass/test_struct_global.out").read()
        look_for = "Ya still got some fight in ya!"
        result = look_for in out
        self.assertEqual(result, True)

    def test_struct_local(self):
        out = int(os.popen("./pass/test_struct_local.out").read())
        result = 65500
        self.assertEqual(result, out)

    def test_struct_array(self):
        out = float(os.popen("./pass/test_struct_array.out").read())
        result = 19.040000
        self.assertEqual(result, out)

# These test cases are intentionally designed to fail. We parse the output of
# logfiles to find our desired error message.
# Using assertIn would be easier, but the test server only has python 2.6.
class TestFailures(unittest.TestCase):
    def setup(self):
        pass

    def test_fun_count1(self):
        fi = open("fail/fail_fun_count1.bb.log", "r")
        err = fi.read().lower()
        look_for = "2 arguments when it requires 3"
        result = look_for in err
        self.assertEqual(result, True)

    def test_fun_count2(self):
        fi = open("fail/fail_fun_count2.bb.log", "r")
        err = fi.read().lower()
        look_for = "too many arguments"
        result = look_for in err
        self.assertEqual(result, True)

    def test_redeclared(self):
        fi = open("fail/fail_redeclared.bb.log", "r")
        err = fi.read().lower()
        look_for = "conflicting types"
        result = look_for in err
        self.assertEqual(result, True)

    def test_return_type(self):
        fi = open("fail/fail_return_type.bb.log", "r")
        err = fi.read().lower()
        look_for = "type mismatch"
        result = look_for in err
        self.assertEqual(result, True)

    def test_scope_same_level_diff_block(self):
        fi = open("fail/fail_scope1.bb.log", "r")
        err = fi.read().lower()
        look_for = "not declared"
        result = look_for in err
        self.assertEqual(result, True)

    def test_scope_diff_level(self):
        fi = open("fail/fail_scope2.bb.log", "r")
        err = fi.read().lower()
        look_for = "not declared"
        result = look_for in err
        self.assertEqual(result, True)

    def test_string_math_ops(self):
        fi = open("fail/fail_string_math_ops.bb.log", "r")
        err = fi.read().lower()
        look_for = "operation (+) not defined"
        result = look_for in err
        self.assertEqual(result, True)

    def test_types1(self):
        fi = open("fail/fail_types1.bb.log", "r")
        err = fi.read().lower()
        look_for = "type mismatch"
        result = look_for in err
        self.assertEqual(result, True)

    def test_types2(self):
        fi = open("fail/fail_types2.bb.log", "r")
        err = fi.read().lower()
        look_for = "type mismatch"
        result = look_for in err
        self.assertEqual(result, True)

    def test_type_check(self):
        fi = open("fail/fail_type_check.bb.log", "r")
        err = fi.read().lower()
        look_for = "should be of type bool, not float"
        result = look_for in err
        self.assertEqual(result, True)

    def test_undeclared(self):
        fi = open("fail/fail_undeclared.bb.log", "r")
        err = fi.read().lower()
        look_for = "not declared"
        result = look_for in err
        self.assertEqual(result, True)

if __name__ == '__main__':
    unittest.main()
