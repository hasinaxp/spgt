@echo off
cl /W1 /EHsc test_g.cpp
del test_g.obj
test_g.exe